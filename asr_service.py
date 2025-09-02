# This Python file uses the following encoding: utf-8

# if __name__ == "__main__":
#     pass
# -*- coding: utf-8 -*-
import os
import wave
import json
import audioop
from urllib.parse import urlparse, unquote
from typing import Optional

from vosk import Model, KaldiRecognizer

_MODEL: Optional[Model] = None
_TARGET_RATE = 16000  # 统一转换为 16k 采样率，兼容性最好


def _from_file_url(path_or_url: str) -> str:
    """
    将 file:/// 开头的 URL 转换为本地文件路径；普通路径则原样返回。
    兼容 Windows 下的 file:///C:/... 与 *nix 的 file:///home/...
    """
    if path_or_url.startswith("file://"):
        parsed = urlparse(path_or_url)
        # Windows 下 parsed.netloc 可能为空或为盘符，path 需要 unquote
        local_path = unquote(parsed.path)
        if os.name == "nt":
            # 去掉可能多余的前导斜杠，例如 /C:/path -> C:/path
            if local_path.startswith("/") and len(local_path) > 3 and local_path[2] == ":":
                local_path = local_path.lstrip("/")
        return local_path
    return path_or_url


def load_model(model_dir: str) -> None:
    """
    懒加载 Vosk 模型。建议在进程启动时调用一次。
    """
    global _MODEL
    if _MODEL is None:
        if not os.path.isdir(model_dir):
            raise RuntimeError("Vosk 模型未找到: %s" % model_dir)
        _MODEL = Model(model_dir)


def _iter_wav_as_16k_mono_s16le(path: str, chunk_frames: int = 4000):
    """
    以流式方式读取任意 PCM WAV，并转换为：
    - 单声道（mono）
    - 16-bit（S16_LE）
    - 16k 采样率
    然后逐块产出字节数据，便于送入 KaldiRecognizer。

    注意：仅支持未压缩 PCM WAV（wave 模块本身也只支持该类）。
    """
    with wave.open(path, "rb") as wf:
        n_channels = wf.getnchannels()
        sampwidth = wf.getsampwidth()
        framerate = wf.getframerate()
        comptype = wf.getcomptype()

        if comptype not in ("NONE", "not compressed"):
            raise RuntimeError("仅支持未压缩 PCM WAV，当前压缩类型: %s" % comptype)

        # ratecv 状态在分块转换时需要保留
        ratecv_state = None

        while True:
            frames = wf.readframes(chunk_frames)
            if not frames:
                break

            data = frames

            # 若为多声道（常见为双声道），先下混为单声道
            if n_channels == 2:
                # 等权重下混
                data = audioop.tomono(data, sampwidth, 0.5, 0.5)
                nch = 1
            elif n_channels == 1:
                nch = 1
            else:
                # 非 1/2 声道的情况，这里简单取前两个声道做下混
                if n_channels > 2:
                    # 先转换为 2 声道再 tomono（保守做法）
                    data = audioop.tomono(data, sampwidth, 1.0, 0.0)
                    nch = 1
                else:
                    nch = n_channels  # 理论上不会到这

            # 采样位深转 16-bit
            if sampwidth != 2:
                data = audioop.lin2lin(data, sampwidth, 2)
                width = 2
            else:
                width = 2

            # 采样率转换为 16k
            if framerate != _TARGET_RATE:
                data, ratecv_state = audioop.ratecv(
                    data, width, nch, framerate, _TARGET_RATE, ratecv_state
                )

            yield data


def recognize_wav(path_or_url: str) -> str:
    """
    识别本地 WAV 文件（或 file:// URL 指向的 WAV）。
    - 自动将音频转换为 单声道/16-bit/16k 再送入 Vosk
    - 返回识别文本（空字符串表示未识别到有效文本）

    兼容性增强点：
    - 不再要求输入必须是单声道 8k/16k；常见的双声道/44.1k/48k 也会自动转换
    """
    if _MODEL is None:
        raise RuntimeError("Vosk 模型未加载")

    path = _from_file_url(path_or_url)
    if not os.path.exists(path):
        raise RuntimeError("音频文件不存在: %s" % path)

    rec = KaldiRecognizer(_MODEL, _TARGET_RATE)
    rec.SetWords(True)

    try:
        for chunk in _iter_wav_as_16k_mono_s16le(path):
            # chunk 是已转换好的字节流，直接送入识别器
            rec.AcceptWaveform(chunk)

        final = rec.FinalResult()  # JSON 字符串，形如 {"text": "...", ...}
        txt = json.loads(final).get("text", "") if final else ""
        return txt or ""
    except wave.Error as e:
        raise RuntimeError("WAV 解析失败：%s（请确认是未压缩 PCM WAV）" % str(e))
    except Exception as e:
        # 统一包装为 RuntimeError，便于上层返回给前端
        raise RuntimeError("语音识别失败：%s" % str(e))

# This Python file uses the following encoding: utf-8

# if __name__ == "__main__":
#     pass
# -*- coding: utf-8 -*-
import os
import wave
from typing import Tuple

from vosk import Model, KaldiRecognizer

_MODEL = None

def load_model(model_dir: str) -> None:
    global _MODEL
    if _MODEL is None:
        if not os.path.isdir(model_dir):
            raise RuntimeError("Vosk 模型未找到: %s" % model_dir)
        _MODEL = Model(model_dir)

def recognize_wav(path: str) -> str:
    if _MODEL is None:
        raise RuntimeError("Vosk 模型未加载")

    wf = wave.open(path, "rb")
    try:
        if wf.getnchannels() != 1 or wf.getsampwidth() != 2 or wf.getframerate() not in (16000, 8000):
            raise RuntimeError("仅支持 16-bit PCM 单声道 8k/16k WAV")
        rec = KaldiRecognizer(_MODEL, wf.getframerate())
        rec.SetWords(True)

        result = []
        while True:
            data = wf.readframes(4000)
            if len(data) == 0:
                break
            if rec.AcceptWaveform(data):
                pass
        final = rec.FinalResult()
        # final 为 JSON 字符串，形如 {"text": "..."}
        import json
        txt = json.loads(final).get("text", "")
        return txt
    finally:
        wf.close()

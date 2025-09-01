#include "recorderprocess.h"
#include <QFileInfo>
#include <QStandardPaths>


RecorderProcess::RecorderProcess(QObject* parent) : QObject(parent) {
    connectProcess();
}

void RecorderProcess::connectProcess() {
    connect(&m_proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this](int, QProcess::ExitStatus) {
                if (!m_currentOutputPath.isEmpty()) {
                    emit finished(QUrl::fromLocalFile(m_currentOutputPath));
                }
                m_currentOutputPath.clear();
            });
    connect(&m_proc, &QProcess::errorOccurred, this, [this](QProcess::ProcessError err) {
        QString msg = "Recorder process error: " + QString::number(int(err)) + " (" + m_proc.errorString() + ")";
        emit errorOccurred(msg);
    });
}

void RecorderProcess::start(const QString& outputPath) {
    if (isRecording())
        return;

    m_currentOutputPath = outputPath;
    // arecord: 16-bit PCM, mono, 16kHz, WAV
    // -q: quiet; -f: format; -c: channels; -r: rate; -t: type
    QString program = "arecord";
    QStringList args;
    args << "-q" << "-f" << "S16_LE" << "-c" << "1" << "-r" << "16000" << "-t" << "wav" << outputPath;

    m_proc.start(program, args);

    if (!m_proc.waitForStarted(1500)) {
        emit errorOccurred(QString("Failed to start arecord: %1").arg(m_proc.errorString()));
        m_currentOutputPath.clear();
    }
}

void RecorderProcess::stop() {
    if (!isRecording())
        return;

    // 尝试优雅结束
    m_proc.terminate();
    if (!m_proc.waitForFinished(1500)) {
        m_proc.kill();
        m_proc.waitForFinished(1000);
    }
}

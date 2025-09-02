#pragma once
#include <QObject>
#include <QProcess>
#include <QUrl>

class RecorderProcess : public QObject {
    Q_OBJECT
public:
    explicit RecorderProcess(QObject* parent = nullptr);

    Q_INVOKABLE bool isRecording() const { return m_proc.state() != QProcess::NotRunning; }
    Q_INVOKABLE void start(const QString& outputPath); // e.g. "/tmp/asr.wav"
    Q_INVOKABLE void stop();

signals:
    void finished(const QUrl& fileUrl);
    void errorOccurred(const QString& message);

private:
    QProcess m_proc;
    QString m_currentOutputPath;
    void connectProcess();
};

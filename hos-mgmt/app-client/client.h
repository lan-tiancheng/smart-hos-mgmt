#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QObject *parent = nullptr);
    ~client();
};

#endif // CLIENT_H

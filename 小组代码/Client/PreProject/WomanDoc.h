#ifndef WOMANDOC_H
#define WOMANDOC_H

#endif // WOMANDOC_H
#include <QString>
#include <QPixmap>
#include <QLabel>

class WomanDoc{
public:
    QLabel *picturelabel;
    QLabel *namelabel;
    QLabel *positionlabel;
    QLabel *introducelabel;
    QPixmap picture;
    QString name="李医生";
    QString position="主治医师";
    QString introduce="擅长妇科病";
    QString id;//工号
};

#ifndef SKINDOC_H
#define SKINDOC_H

#endif // SKINDOC_H
#include <QString>
#include <QPixmap>
#include <QLabel>

class SkinDoc{
public:
    QLabel *picturelabel;
    QLabel *namelabel;
    QLabel *positionlabel;
    QLabel *introducelabel;
    QPixmap picture;
    QString name="赵医生";
    QString position="主治医师";
    QString introduce="擅长皮肤病";
    QString id;//工号
};

#ifndef INSIDEDOC_H
#define INSIDEDOC_H

#endif // INSIDEDOC_H
#include <QString>
#include <QPixmap>
#include <QLabel>

class InsideDoc{
public:
    QLabel *picturelabel;
    QLabel *namelabel;
    QLabel *positionlabel;
    QLabel *introducelabel;
    QPixmap picture;
    QString name="周医生";
    QString position="主治医师";
    QString introduce="擅长内科";
    QString id;//工号
};

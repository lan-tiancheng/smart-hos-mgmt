#ifndef OUTDOC_H
#define OUTDOC_H

#endif // OUTDOC_H
#include <QString>
#include <QPixmap>
#include <QLabel>

class OutDoc{
public:
    QLabel *picturelabel;
    QLabel *namelabel;
    QLabel *positionlabel;
    QLabel *introducelabel;
    QPixmap picture;
    QString name="何医生";
    QString position="主任医师";
    QString introduce="擅长外科手术";
    QString id;//工号
};

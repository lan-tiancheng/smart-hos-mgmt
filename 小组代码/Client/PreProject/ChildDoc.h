#ifndef CHILDDOC_H
#define CHILDDOC_H

#endif // CHILDDOC_H
#include <QString>
#include <QPixmap>
#include <QLabel>

class ChildDoc{
public:
    QLabel *picturelabel;
    QLabel *namelabel;
    QLabel *positionlabel;
    QLabel *introducelabel;
    QPixmap picture;
    QString name="王医生";
    QString position="主任医师";
    QString introduce="擅长治疗熊孩子";
    QString id="114514";//工号
};

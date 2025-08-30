#ifndef MEDICINEITEM_H
#define MEDICINEITEM_H
#include <QLabel>
#include <QString>
#include <QPixmap>
#endif // MEDICINEITEM_H
class MedicineItem{
public:
    QLabel *namelabel;
    QString name="六味地黄丸";
    QLabel *picturelabel;
    QPixmap picture;
    int pictureid;
    QLabel *introducelabel;
    QString introduce="六味地黄丸";
};

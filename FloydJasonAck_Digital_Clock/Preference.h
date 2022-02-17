/* Student ID/Name: 2019120154 Floyd Ack
 * Date: 02/02/2022
 * Course Code: CMPS2212 | Section: 1
 * Program Name: FloydJasonAck_Digital_Clock
*/

#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class Preference;
}

class Preference : public QDialog
{
    Q_OBJECT

public:
    explicit Preference(QWidget *parent = 0);
    ~Preference();

private:
    Ui::Preference *ui;
    QButtonGroup *btnGroup;

private slots:
    void onAccepted();
};

#endif // PREFERENCE_H

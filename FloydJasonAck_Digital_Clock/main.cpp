/* Student ID/Name: 2019120154 Floyd Ack
 * Date: 02/02/2022
 * Course Code: CMPS2212 | Section: 1
 * Program Name: FloydJasonAck_Digital_Clock
*/

#include "FloydDigiClock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName(QString("CMPS2212 GUI Programming"));
    a.setApplicationName(QString("Floyd Digital Clock"));

    FloydDigiClock w;
    w.show();

    return a.exec();
}

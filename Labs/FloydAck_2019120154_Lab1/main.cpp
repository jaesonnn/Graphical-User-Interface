/* Student ID/Name: 2019120154 Floyd Ack
 * Date: 02/02/2022
 * Course Code: CMPS2212 | Section: 1
 * Program Name: FloydAck_2019120154_Lab1
*/

#include "MainMenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu menu;
    menu.show();

    return a.exec();
}

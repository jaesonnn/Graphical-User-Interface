/* Course Title:    GUI | Section 1
 * Program Name:    FloydAck_2019120154_Lab2
 * Student ID/Name: 2019120154 Floyd Ack
 * Submission Date: Wednesday, 16 February 2022
*/

#include "Notepad.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Notepad w;
    w.show();

    return a.exec();
}

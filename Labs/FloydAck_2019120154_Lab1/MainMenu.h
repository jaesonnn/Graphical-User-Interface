/* Student ID/Name: 2019120154 Floyd Ack
 * Date: 02/02/2022
 * Course Code: CMPS2212 | Section: 1
 * Program Name: FloydAck_2019120154_Lab1
*/

#ifndef MAINMENU_H
#define MAINMENU_H

#include "Chat.h"

#include <QWidget>

#include <QColorDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QColor>
#include <QList>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);

private:
    QList<Chat *> chatWindows;
    QLineEdit *userInput;

private slots:
    void onAddChat();
};

#endif // MAINMENU_H

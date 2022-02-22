/* Course Title:    GUI | Section 1
 * Program Name:    FloydAck_2019120154_Lab2
 * Student ID/Name: 2019120154 Floyd Ack
 * Submission Date: Wednesday, 16 February 2022
*/

#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

namespace Ui {
class Notepad;
}

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = 0);
    ~Notepad();

private slots:
    void newDocument();
    void open();
    void save();
    void saveAs();
    void markChange();
    void setFont();
    void print();
    void exit();

private:
    Ui::Notepad *ui;
    QString currentFile;
    QString savedText;
};

#endif // NOTEPAD_H

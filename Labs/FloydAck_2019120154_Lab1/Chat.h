/* Student ID/Name: 2019120154 Floyd Ack
 * Date: 02/02/2022
 * Course Code: CMPS2212 | Section: 1
 * Program Name: FloydAck_2019120154_Lab1
*/

#ifndef CHAT_H
#define CHAT_H

#include <QWidget>

#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class Chat : public QWidget
{
    Q_OBJECT
public:
    explicit Chat(QString, QWidget *parent = nullptr);

signals:
    void sendMessage(QString, QString);

public slots:
    void createMessage();
    void addMessage(QString, QString);

private:
    QVBoxLayout *chatLayout;
    QLineEdit *chatInput;
    QString username;
};

#endif // CHAT_H

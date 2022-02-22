/* Student ID/Name: 2019120154 Floyd Ack
 * Date: 02/02/2022
 * Course Code: CMPS2212 | Section: 1
 * Program Name: FloydAck_2019120154_Lab1
*/

#include "Chat.h"

Chat::Chat(QString name, QWidget *parent)
    : QWidget(parent)
{
    QPushButton * sendBtn = new QPushButton("Send");
    QLineEdit * chatInput = new QLineEdit();

    chatInput->setPlaceholderText("Type Message");

    QHBoxLayout * row = new QHBoxLayout;
    row->addWidget(chatInput);
    row->addWidget(sendBtn);

    QVBoxLayout * col = new QVBoxLayout;
    col->addLayout(row);

    setLayout(col);
    setWindowTitle(name);

    this->chatLayout = col;
    this->chatInput = chatInput;
    this->username = name;

    connect(sendBtn, SIGNAL(clicked(bool)), this, SLOT(createMessage()));
}

void Chat::createMessage()
{
    if(this->chatInput->text().trimmed() == "")
        return;

    QString msg = this->chatInput->text();

    emit this->sendMessage(this->username, msg);

    this->addMessage("YOU", msg);

    this->chatInput->clear();
}

void Chat::addMessage(QString sender, QString msg)
{
    this->layout()->addWidget(new QLabel(sender + " :: " + msg));
}

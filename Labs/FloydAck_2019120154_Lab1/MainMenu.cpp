/* Student ID/Name: 2019120154 Floyd Ack
 * Date: 02/02/2022
 * Course Code: CMPS2212 | Section: 1
 * Program Name: FloydAck_2019120154_Lab1
*/

#include "MainMenu.h" 

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    QPushButton *btn = new QPushButton("New Chat", this);      // create new button
    btn->show();

    QLineEdit *userInput = new QLineEdit();                    // creates new text input
    userInput->setPlaceholderText("Type Username");
    userInput->show();
    this->userInput = userInput;

    QHBoxLayout *row = new QHBoxLayout;                        // creates a row layout
    row->addWidget(userInput);
    row->addWidget(btn);

    QLabel *header = new QLabel("Add Person to Conversation");  // creates header label
    header->setAlignment(Qt::AlignCenter);
    header->setStyleSheet("color: #0755a8; font-weight: bold;");

    QVBoxLayout *col = new QVBoxLayout;    // creates column layout
    col->addWidget(header);
    col->addLayout(row);

    setWindowTitle("Chat App");             // configures the window
    setLayout(col);
    setFixedSize(250, 100);

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(onAddChat()));
}

void MainMenu::onAddChat()
{
    if(this->userInput->text().trimmed() == "")    // checks if the username is invalid
        return;

    QColor color = QColorDialog::getColor();

    if(!color.isValid())
        return;

    QPalette windowColor = QPalette(color);

    Chat *newChat = new Chat(this->userInput->text().trimmed());
    newChat->setPalette(windowColor);

    // loop through each window in the chatWindows data member
    for(int n=0; n<this->chatWindows.length(); n++)
    {
        Chat *currentChat = this->chatWindows.at(n);
        // connect the sendMessage signal from newChat to the addMessage slot of each windowItem
        connect(newChat, SIGNAL(sendMessage(QString,QString)), currentChat, SLOT(addMessage(QString,QString)));

        // connect the sendMessage signal of each windowItem to the addMessage slot of the new window
        connect(currentChat, SIGNAL(sendMessage(QString,QString)), newChat, SLOT(addMessage(QString,QString)));
    }

    this->chatWindows.push_back(newChat);
    newChat->show();

    this->userInput->clear();
}

/* Student ID/Name: 2019120154 Floyd Ack
 * Date: 02/02/2022
 * Course Code: CMPS2212 | Section: 1
 * Program Name: FloydJasonAck_Digital_Clock
*/

#include "FloydDigiClock.h"
#include "ui_FloydDigiClock.h"

#include <QTime>
#include <QTimer>
#include <QPalette>

#include <QDebug>

#include "Preference.h"

FloydDigiClock::FloydDigiClock(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FloydDigiClock)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_TranslucentBackground);
//    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | windowFlags());

    connect(this, &FloydDigiClock::customContextMenuRequested, this, &FloydDigiClock::showContextMenu);

    // create QTimer object and connect to updateTime to start clock every second
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);

    updateTime();   // calls updateTime explicitly allowing the clock to display the current time

    QSettings mySettings;
    restoreGeometry(mySettings.value("MainGeometry").toByteArray());
    restoreState(mySettings.value("MainState").toByteArray());

    setColor();

    QSettings timeSettings;
    restoreState(timeSettings.value("TimeState").toByteArray());
}

FloydDigiClock::~FloydDigiClock()
{
    delete ui;
}

// changes the color of the lcdNumber
void FloydDigiClock::setColor()
{
    QSettings mySettings;
    int currIndex = mySettings.value("Color").toInt();  // reads the color value from the QSettings object that was previously created

    QPalette pal;

    // gets the correct color value and assigns it to the QPalette object
    switch(currIndex)
    {
        case 0:
            pal.setColor(QPalette::Foreground, Qt::black);
            break;
        case 1:
            pal.setColor(QPalette::Foreground, Qt::white);
            break;
        case 2:
            pal.setColor(QPalette::Foreground, Qt::green);
            break;
        case 3:
            pal.setColor(QPalette::Foreground, Qt::red);
            break;
    }

    ui->lcdNumber->setPalette(pal);
    updateTime();       // ensures the time is updated when ONLY a color changes and not the format
    this->update();     // updates the main interface (i.e., the clock)
}

void FloydDigiClock::updateTime()
{
    QSettings timeSettings;
    QString tmeStg = timeSettings.value("Format", "").toString();                   // reads the format value from the QSettings variable and converts it toString()

    if(tmeStg == "12 Hr") {                                                         // the value of the checked button is "12 Hr"
        QTime currTimeTwelveHRFormat = QTime::currentTime();                        // gets current time using currentTime() function
        QString currTimeTxt_TwelveHR = currTimeTwelveHRFormat.toString("hh:mm ap"); // converts the currentTime to a string in an "hh:mm ap" format

        if((currTimeTwelveHRFormat.second() % 2) == 0)                              // colon will flash if the value is even & will reappear when the second's value is odd
            currTimeTxt_TwelveHR[2] = ' ';

        ui->lcdNumber->display(currTimeTxt_TwelveHR);
    }
    else {                                                                                  // the value of the checked button is "24 Hr"
        QTime currTimeTwoFourHRFormat = QTime::currentTime();                               // gets current time using currentTime() function
        QString currTimeTxt_TwoFourHR = currTimeTwoFourHRFormat.toString("hh:mm:ss p");     // converts the currentTime to a string in an "hh:mm:ss ap" format

        if((currTimeTwoFourHRFormat.second() % 2) == 0) {
            currTimeTxt_TwoFourHR[2] = ' ';
            currTimeTxt_TwoFourHR[5] = ' ';
        }

        ui->lcdNumber->display(currTimeTxt_TwoFourHR);
    }
}

// displays a pop-up menu at the given position on the clock
void FloydDigiClock::showContextMenu(const QPoint &pos)
{
    QMenu contextMenu;                                              // creates a contextMenu object of type QMenu
    contextMenu.addAction(QString("Exit"), this, SLOT(close()));    // adds an "Exit" action to the menu

    contextMenu.addAction("Preference", this, SLOT(showPreference()));

    contextMenu.exec(mapToGlobal(pos));                             // mapping to global position
}

// executes a Preference object
void FloydDigiClock::showPreference()
{
    Preference *pref = new Preference(this);
    pref->exec();
    setColor();
}

// triggered when the right button on the mouse is clicked
void FloydDigiClock::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton)              // if the right button is clicked,
        emit customContextMenuRequested(e->pos());  // the menu bar will appear
    else
        QMainWindow::mouseReleaseEvent(e);          // otherwise, call the default mouseReleaseEvent function of QMainWindow
}

// called when a mouse button is pressed
void FloydDigiClock::mousePressEvent(QMouseEvent *e)
{
    m_mousePos = e->pos();                          // the local position of the mouse is stored as m_mousePos
}

// called when the mouse is moving
void FloydDigiClock::mouseMoveEvent(QMouseEvent *e)
{
    this->move(e->globalPos() - m_mousePos);        // moves the clock to the position that we get after subtracting the event's
}                                                   // global position from the local position of the mouse

// saves the geometry and state of the digital clock
void FloydDigiClock::closeEvent(QCloseEvent *e)
{
    QSettings mySettings;
    mySettings.setValue("MainGeometry", saveGeometry());
    mySettings.setValue("MainState", saveState());

    QSettings timeSettings;
    timeSettings.setValue("TimeState", saveState());    // saves the state of the format that was last chosen

    e->accept();
}

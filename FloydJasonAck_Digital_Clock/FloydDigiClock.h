/* Student ID/Name: 2019120154 Floyd Ack
 * Date: 02/02/2022
 * Course Code: CMPS2212 | Section: 1
 * Program Name: FloydJasonAck_Digital_Clock
*/

#ifndef FLOYDDIGICLOCK_H
#define FLOYDDIGICLOCK_H

#include <QMainWindow>

#include <QMouseEvent>
#include <QCloseEvent>
#include <QLCDNumber>
#include <QSettings>
#include <QAction>
#include <QPoint>
#include <QMenu>

namespace Ui {
class FloydDigiClock;
}

class FloydDigiClock : public QMainWindow
{
    Q_OBJECT

public:
    explicit FloydDigiClock(QWidget *parent = 0);
    ~FloydDigiClock();

private:
    Ui::FloydDigiClock *ui;
    QPoint m_mousePos;
    void setColor();

private slots:
    void updateTime();
    void showContextMenu(const QPoint &pos);
    void showPreference();

protected:
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
};

#endif // FLOYDDIGICLOCK_H

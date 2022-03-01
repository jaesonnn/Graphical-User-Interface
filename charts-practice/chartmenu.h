#ifndef CHARTMENU_H
#define CHARTMENU_H

#include <QMainWindow>

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include <QPieSeries>

QT_BEGIN_NAMESPACE
namespace Ui { class chartMenu; }
QT_END_NAMESPACE

class chartMenu : public QMainWindow
{
    Q_OBJECT

public:
    chartMenu(QWidget *parent = nullptr);
    ~chartMenu();


public slots:
    void createBarChart();
    void createLineChart();
    void createPieChart();

private:
    Ui::chartMenu *ui;
};
#endif // CHARTMENU_H

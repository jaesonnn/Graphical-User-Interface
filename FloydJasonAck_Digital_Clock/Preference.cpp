/* Student ID/Name: 2019120154 Floyd Ack
 * Date: 02/02/2022
 * Course Code: CMPS2212 | Section: 1
 * Program Name: FloydJasonAck_Digital_Clock
*/

#include "Preference.h"
#include "ui_Preference.h"

#include <QSettings>

Preference::Preference(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preference)
{
    ui->setupUi(this);

    QSettings mySettings;
    ui->colorBox->setCurrentIndex(mySettings.value("Color").toInt());   // gets the color choice from the drop down "Color" then gets the index (i.e., which choice was made, returns int value)

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onAccepted()));

    btnGroup = new QButtonGroup(this);
    btnGroup->addButton(ui->twentyFourRadio);
    btnGroup->addButton(ui->twelveRadio);

    ui->twentyFourRadio->setChecked(true);      // 24 hr. radio button set to default
}

Preference::~Preference()
{
    delete ui;
}

// returns the results of when OK is clicked from the Preference dialog
void Preference::onAccepted()
{
    QSettings mySettings;
    mySettings.setValue("Color", ui->colorBox->currentIndex());             // saves currentIndex of colorBox to the settings so that we can read this setting elsewhere

    QSettings timeSettings;
    timeSettings.setValue("Format", btnGroup->checkedButton()->text());     // stores the actual text of the button so that we can use it to determine which format the clock should display
}

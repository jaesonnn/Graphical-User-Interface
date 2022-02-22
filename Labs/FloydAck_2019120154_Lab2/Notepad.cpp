/* Course Title:    GUI | Section 1
 * Program Name:    FloydAck_2019120154_Lab2
 * Student ID/Name: 2019120154 Floyd Ack
 * Submission Date: Wednesday, 16 February 2022
*/

#include "Notepad.h"
#include "ui_Notepad.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPrintDialog>
#include <QFontDialog>
#include <QPrinter>
#include <QString>

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->editor);

    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(newDocument()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(open()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(save()));
    connect(ui->actionSave_As, SIGNAL(triggered(bool)), this, SLOT(saveAs()));
    connect(ui->editor, SIGNAL(textChanged()), this, SLOT(markChange()));
    connect(ui->actionFont_2, SIGNAL(triggered(bool)), this, SLOT(setFont()));
    connect(ui->actionPrint, SIGNAL(triggered(bool)), this, SLOT(print()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(exit()));

    savedText = "";
    ui->editor->setText("");
}

Notepad::~Notepad()
{
    delete ui;
}

// creates a new document
void Notepad::newDocument()
{
    if(savedText != ui->editor->toPlainText()) {
        QMessageBox msgBox;
        msgBox.setText("You have unsaved changes.");
        msgBox.setInformativeText("Do you want to proceed?");
        msgBox.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int result = msgBox.exec();

        if(result == QMessageBox::Cancel)
            return;
    }

    savedText = "";
    ui->editor->setText("");
    currentFile = "";
}

// opens an existing file
void Notepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select file");
    QFile file(fileName);

    if(!file.open((QIODevice::ReadOnly) | QFile::Text)) {
        QMessageBox::warning(this, "..", "File not opened.");
        return;
    }
    currentFile = fileName;

    setWindowTitle(fileName);

    QTextStream fileStream(&file);
    QString content = fileStream.readAll();     // reads all content of the file

    savedText = content;
    ui->editor->setText(content);               // sets the text read from the document to the widget

    file.close();
}

// saves a file
void Notepad::save()
{
    QString fileName;

    // if we don't have an existing file name, get one.
    if (currentFile.isEmpty())      // new file without a name
    {
        fileName = QFileDialog::getSaveFileName(this, "Save");

        if (fileName.isEmpty())
            return;

        currentFile = fileName;
    }
    else        // existing file that has been opened
    {
        fileName = currentFile;
    }

    QFile file(fileName);

    // opens the file for writing in text mode
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);

    QTextStream fileStream(&file);
    QString text = ui->editor->toPlainText();       // converts whatever was in the file to plain text

    savedText = text;
    fileStream << text;                             // writes the converted text to the file

    file.close();
}

// saves the file using a new name
void Notepad::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    // opens the file for writing
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);

    QTextStream fileStream(&file);
    QString text = ui->editor->toPlainText();

    savedText = text;
    fileStream << text;

    file.close();
}

// notifies the user that changes have been made by adding an asterisk by the widget's file name.
void Notepad::markChange()
{
    QString file = "New";
    QString prefix = "";

    if(savedText != ui->editor->toPlainText()) {
        prefix = "*";
    }

    if(!currentFile.isEmpty()) {
        file = currentFile;
    }
    setWindowTitle(prefix + file);
}

void Notepad::setFont()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);

    if(fontSelected) {
        ui->editor->setFont(font);
    }
}

// opens a print dialog which gives the user the option to print the document
void Notepad::print()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog * printDialog = new QPrintDialog(&printer, this);

    printDialog->setWindowTitle("Print Document");
    if(printDialog->exec() == QDialog::Accepted) {
        ui->editor->print(&printer);
    }
}

// exits the application
void Notepad::exit()
{
    if(savedText != ui->editor->toPlainText())
    {
        QMessageBox msgBox;
        msgBox.setText("You have unsaved changes.");
        msgBox.setInformativeText("Do you want to exit without saving?");
        msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int result = msgBox.exec();

        if(result == QMessageBox::Cancel)
            return;
    }

    QCoreApplication::quit();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editortext.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->editBox , &QPlainTextEdit::textChanged,
          [this]() { mdContent.setText(ui->editBox->toPlainText()); });
}

MainWindow::~MainWindow()
{
  delete ui;
}




void MainWindow::on_actionOpen_File_triggered()
{
    ui->editBox->setPlainText("open" + mdContent.mdCodeText);
}

void MainWindow::on_actionNew_File_triggered()
{
    ui->editBox->setPlainText("new");
}

void MainWindow::on_actionSave_File_triggered()
{
    ui->editBox->setPlainText("save");
}

void MainWindow::on_actionSave_As_triggered()
{
    ui->editBox->setPlainText("save as");
}

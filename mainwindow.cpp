#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editortext.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QIODevice>
#include <QFileDialog>
#include <QFile>

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
  if (mdFilePath.isEmpty()) {
      on_actionSave_As_triggered();
      return;
  }

  QFile f(mdFilePath);
  if (!f.open(QIODevice::WriteOnly | QIODevice::Text))  {
      QMessageBox::warning(this, windowTitle(),
                           tr("Could not write to file %1: %2").arg(
                               QDir::toNativeSeparators(mdFilePath), f.errorString()));
      return;
  }
  QTextStream str(&f);
  str << ui->editBox->toPlainText();

  ui->editBox->document()->setModified(false);
    ui->editBox->setPlainText("save");
}

void MainWindow::on_actionSave_As_triggered()
{
  QString path = QFileDialog::getSaveFileName(this,
      tr("Save MarkDown File"), "", tr("MarkDown File (*.md, *.markdown)"));
  if (path.isEmpty())
      return;
  mdFilePath = path;
  on_actionSave_File_triggered();
    ui->editBox->setPlainText("save as");
}

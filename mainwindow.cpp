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


bool MainWindow::isModified() const
{
    return ui->editBox->document()->isModified();
}

void MainWindow::openFile(const QString &path)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, windowTitle(),
                             tr("无法打开文件 file %1: %2").arg(
                                 QDir::toNativeSeparators(path), f.errorString()));
        return;
    }
    mdFilePath = path;
    ui->editBox->setPlainText(f.readAll());
}

void MainWindow::on_actionOpen_File_triggered()
{
  if (isModified()) {
      QMessageBox::StandardButton button = QMessageBox::question(this, windowTitle(),
                           tr("你有未保存的改动，是否仍要打开文档？"));
      if (button != QMessageBox::Yes)
          return;
  }

  QString path = QFileDialog::getOpenFileName(this,
      tr("打开Markdown文件"), "", tr("Markdown文件 (*.md)"));
  if (path.isEmpty())
      return;

  openFile(path);
//    ui->editBox->setPlainText("open" + mdContent.mdCodeText);
}

void MainWindow::on_actionNew_File_triggered()
{
  if (isModified()) {
      QMessageBox::StandardButton button = QMessageBox::question(this, windowTitle(),
                           tr("你有未保存的改动，是否仍要创建新文档？"));
      if (button != QMessageBox::Yes)
          return;
  }

  mdFilePath.clear();
  ui->editBox->setPlainText(tr("## 新文档"));
  ui->editBox->document()->setModified(false);
//    ui->editBox->setPlainText("new");
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
                           tr("无法写入文件 %1: %2").arg(
                               QDir::toNativeSeparators(mdFilePath), f.errorString()));
      return;
  }
  QTextStream str(&f);
  str << ui->editBox->toPlainText();

  ui->editBox->document()->setModified(false);
//    ui->editBox->setPlainText("save");
}

void MainWindow::on_actionSave_As_triggered()
{
  QString path = QFileDialog::getSaveFileName(this,
      tr("保存Markdown文件"), "", tr("Markdown文件 (*.md, *.markdown)"));
  if (path.isEmpty())
      return;
  mdFilePath = path;
  on_actionSave_File_triggered();
//    ui->editBox->setPlainText("save as");
}

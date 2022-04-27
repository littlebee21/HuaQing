#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "finddialog.h"
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->aboutAction, &QAction::triggered, this, &MainWindow::slotShowAboutDlg);
    connect(ui->openAction, &QAction::triggered, this, &MainWindow::slotOpenDlg);
    connect(ui->findAction, &QAction::triggered, this, &MainWindow::slotShowFindDlg);
}

void MainWindow::slotShowAboutDlg(){
    AboutDialog aboutDlg;
    aboutDlg.exec();
}

void MainWindow::slotOpenDlg(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "C:/users/Administrator/Desktop",
                                                    tr("Images (*.txt)"));
    if(fileName.isEmpty()){
        qDebug() << "fileName is Empty";
        return;
    }

    QFile *pFile = new QFile(fileName);

    if(!pFile->open(QIODevice::ReadOnly)){
        qDebug() << "openFile failed";
        return;
    }

    ui->textEdit->clear();
    QTextStream stream(pFile);

    // 读完文件结束
    while(!pFile->atEnd()){
        ui->textEdit->append(pFile->readLine());
    }

    m_strFileText = ui->textEdit->document()->toPlainText();
}

void MainWindow::slotShowFindDlg(){
    FindDialog finddlg;
    finddlg.exec();
}

MainWindow::~MainWindow(){
    delete ui;
}

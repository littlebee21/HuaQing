#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog){
    ui->setupUi(this);
    // 去掉QDialog的问号按钮
    setWindowTitle("关于\"记事本\"");
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::Drawer);
    connect(ui->okBtn, &QPushButton::clicked, this, &AboutDialog::closeAboutDlg);
}

void AboutDialog::closeAboutDlg(){
    close();
}

AboutDialog::~AboutDialog(){
    delete ui;
}

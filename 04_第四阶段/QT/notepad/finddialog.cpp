#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog){
    ui->setupUi(this);
    // 去掉QDialog的问号按钮
    setWindowTitle("查找");
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::Drawer);
    connect(ui->findLineEdit, SIGNAL(textChanged(QString)), this, SLOT(slotContentChanged()));
}

void FindDialog::focusInEvent(QFocusEvent *event){
    Q_UNUSED(event)
    //    if(ui->findLineEdit->text().isEmpty()){
    //        ui->findBtn->setDisabled(true);     // 禁止点击
    //    }
    //    else{
    //        ui->findBtn->setDisabled(false);
    //    }
}

void FindDialog::slotFindContent(){
    bool bUp = ui->upRadioBtn->isChecked();
    // bool bDown = ui->downRadioBtn->isChecked();
    bool bDaxiaoxie = ui->checkBox_1->isChecked();
    bool bXunhuan = ui->checkBox_2->isChecked();

    QString strContent = ui->findLineEdit->text();
    if(strContent.isEmpty()){
        return;
    }

    emit signalFind(strContent, bUp);
}

void FindDialog::slotContentChanged(){
    if(ui->findLineEdit->text().trimmed().isEmpty()){
        ui->findBtn->setDisabled(true);     // 禁止点击
    }
    else{
        ui->findBtn->setDisabled(false);
    }
}

FindDialog::~FindDialog(){
    delete ui;
}

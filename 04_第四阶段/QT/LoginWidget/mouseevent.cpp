#include "mouseevent.h"
#include <QMessageBox>

MouseEvent::MouseEvent(QWidget *parent) : QWidget(parent){

}

void MouseEvent::mousePressEvent(QMouseEvent *event){
    // 鼠标左键
    if(event->button() == Qt::LeftButton){
        m_point = event->pos();
        m_bPressed = true;
    }
}

void MouseEvent::mouseReleaseEvent(QMouseEvent *){
    m_bPressed = false;
}

void MouseEvent::mouseMoveEvent(QMouseEvent *event){
    if(m_bPressed){
        move(pos() + event->pos() - m_point);
    }
}

void MouseEvent::closeEvent(QCloseEvent *event){
    QMessageBox msgBox;
    msgBox.setText("是否关闭对话框？");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    switch (msgBox.exec()) {
    case QMessageBox::Yes:
        event->accept();    // close
        break;
    case QMessageBox::No:
        event->ignore();    // 取消关闭
        break;
    default:
        break;
    }
}

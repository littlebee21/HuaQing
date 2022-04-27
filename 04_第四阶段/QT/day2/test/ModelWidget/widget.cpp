#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_pSonWidget(nullptr)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::slotCreateNewWidget);
}

void Widget::slotCreateNewWidget()
{
    if(m_pSonWidget)        // 只能创建一个子窗口
        return;
    m_pSonWidget = new SonWidget;
    // m_pSonWidget->setWindowModality(Qt::ApplicationModal);     // 模态 方法1
    // m_pSonWidget->setAttribute(Qt::WA_ShowModal);              // 模态 方法2
    m_pSonWidget->show();
}

Widget::~Widget()
{
    delete ui;
    delete m_pSonWidget;
    m_pSonWidget = nullptr;
}

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 初始化slider
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setRange(0, 100);
    ui->horizontalSlider->setTickInterval(5);
    ui->horizontalSlider->setTickPosition(QSlider::TicksAbove);
    ui->horizontalSlider->setSingleStep(5); // 设置步长
    // 初始化spinbox
    ui->spinBox->setRange(0, 100);
    ui->spinBox->setSingleStep(5);
    ui->spinBox->setValue(0);
    // ui->spinBox->setWrapping(true); // 设置循环
    // ui->spinBox->setPrefix("<");    // 设置前缀
    // ui->spinBox->setSuffix(">");    // 设置后缀

    // 通过spinbox来控制slider
    connect(ui->spinBox, SIGNAL(valueChanged(int)),
            ui->horizontalSlider, SLOT(setValue(int)));

    // 通过slider来控制spinbox
    connect(ui->horizontalSlider, &QSlider::valueChanged,
            ui->spinBox, &QSpinBox::setValue);
}

Widget::~Widget()
{
    delete ui;
}

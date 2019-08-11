#include "smallwidget.h"
#include <QSpinBox>    // 选择框
#include <QSlider>    // 滑块
#include <QHBoxLayout>    // 水平布局

SmallWidget::SmallWidget(QWidget *parent) : QWidget(parent)
{
    QSpinBox *spin = new QSpinBox(this);
    QSlider *slider = new QSlider(Qt::Horizontal ,this);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout -> addWidget(spin);
    hLayout -> addWidget(slider);
    // 如果初始化时候没有定义父控件，则需要加下面的语句
    // setLayout(hLayout);

    // 强制类型转换
    connect(spin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),slider,&QSlider::setValue);
    connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);
}

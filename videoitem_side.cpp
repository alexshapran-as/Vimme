#include "videoitem_side.h"
#include "ui_videoitem_side.h"

VideoItem_side::VideoItem_side(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoItem_side)
{
    ui->setupUi(this);
}

VideoItem_side::~VideoItem_side()
{
    delete ui;
}

QLabel *VideoItem_side::get_label_from_vi(unsigned int label_index)
{
    if (label_index == 1)
    {
        return ui->label;
    }
    else if (label_index == 2)
    {
        return ui->label_2;
    }
    else if (label_index == 3)
    {
        return ui->label_3;
    }
}

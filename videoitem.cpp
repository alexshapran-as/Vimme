#include "videoitem.h"
#include "ui_videoitem.h"

VideoItem::VideoItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoItem)
{
    ui->setupUi(this);
}

VideoItem::~VideoItem()
{
    delete ui;
}

QLabel *VideoItem::get_label_from_vi(unsigned int label_index)
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

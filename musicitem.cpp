#include "musicitem.h"
#include "ui_musicitem.h"

MusicItem::MusicItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicItem)
{
    ui->setupUi(this);
}

MusicItem::~MusicItem()
{
    delete ui;
}

QLabel * MusicItem::get_label_from_mi(unsigned int label_index)
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

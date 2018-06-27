#include "moreitem.h"
#include "ui_moreitem.h"

MoreItem::MoreItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MoreItem)
{
    ui->setupUi(this);
}

MoreItem::~MoreItem()
{
    delete ui;
}

QLabel *MoreItem::get_label_from_morei()
{
    return ui->label;
}

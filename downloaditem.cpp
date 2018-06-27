#include "downloaditem.h"
#include "ui_downloaditem.h"

downloaditem::downloaditem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::downloaditem)
{
    ui->setupUi(this);
}

downloaditem::~downloaditem()
{
    delete ui;
}

QLabel * downloaditem::get_label_from_di(unsigned int label_index)
{
    if (label_index == 1)
    {
        return ui->label_1;
    }
    else if (label_index == 2)
    {
        return ui->label_2;
    }
}

QProgressBar *downloaditem::get_progressbar_from_di()
{
    return ui->progressBar;
}

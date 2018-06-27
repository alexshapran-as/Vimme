#include "video.h"
#include "ui_video.h"

Video::Video(QVideoWidget * video_widget, QWidget *parent) :
    video_widget(video_widget), QWidget(parent),
    ui(new Ui::Video)
{
    ui->setupUi(this);
    ui->gridLayout->addWidget(video_widget);
    video_widget->show();
}

Video::~Video()
{
    delete ui;
}

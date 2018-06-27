#include "authorization_window.h"
#include "ui_authorization_window.h"

unsigned int auth_id;

Authorization_window::Authorization_window(Vimme * vimme_window, Video_window * video_window, QWidget *parent) :
    vimme_window(vimme_window), video_window(video_window), QMainWindow(parent),
    ui(new Ui::Authorization_window)
{
    ui->setupUi(this);
    //vimme_window = parent;
}

Authorization_window::~Authorization_window()
{
    delete ui;
    delete vimme_window;
    delete video_window;
}

// Авторизация
void Authorization_window::on_pushButton_clicked()
{
    auth_id = ui->lineEdit->text().toInt();
    if (vimme_window != 0)
    {
        vimme_window->show();
        vimme_window->audio_starter();
    }
    if (video_window != 0)
    {
        video_window->show();
        video_window->video_starter();
    }
    this->close();
}

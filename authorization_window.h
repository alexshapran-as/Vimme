#ifndef AUTHORIZATION_WINDOW_H
#define AUTHORIZATION_WINDOW_H

#include <QMainWindow>
#include <QVector>
#include "vimme.h"
#include "video_window.h"

class Vimme;
class Video_window;

namespace Ui {
class Authorization_window;
}

class Authorization_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Authorization_window(Vimme * vimme_window = 0, Video_window * video_window = 0, QWidget *parent = 0);
    ~Authorization_window();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Authorization_window *ui;
    Vimme * vimme_window;
    Video_window * video_window;
};

#endif // AUTHORIZATION_WINDOW_H

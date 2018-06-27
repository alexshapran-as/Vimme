#ifndef DOWNLOADS_WINDOW_H
#define DOWNLOADS_WINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QProgressBar>
#include <QMouseEvent>
#include <QMainWindow>
#include <QDesktopServices>
#include <QGraphicsDropShadowEffect>
#include "vimme.h"
#include "downloaditem.h"
#include "video_window_widget.h"

using namespace Network;
class Vimme;
class downloaditem;
class Video_window_widget;

namespace Ui {
class Downloads_window;
}

class Downloads_window : public QMainWindow
{
    Q_OBJECT

public:
    Vimme * main_vimme;
    explicit Downloads_window(Vimme * main_vimme = 0);
    ~Downloads_window();
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent();
    QListWidget * get_listwidget_from_dw();
    QListWidget * get_listwidget_2_from_dw();


private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_video_itemClicked(QListWidgetItem *item);

private:
    Ui::Downloads_window *ui;
    QPoint mpos;
};

#endif // DOWNLOADS_WINDOW_H

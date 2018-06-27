#ifndef VIDEO_WINDOW_WIDGET_H
#define VIDEO_WINDOW_WIDGET_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QtConcurrent/QtConcurrentRun>
#include <QLineEdit>
#include <QListWidget>
#include "video_window.h"
#include "downloader.h"
#include "downloaditem.h"
#include "downloads_window.h"

class Video_window;
class Downloader;
class downloaditem;
class Downloads_window;

namespace Ui {
class Video_window_widget;
}

class Video_window_widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Video_window_widget(QMediaPlayer * player, QVideoWidget * video_widget, Video_window * video_window_parent, Downloads_window * downloads_window);
    ~Video_window_widget();
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent();
    QLineEdit * get_lineEdit_3();
    QListWidget * get_listWidget();

public slots:
    void on_duration_changed(qint64 position);
    void on_duration_changing(qint64 position);

private slots:
    void on_pushButton_7_clicked();
    void on_volume_changed(qint64 position);
    void mediaPlayerError(QMediaPlayer::Error err);

    void on_pushButton_2_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_3_clicked();
    //void download_video();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::Video_window_widget *ui;
    QPoint mpos;
    QMediaPlayer * player;
    QVideoWidget * video_widget;
    Video_window * video_window_parent;
    QString file_name;
    QString urls;
    Downloader * video_downloader;
    Downloads_window * downloads_window;
};

#endif // VIDEO_WINDOW_WIDGET_H

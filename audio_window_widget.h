#ifndef AUDIO_WINDOW_WIDGET_H
#define AUDIO_WINDOW_WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QJsonObject>
#include <QMainWindow>
#include "vimme.h"

using namespace Network;
class Vimme;

namespace Ui {
class Audio_window_widget;
}

class Audio_window_widget : public QWidget
{
    Q_OBJECT

public:
    Vimme * main_vimme;
    explicit Audio_window_widget(/*QWidget * parent = 0,*/ Vimme * main_vimme = 0, QMediaPlayer * player = 0);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent();
    QPushButton * get_play_pause_button();
    QLineEdit * get_time_1_lineEdit();
    QLineEdit * get_time_2_lineEdit();
    QLineEdit * get_audio_name_lineEdit();
    QSlider * get_horizontalSlider();
    void refresh_audio_name_lineEdit();
    ~Audio_window_widget();

public slots:
    void on_duration_changed(qint64 position);
    void on_duration_changing(qint64 position);

private slots:
    void on_pushButton_close_widget_clicked();
    void on_pushButton_on_off_clicked();
    void on_pushButton_next_audio_clicked();
    void on_pushButton_previous_audio_clicked();
    void on_pushButton_download_audio_clicked();

    void on_horizontalSlider_sliderMoved(int position);

public:
    QMediaPlayer * player;

private:
    Ui::Audio_window_widget * ui;
    QPoint mpos;
};

#endif // AUDIO_WINDOW_WIDGET_H

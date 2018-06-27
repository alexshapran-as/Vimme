#ifndef VIMME_H
#define VIMME_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QVector>
#include <QFileDialog>
#include <QProgressBar>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QListWidgetItem>
#include <QToolButton>
#include <QCompleter>
#include <QtAlgorithms>
#include <QRegExp>
#include <QListWidget>
#include <QMovie>
#include <QLabel>
#include <thread>
#include "request.h"
#include "requestsender.h"
#include "downloader.h"
#include "downloads_window.h"
#include "authorization_window.h"
#include "video_window.h"
#include "musicitem.h"
#include "audio_window_widget.h"
#include "downloaditem.h"
#include "up_button.h"

class Downloader;
class Downloads_window;
class Video_window;
class Authorization_window;

namespace Ui {
class Vimme;
}

using namespace Network;
class Audio_window_widget;

class Vimme : public QMainWindow
{
    Q_OBJECT

public:
    explicit Vimme(QWidget *parent = 0);
    ~Vimme();
    void parser(QByteArray &data);
    void generate_sig(QString & sig);
    QSlider * get_horisontalSlider_from_vimme();
    void audio_starter();

public slots:
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_3_clicked();
    void on_duration_changed(qint64 position);
    void on_duration_changing(qint64 position);
    QListWidget * get_listWidget_from_vimme();
    QLineEdit * get_lineEdit_5_from_vimme();
    QLineEdit * get_lineEdit_4_from_vimme();

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void on_pushButton_4_clicked();
    void on_horizontalSlider_2_sliderMoved(int position);
    void on_horizontalSlider_sliderMoved(int position);
    void on_volume_changed(qint64 position);
    void mediaPlayerError(QMediaPlayer::Error err);
    void on_listWidget_itemClicked();
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_14_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_11_clicked();
    // Процедуры для перетаскивания окна
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent();
    void on_pushButton_15_clicked();
    void on_pushButton_13_clicked();
    void on_comboBox_currentIndexChanged(int index);
    // Событие прокручивания колесика мыши
    void wheelEvent( QWheelEvent* e );

private:
    Ui::Vimme *ui;
    // Выражение для исключения из json-а
    const QString j_parse_start = "Site.APIRequestCallbacks[2](";
    // Диапозон индексов для выбора значения sig в конце запроса на поиск
    unsigned int low = {1};
    unsigned int high = {31};
    QString sig;
    QString file_name;
    QString urls;
    Downloader * audio_downloader;
    QPoint mouse_position;
    Downloads_window * downloads_window;
    Authorization_window * authorization_window;
    Video_window * video_window;
    Audio_window_widget * audio_window_widget;
    Up_button * up_button;
    QString all_music_or_artist = "0";
    QStringList choice_for_search;
    // Поле - переменная для гиф-анимации
    QMovie cat_loading;

public:
    // Массив данных о песнях
    QJsonArray audios;
    QMediaPlayer * player;
};

#endif // VIMME_H

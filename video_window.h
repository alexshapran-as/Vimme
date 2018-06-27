#ifndef VIDEO_WINDOW_H
#define VIDEO_WINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QListWidgetItem>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMovie>
#include <QListWidget>
#include "request.h"
#include "requestsender.h"
#include "authorization_window.h"
#include "video_window_widget.h"
#include "vimme.h"
#include "downloads_window.h"
#include "authorization_window.h"
#include "videoitem.h"
#include "videoitem_side.h"
//#include "moreitem.h"

class Vimme;
class Downloads_window;
class Authorization_window;
class VideoItem;
class VideoItem_side;
//class MoreItem;

namespace Ui {
class Video_window;
}

using namespace Network;

class Video_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Video_window(Vimme * vimme_window = 0, Downloads_window * downloads_window = 0);
    ~Video_window();
    void video_starter();
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent();
    void generate_video_sig(QString & sig);
    QListWidget * get_list_widget();

private:
    unsigned int parser(QString & j_search_result);
    void video_by_url();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_15_clicked();
    void on_lineEdit_video_name_returnPressed();
    void on_listWidget_itemEntered(QListWidgetItem *item);
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_18_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

public slots:
    void on_listWidget_itemClicked(QListWidgetItem * item);

public:
    QMediaPlayer * player;
    QVideoWidget * vid_widget;
    QJsonArray videos;
    QVector<QString> urls;
private:
    Ui::Video_window *ui;
    Vimme * vimme_window;
    Downloads_window * downloads_window;
    Authorization_window * authorization_window;
    unsigned int low = {1};
    unsigned int high = {31};
    QString sig;
    QString str_for_search_by_url;
    QString first_parse = "<source src=\"";
    QString end_parse = "\"video/mp4\" />\n";
    QString str_for_size = "type=";
    QPoint mpos;
    // Поле - переменная для гиф-анимации
    QMovie cat_loading;
    unsigned int last_item = {1};
    unsigned int last_item_2 = {2};
};

#endif // VIDEO_WINDOW_H

#include "video_window.h"
#include "ui_video_window.h"

extern unsigned int auth_id;
QVector<QString> all_urls;
bool menu_was_opened_vw = {false};
//unsigned int index = {0};
//unsigned int index_2 = {0};
//bool new_search = {true};
bool search_by_url = {false};

Video_window::Video_window(Vimme * vimme_window, Downloads_window * downloads_window/*, Authorization_window *authorization_window*/) :
    vimme_window(vimme_window),
    downloads_window(downloads_window),
//    authorization_window(authorization_window),
    ui(new Ui::Video_window)
{
    ui->setupUi(this);
    // Настройка UI
    this->setWindowFlags(Qt::FramelessWindowHint);      // Отключаем оформление окна
    this->setAttribute(Qt::WA_TranslucentBackground);   // Делаем фон главного виджета прозрачным
    this->setMouseTracking(true);   // Включаем отслеживание курсора без нажатых кнопокы

    // Создаём эффект тени
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10); // Устанавливаем радиус размытия
    shadowEffect->setOffset(5);     // Устанавливаем смещение тени
    ui->Widget_interface->setGraphicsEffect(shadowEffect);   // Устанавливаем эффект тени на окно
    ui->Widget_interface->layout()->setMargin(5);            // Устанавливаем размер полей
    ui->Widget_interface->layout()->setSpacing(5);
    ui->pushButton_10->hide();
    ui->burger_menu->hide();
    ui->lineEdit_video_name->setPlaceholderText("Введите название видеозаписи для поиска или ссылку на видео для воспроизведения:)");
    ui->listWidget->clear();
    video_starter();
}

Video_window::~Video_window()
{
    delete ui;
    delete player;
}

void Video_window::video_starter()
{
    ui->listWidget->clear();
    QLabel * cat_label = new QLabel(this);
    cat_label->setGeometry(/*ui->listWidget*/ui->centralwidget->height() / 2, /*ui->listWidget*/ui->centralwidget->width() / 4, 350, 350);
    cat_loading.setFileName("://img/cat_loading.gif");
    cat_loading.setSpeed(1000000);
    cat_label->setMovie(&cat_loading);
    cat_label->show();
    cat_loading.start();
    Request request_;
    RequestSender request_sender_;
    QString address;
    if (auth_id != 0)
    {
        address = "https://api.vk.com/method/video.get?owner_id=" + QString::number(auth_id) + "&count=200&offset=0&access_token=167bfe8dc246bca0c50ae358b47a631eddb348dd1dc857c0597e3c9d40d8fd8cc43403f7922acb6da69ea&extended=1&v=5.74";
    }
    else
    {
        address = "https://api.vk.com/method/video.get?owner_id=145136254&count=200&offset=0&access_token=167bfe8dc246bca0c50ae358b47a631eddb348dd1dc857c0597e3c9d40d8fd8cc43403f7922acb6da69ea&extended=1&v=5.74";
    }
    request_.setAddress(address);
    QByteArray data = request_sender_.get(request_);
    QString j_search_result = QString::fromStdString(data.toStdString());
    data = j_search_result.toUtf8();
    QJsonParseError * err = new QJsonParseError();
    QJsonDocument j_document = QJsonDocument::fromJson(data, err);
    if (err->error != 0)
    {
        qDebug() << err->errorString();
        return;
    }
    if (j_document.isNull() || j_document.isEmpty())
    {
        ui->listWidget->addItem("Ничего не нашлось :( Повторите попытку позже");
        return;
    }
    if (j_document.isObject())
    {
        QJsonObject j_object = j_document.object();
        videos = j_object["response"].toObject()["items"].toArray();
    }
    cat_loading.stop();
    delete cat_label;
    foreach (const QJsonValue & value, videos)
    {
        QJsonObject obj = value.toObject();
        unsigned int duration = + obj["duration"].toInt();
        unsigned int minutes = duration / 60;
        unsigned int seconds = duration - ( minutes * 60 );
        VideoItem * video_item = new VideoItem();
        QString video_name = obj["title"].toString();
        if (video_name.size() > 75)
        {
            video_name.truncate(75);
            video_name.push_back("...");
        }
        video_item->get_label_from_vi(1)->setText(video_name + "\n" + obj["artist"].toString());
        video_item->get_label_from_vi(2)->setText(QString::number(minutes) + ":" + QString::number(seconds));
        QString img_address = obj["photo_130"].toString();
        Request request_;
        RequestSender request_sender_;
        request_.setAddress(img_address);
        QByteArray data = request_sender_.get(request_);
        QImage image;
        if (data.isEmpty())
        {
            video_item->get_label_from_vi(3)->setStyleSheet("QLabel#label_3 {image: url(://img/music_ico.png);}");
        }
        else
        {
            image = QImage::fromData(data);
            image = image.scaled(420, 320);
            video_item->get_label_from_vi(3)->setPixmap(QPixmap::fromImage(image));
        }
        QListWidgetItem * item = new QListWidgetItem(ui->listWidget);
        item->setSizeHint(video_item->sizeHint());
        ui->listWidget->setItemWidget(item, video_item);
//        ++index;
    }
//    MoreItem * more_item = new MoreItem();
//    //more_item->get_label_from_morei()->setGeometry(0, 0, 500, 500);
//    //more_item->get_label_from_morei()->setStyleSheet("QLabel#label {image: url(://img/more.png);}");
//    QListWidgetItem * item = new QListWidgetItem(ui->listWidget, last_item);
//    item->setSizeHint(more_item->sizeHint());
//    ui->listWidget->setItemWidget(item, more_item);
}

void Video_window::mousePressEvent(QMouseEvent *event)
{
    // Запоминаем позицию при нажатии кнопки мыши
    mpos = event->pos();
}

void Video_window::mouseMoveEvent(QMouseEvent *event)
{
    if (mpos.x() >= 0 && event->buttons() && Qt::LeftButton)
    {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

void Video_window::mouseReleaseEvent()
{
    // Очищаем старое значение позиции нажатия мыши
    mpos = QPoint(-1, -1);
}

unsigned int Video_window::parser(QString & j_search_result)
{
    j_search_result.remove(0, j_search_result.indexOf(first_parse));
    j_search_result.chop(j_search_result.size() - j_search_result.indexOf(end_parse));
    unsigned int count_of_urls = j_search_result.count(str_for_size);
    return count_of_urls;
}

void Video_window::on_listWidget_itemClicked(QListWidgetItem * item)
{
    // Работа с добавлением видео
//    if (item->type() == last_item)
//    {
//        ui->listWidget->removeItemWidget(item);
//        video_starter();
//        return;
//    }
//    if (item->type() == last_item_2)
//    {
//        ui->listWidget->removeItemWidget(item);
//        new_search = {false};
//        on_pushButton_clicked();
//        return;
//    }
    urls.clear();
    Request request_;
    RequestSender request_sender_;
    QJsonObject obj = videos[ui->listWidget->currentRow()].toObject();
    request_.setAddress(obj["player"].toString());
    QByteArray data = request_sender_.get(request_);
    QString j_search_result = QString::fromStdString(data.toStdString());
    unsigned int size = parser(j_search_result);
    QString temp = j_search_result;
    for (unsigned int i = {0}; i < size; ++i)
    {
        temp.remove(0, temp.indexOf("https"));
        temp.chop(temp.size() - temp.indexOf("?extra="));
        //qDebug() << temp;
        urls.push_back(temp);
        temp.clear();
        temp = j_search_result;
        temp.remove(0,temp.indexOf("type="));
    }
    player = new QMediaPlayer;
    vid_widget = new QVideoWidget();
    player->setVideoOutput(vid_widget);
    if (urls.isEmpty())
    {
        QString address = "https://m.vk.com/video";
        QString temp = obj["player"].toString();
        temp.remove(0, temp.indexOf("=") + 1);
        temp.replace("&id=", "_");
        temp.chop(temp.size() - temp.indexOf("&hash"));
        address.push_back(temp);
        qDebug() << address;
        request_.setAddress(address);
        QByteArray data = request_sender_.get(request_);
        QString j_search_result = QString::fromStdString(data.toStdString());
        QString temp_str = j_search_result;
        temp_str.remove(0, temp_str.indexOf("https://cs"));
        temp_str.chop(temp_str.size() - temp_str.indexOf("vv_img"));
        int count = temp_str.count("https://cs");
        for (unsigned int i = {0}; i < count; ++i)
        {
            j_search_result.remove(0, j_search_result.indexOf("https://cs"));
            QString temp = j_search_result;
            temp.remove(0, j_search_result.indexOf("?extra"));
            j_search_result.chop(j_search_result.size() - j_search_result.indexOf("?extra"));
            qDebug() << "RESULT = " << j_search_result;
            if (j_search_result.isEmpty())
            {
                QMessageBox::critical(this, "Ошибка!", "Не все видео пока работают");
                return;
            }
            urls.push_back(j_search_result);
            qSwap(temp, j_search_result);
        }
    }
    QUrl url(urls[0]);
    player->setMedia(url);
    vid_widget->setGeometry(100, 100, 1166, 664);
    Video_window_widget * video_window_widget = new Video_window_widget(player,vid_widget, this, downloads_window);
    video_window_widget->get_lineEdit_3()->setText(obj["title"].toString());
    video_window_widget->show();
    player->play();
    foreach (const QJsonValue & value, videos)
    {
        QJsonObject obj = value.toObject();
        unsigned int duration = + obj["duration"].toInt();
        unsigned int minutes = duration / 60;
        unsigned int seconds = duration - ( minutes * 60 );
        VideoItem_side * video_item = new VideoItem_side(video_window_widget->get_listWidget());
        QString video_name = obj["title"].toString();
        if (video_name.size() > 15)
        {
            video_name.truncate(15);
            video_name.push_back("...");
        }
        video_item->get_label_from_vi(1)->setText(video_name + "\n" + obj["artist"].toString());
        video_item->get_label_from_vi(2)->setText(QString::number(minutes) + ":" + QString::number(seconds));
        QString img_address = obj["photo_130"].toString();
        Request request_;
        RequestSender request_sender_;
        request_.setAddress(img_address);
        QByteArray data = request_sender_.get(request_);
        QImage image;
        if (data.isEmpty())
        {
            video_item->get_label_from_vi(3)->setStyleSheet("QLabel#label_3 {image: url(://img/music_ico.png);}");
        }
        else
        {
            image = QImage::fromData(data);
            image = image.scaled(130, 130);
            video_item->get_label_from_vi(3)->setPixmap(QPixmap::fromImage(image));
        }
        QListWidgetItem * item = new QListWidgetItem(video_window_widget->get_listWidget());
        item->setSizeHint(video_item->sizeHint());
        video_window_widget->get_listWidget()->setItemWidget(item, video_item);
    }
}

void Video_window::video_by_url()
{
    ui->listWidget->clear();
    urls.clear();
    str_for_search_by_url = ui->lineEdit_video_name->text();
    str_for_search_by_url.remove(0, str_for_search_by_url.indexOf("video-"));
    str_for_search_by_url.remove("video");
    if (str_for_search_by_url.indexOf("%") != -1)
    {
        str_for_search_by_url.chop(str_for_search_by_url.size() - str_for_search_by_url.indexOf("%"));
    }
    QString address = "https://m.vk.com/video" + str_for_search_by_url;
    Request request_;
    RequestSender request_sender_;
    request_.setAddress(address);
    QByteArray data = request_sender_.get(request_);
    QString j_search_result = QString::fromStdString(data.toStdString());
    j_search_result.remove(0, j_search_result.indexOf("https://cs"));
    j_search_result.chop(j_search_result.size() - j_search_result.indexOf("?extra"));
    if (j_search_result.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка!", "Не все видео пока работают");
        return;
    }
    urls.push_back(j_search_result);
    player = new QMediaPlayer;
    vid_widget = new QVideoWidget();
    player->setVideoOutput(vid_widget);
    QUrl url(urls[0]);
    player->setMedia(url);
    vid_widget->setGeometry(100, 100, 640, 360);
    Video_window_widget * video_window_widget = new Video_window_widget(player,vid_widget, this, downloads_window);
    video_window_widget->show();
    player->play();
}

void Video_window::on_pushButton_clicked()
{
//    if (new_search == true)
//    {
//        ui->listWidget->clear();
//        while (videos.count())
//        {
//            videos.pop_back();
//        }
//    }
    ui->listWidget->clear();
    if (search_by_url == true)
    {
       ui->listWidget->clear();
       video_by_url();
       return;
    }
    // Анимированная загрузка
    QLabel * cat_label = new QLabel(this);
    cat_label->setGeometry(/*ui->listWidget*/ui->centralwidget->height() / 2, /*ui->listWidget*/ui->centralwidget->width() / 4, 350, 350);
    cat_loading.setFileName("://img/cat_loading.gif");
    cat_loading.setSpeed(1000000);
    cat_label->setMovie(&cat_loading);
    cat_label->show();
    cat_loading.start();
    Request request_;
    RequestSender request_sender_;
    QString video_search_name = ui->lineEdit_video_name->text();
    generate_video_sig(sig);
//    QString address = "https://api.vk.com/method/execute?code=return%20API.video.search(%7Bq%3A\"" + video_search_name + "\"%2Csort%3A\"0\"%2Chd%3A\"0\"%2Cadult%3A\"1\"%2Cfilters%3A\"0\"%2Ccount%3A\"100\"%2Coffset%3A\"" + QString::number(index_2) + "\"%2Cv%3A\"5.18\"%7D)%3B&access_token=29cb9c5734cdfb32e5412387200313a62e732aba4bbc48f84920667e703d2c113b4402a10e9cc5a78589f&v=4.99&lang=ru&random=0.5648019668732438&https=1&callback=Site.APIRequestCallbacks%5B330%5D&sig=a14db0e1f13944e60b64959d8331ab39";
    QString address = "https://api.vk.com/method/execute?code=return%20API.video.search(%7Bq%3A\"" + video_search_name + "\"%2Csort%3A\"0\"%2Chd%3A\"0\"%2Cadult%3A\"1\"%2Cfilters%3A\"0\"%2Ccount%3A\"200\"%2Coffset%3A\"0\"%2Cv%3A\"5.18\"%7D)%3B&access_token=29cb9c5734cdfb32e5412387200313a62e732aba4bbc48f84920667e703d2c113b4402a10e9cc5a78589f&v=4.99&lang=ru&random=0.5648019668732438&https=1&callback=Site.APIRequestCallbacks%5B330%5D&sig=" + sig;
    request_.setAddress(address);
    QByteArray data = request_sender_.get(request_);
    QString j_search_result = QString::fromStdString(data.toStdString());
    j_search_result.remove("Site.APIRequestCallbacks[330](");
    j_search_result.chop(2);
    data = j_search_result.toUtf8();
    QJsonParseError * err = new QJsonParseError();
    QJsonDocument j_document = QJsonDocument::fromJson(data, err);
    if (err->error != 0)
    {
        qDebug() << err->errorString();
        return;
    }
    if (j_document.isNull() || j_document.isEmpty())
    {
        ui->listWidget->addItem("Ничего не нашлось :( Повторите попытку позже");
        return;
    }
    if (j_document.isObject())
    {
        QJsonObject j_object = j_document.object();
        videos = j_object["response"].toObject()["items"].toArray();
//        if (new_search == true)
//        {
//            videos = j_object["response"].toObject()["items"].toArray();
//        }
//        else
//        {
//            more_videos = videos;
//            videos = j_object["response"].toObject()["items"].toArray();
//        }
    }
    cat_loading.stop();
    delete cat_label;
    foreach (const QJsonValue & value, videos)
    {
        QJsonObject obj = value.toObject();
        unsigned int duration = + obj["duration"].toInt();
        unsigned int minutes = duration / 60;
        unsigned int seconds = duration - ( minutes * 60 );
        VideoItem * video_item = new VideoItem();
        QString video_name = obj["title"].toString();
        if (video_name.size() > 75)
        {
            video_name.truncate(75);
            video_name.push_back("...");
        }
        video_item->get_label_from_vi(1)->setText(video_name + "\n" + obj["artist"].toString());
        video_item->get_label_from_vi(2)->setText(QString::number(minutes) + ":" + QString::number(seconds));
        QString img_address = obj["photo_130"].toString();
        Request request_;
        RequestSender request_sender_;
        request_.setAddress(img_address);
        QByteArray data = request_sender_.get(request_);
        QImage image;
        if (data.isEmpty())
        {
            video_item->get_label_from_vi(3)->setStyleSheet("QLabel#label_3 {image: url(://img/music_ico.png);}");
        }
        else
        {
            image = QImage::fromData(data);
            image = image.scaled(420, 420);
            video_item->get_label_from_vi(3)->setPixmap(QPixmap::fromImage(image));
        }
        QListWidgetItem * item = new QListWidgetItem(ui->listWidget);
        item->setSizeHint(video_item->sizeHint());
        ui->listWidget->setItemWidget(item, video_item);
//        ++index_2;
    }
//    if (new_search == false)
//    {
//        foreach (const QJsonValue & value, more_videos)
//        {
//            videos.push_back(value);
//        }
//    }
//    MoreItem * more_item = new MoreItem();
//    //more_item->get_label_from_morei()->setGeometry(0, 0, 200, 200);
//    //more_item->get_label_from_morei()->setStyleSheet("QLabel#label {image: url(://img/more.png);}");
//    QListWidgetItem * item = new QListWidgetItem(ui->listWidget, last_item_2);
//    item->setSizeHint(more_item->sizeHint());
//    ui->listWidget->setItemWidget(item, more_item);
//    new_search = {true};
}

// Закрыть окно
void Video_window::on_pushButton_7_clicked()
{
    this->close();
}

// Свернуть окно
void Video_window::on_pushButton_18_clicked()
{
    this->showMinimized();
}

// Уменьшить окно
void Video_window::on_pushButton_10_clicked()
{
    ui->pushButton_10->hide();
    ui->pushButton_9->show();
    this->showNormal();
}

// Развернуть окно
void Video_window::on_pushButton_9_clicked()
{
    ui->pushButton_9->hide();
    ui->pushButton_10->show();
    this->showFullScreen();
}

void Video_window::on_pushButton_14_clicked()
{
    if (menu_was_opened_vw)
    {
        ui->burger_menu->hide();
        ui->pushButton_14->setStyleSheet("QPushButton#pushButton_14 {"
                                         "image: url(://img/burger_menu_gray.png);"
                                         "background-color: rgb(54, 57, 62);"
                                         "border-radius:20px; "
                                         "border: 6px; }"
                                         "QPushButton#pushButton_14:hover {"
                                         "image: url(://img/burger_menu.png);"
                                         "background-color: rgb(54, 57, 62);"
                                         "border-radius:20px; "
                                         "border: 6px;"
                                         "}");
        menu_was_opened_vw = false;
        return;
    }
    ui->pushButton_14->setStyleSheet("image: url(:/img/close.png);"
                                     "background-color: rgb(54, 57, 62);"
                                     "border-radius:20px;"
                                     "border: 6px;");
    ui->burger_menu->show();
    menu_was_opened_vw = true;
}

void Video_window::on_pushButton_12_clicked()
{
    vimme_window->show();
    this->close();
}

void Video_window::on_pushButton_11_clicked()
{
    downloads_window->show();
    this->close();
}

void Video_window::on_pushButton_15_clicked()
{
    authorization_window = new Authorization_window(0, this, 0);
    authorization_window->show();
    this->hide();
}

// Нажатие enter для поиска
void Video_window::on_lineEdit_video_name_returnPressed()
{
    on_pushButton_clicked();
}

void Video_window::on_listWidget_itemEntered(QListWidgetItem *item)
{

}

void Video_window::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        search_by_url = {false};
        break;
    case 1:
        search_by_url = {true};
        break;
    }
    return;
}

// геттер на listWidget
QListWidget *Video_window::get_list_widget()
{
    return ui->listWidget;
}

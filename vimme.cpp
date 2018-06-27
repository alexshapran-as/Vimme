#include "vimme.h"
#include "ui_vimme.h"

extern unsigned int auth_id;
bool music_is_playing = {false};
bool next_or_previos = {false};
bool menu_was_opened = {false};
QString audio_name_for_vimme_window_widget;

Vimme::Vimme(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Vimme)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint);      // Отключаем оформление окна
    this->setAttribute(Qt::WA_TranslucentBackground, Qt::AA_ImmediateWidgetCreation);   // Делаем фон главного виджета прозрачным
    // Создаём эффект тени
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    ui->centralWidget->setGraphicsEffect(shadowEffect);   // Устанавливаем эффект тени на окно
    ui->centralWidget->layout()->setMargin(5);            // Устанавливаем размер полей
    ui->centralWidget->layout()->setSpacing(0);           // Устанавливаем размер пространства между элементами в размещении виджета
    ui->music_player->hide();
    ui->burger_menu->hide();
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setBlurRadius(10); // Устанавливаем радиус размытия
    shadow_effect->setOffset(5);     // Устанавливаем смещение тени
    this->setGraphicsEffect(shadow_effect);   // Устанавливаем эффект тени на окно
    ui->lineEdit->setPlaceholderText("Введите название аудиозаписи для поиска:)");
    ui->lineEdit_2->setPlaceholderText("Пожалуйста, подождите, пока идет поиск...");
    ui->lineEdit_2->hide();
    ui->pushButton_10->hide();
    ui->pushButton_4->setEnabled(false);
    player = new QMediaPlayer(this);
    downloads_window = new Downloads_window(this);
    audio_window_widget = new Audio_window_widget(this, player);
    video_window = new Video_window(this, downloads_window/*, authorization_window*/);
    //choice_for_search << "Розовое вино" << "Feduk" << "LSP";
    connect(player, &QMediaPlayer::volumeChanged, this, &Vimme::on_volume_changed);
    connect(player, &QMediaPlayer::durationChanged, this, &Vimme::on_duration_changed);
    connect(player, &QMediaPlayer::positionChanged, this, &Vimme::on_duration_changing);
    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(mediaPlayerError(QMediaPlayer::Error)));
}

Vimme::~Vimme()
{
    delete ui;
    delete player;
    delete audio_downloader;
    delete downloads_window;
    delete video_window;
}

void Vimme::audio_starter()
{
    ui->listWidget->clear();
    QLabel * cat_label = new QLabel(this);
    cat_label->setGeometry(/*ui->listWidget*/ui->centralWidget->height() / 2, /*ui->listWidget*/ui->centralWidget->width() / 4, 350, 350);
    cat_loading.setFileName("://img/cat_loading.gif");
    cat_loading.setSpeed(1000000);
    cat_label->setMovie(&cat_loading);
    cat_label->show();
    cat_loading.start();
    generate_sig(sig);
    Request request_;
    RequestSender request_sender_;
    QString address;
    if (auth_id != 0)
    {
        address = "https://api.vk.com/method/execute?code=return%7Ba%3AAPI.audio.get(%7Bowner_id%3A" + QString::number(auth_id) + "%2Coffset%3A0%2Ccount%3A150%2Calbum_id%3A0%2Cv%3A5.63%7D)%2Cl%3AAPI.audio.getAlbums(%7Bowner_id%3A" + QString::number(auth_id) + "%2Ccount%3A75%7D)%2Cc%3AAPI.account.getCounters(%7Bfilter%3A\"friends%2Cmessages%2Cphotos%2Cvideos%2Cgroups%2Cnotifications\"%7D)%2Co%3A" + QString::number(auth_id) + "%2Cu%3AAPI.users.get(%7Buser_ids%3A" + QString::number(auth_id) + "%2Cfields%3A\"first_name_gen\"%7D)%7D%3B&access_token=6c9d35a395395bb9edd41f4f45f960b7097616c8b0b067c819de34d064e20371a77b6b53d8efc2a47d635&v=4.99&lang=ru&random=0.9516545731179962&https=1&callback=Site.APIRequestCallbacks%5B4%5D&sig=" + sig;
    }
    request_.setAddress(address);
    QByteArray data = request_sender_.get(request_);
    QString j_search_result = QString::fromStdString(data.toStdString());
    j_search_result.remove("Site.APIRequestCallbacks[4](");
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
        audios = j_object["response"].toObject()["a"].toObject()["items"].toArray();
        audios.pop_front();
    }
    cat_loading.stop();
    delete cat_label;
    foreach (const QJsonValue & value, audios)
    {
        QJsonObject obj = value.toObject();
        unsigned int duration = + obj["duration"].toInt();
        unsigned int minutes = duration / 60;
        unsigned int seconds = duration - ( minutes * 60 );
        MusicItem * music_item = new MusicItem();
        QString music_name = obj["title"].toString();
        if (music_name.size() > 75)
        {
            music_name.truncate(75);
            music_name.push_back("...");
        }
        music_item->get_label_from_mi(1)->setText(music_name + "\n" + obj["artist"].toString());
        music_item->get_label_from_mi(2)->setText(QString::number(minutes) + ":" + QString::number(seconds));
        music_item->get_label_from_mi(3)->setStyleSheet("QLabel#label_3 {image: url(://img/music_ico.png);}");
        QListWidgetItem * item = new QListWidgetItem(ui->listWidget);
        item->setSizeHint(music_item->sizeHint());
        ui->listWidget->setItemWidget(item, music_item);
    }
}

// Парсер json данных - ответа на поисковый запрос
void Vimme::parser(QByteArray & data)
{
    QString j_search_result = QString::fromStdString(data.toStdString());
    j_search_result.remove(j_parse_start);
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
        audios = j_object["response"].toArray();
        audios.pop_front();
    }
}

// Нажатие на кнопку найти
void Vimme::on_pushButton_clicked()
{
    ui->listWidget->clear();
    ui->lineEdit_2->show();
    // Анимированная загрузка
    QLabel * cat_label = new QLabel(this);
    cat_label->setGeometry(/*ui->listWidget*/ui->centralWidget->height() / 2, /*ui->listWidget*/ui->centralWidget->width() / 4, 350, 350);
    cat_loading.setFileName("://img/cat_loading.gif");
    cat_loading.setSpeed(1000000);
    cat_label->setMovie(&cat_loading);
    cat_label->show();
    cat_loading.start();
    QString music = ui->lineEdit->text();

//    if (qFind(choice_for_search.begin(), choice_for_search.end(), music) != choice_for_search.end())
//    {
//        choice_for_search << music;
//    }
//    QCompleter * completer = new QCompleter(choice_for_search, this);
//    completer->setCaseSensitivity(Qt::CaseInsensitive);
//    ui->lineEdit->setCompleter(completer);

    generate_sig(sig);
    Request request_;
    RequestSender request_sender_;
    request_.setAddress("https://api.vk.com/method/audio.search?q=" + music
                        + "&performer_only=" + all_music_or_artist + "&lyrics=0&count=140&offset=1&access_token=167bfe8dc246bca0c50ae358b47a631eddb348dd1dc857c0597e3c9d40d8fd8cc43403f7922acb6da69ea&v=4.99&lang=ru&random=0.9754578837460133&https=1&callback=Site.APIRequestCallbacks%5B2%5D&sig="
                        + sig);
    QByteArray data = request_sender_.get(request_);
    parser(data);
    ui->lineEdit_2->hide();
    cat_loading.stop();
    delete cat_label;
    foreach (const QJsonValue & value, audios)
    {
        QJsonObject obj = value.toObject();
        unsigned int duration = + obj["duration"].toInt();
        unsigned int minutes = duration / 60;
        unsigned int seconds = duration - ( minutes * 60 );
        MusicItem * music_item = new MusicItem();
        QString music_name = obj["title"].toString();
        if (music_name.size() > 75)
        {
            music_name.truncate(75);
            music_name.push_back("...");
        }
        music_item->get_label_from_mi(1)->setText(music_name + "\n" + obj["artist"].toString());
        music_item->get_label_from_mi(2)->setText(QString::number(minutes) + ":" + QString::number(seconds));
        music_item->get_label_from_mi(3)->setStyleSheet("QLabel#label_3 {image: url(://img/music_ico.png);}");
        QListWidgetItem * item = new QListWidgetItem(ui->listWidget);
        item->setSizeHint(music_item->sizeHint());
        ui->listWidget->setItemWidget(item, music_item);
    }
}

// Нажатие на enter для поиска
void Vimme::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

// Нажатие на кнопку скачать
void Vimme::on_pushButton_3_clicked()
{
    if (ui->listWidget->currentRow() == -1)
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите аудиозапись из списка для скачивания, нажав на нее");
        ui->pushButton_3->setEnabled(true);
        return;
    }
    QJsonObject obj = audios[ui->listWidget->currentRow()].toObject();
    //file_name.clear();
    file_name = QFileDialog::getSaveFileName(0, "Выбор места сохранения аудио", obj["title"].toString() + " - " + obj["artist"].toString(), "*.mp3");
    urls = obj["url"].toString();
    downloaditem * download_item = new downloaditem();
    QString music_name = obj["title"].toString();
    if (music_name.size() > 75)
    {
        music_name.truncate(75);
        music_name.push_back("...");
    }
    music_name += "\n" + file_name;
    download_item->get_label_from_di(1)->setStyleSheet("QLabel#label_1 {image: url(://img/music_ico.png);}");
    download_item->get_label_from_di(2)->setText(music_name);
    QListWidgetItem * item = new QListWidgetItem(downloads_window->get_listwidget_from_dw());
    item->setSizeHint(download_item->sizeHint());
    downloads_window->get_listwidget_from_dw()->setItemWidget(item, download_item);

    QUrl url(urls);
    audio_downloader = new Downloader(url, file_name, download_item, this);
}

// Нажатие по аудиозаписи в списке
void Vimme::on_listWidget_itemClicked(/*QListWidgetItem *item*/)
{
    ui->music_player->show();
    music_is_playing = true;
    on_pushButton_2_clicked();
}

// Нажатие на кнопку прослушать
void Vimme::on_pushButton_2_clicked()
{
//    if (ui->listWidget->currentRow() == -1)
//    {
//        QMessageBox::critical(this, "Ошибка!", "Выберите аудиозапись из списка для прослушивания, нажав на нее");
//        return;
//    }
    if (next_or_previos)
    {
        next_or_previos = false;
        player->stop();
        music_is_playing = false;
        ui->pushButton_4->setEnabled(true);
        QJsonObject obj = audios[ui->listWidget->currentRow()].toObject();
        ui->lineEdit_3->setText(obj["artist"].toString() + " - " + obj["title"].toString());
        audio_name_for_vimme_window_widget = obj["artist"].toString() + " - " + obj["title"].toString();
        QUrl url(obj["url"].toString());
        player->setMedia(url);
        player->play();
        return;
    }
    if (music_is_playing)
    {
        if (player->state() != QMediaPlayer::PausedState)
        {
            player->stop();
        }
        else
        {
            player->play();
            ui->pushButton_2->setStyleSheet("image: url(:/img/pause.png); background-color: rgb(54, 57, 62);"
                                            " border-radius:20px; border: 6px;");
            audio_window_widget->get_play_pause_button()->setStyleSheet("image: url(:/img/pause.png); background-color: rgb(54, 57, 62);"
                                                                        " border-radius:20px; border: 6px;");
            QJsonObject obj = audios[ui->listWidget->currentRow()].toObject();
            audio_name_for_vimme_window_widget = obj["artist"].toString() + " - " + obj["title"].toString();
            music_is_playing = false;
            return;
        }
        ui->pushButton_2->setStyleSheet("image: url(:/img/pause.png); background-color: rgb(54, 57, 62);"
                                        " border-radius:20px; border: 6px;");
        audio_window_widget->get_play_pause_button()->setStyleSheet("image: url(:/img/pause.png); background-color: rgb(54, 57, 62);"
                                                                    " border-radius:20px; border: 6px;");
    }
    else
    {
        player->pause();
        ui->pushButton_2->setStyleSheet("image: url(:/img/play.png); background-color: rgb(54, 57, 62);"
                                        " border-radius:20px; border: 6px;");
        audio_window_widget->get_play_pause_button()->setStyleSheet("image: url(:/img/play.png); background-color: rgb(54, 57, 62);"
                                                                   " border-radius:20px; border: 6px;");
        QJsonObject obj = audios[ui->listWidget->currentRow()].toObject();
        audio_name_for_vimme_window_widget = obj["artist"].toString() + " - " + obj["title"].toString();
        music_is_playing = true;
        return;
    }
    music_is_playing = false;
    ui->pushButton_4->setEnabled(true);
    QJsonObject obj = audios[ui->listWidget->currentRow()].toObject();
    ui->lineEdit_3->setText(obj["artist"].toString() + " - " + obj["title"].toString());
    audio_name_for_vimme_window_widget = obj["artist"].toString() + " - " + obj["title"].toString();
    QUrl url(obj["url"].toString());
    player->setMedia(url);
    player->play();
}

void Vimme::mediaPlayerError(QMediaPlayer::Error err)
{
    qDebug() << err;
}

// Нажатие на кнопку - предыдущая песня
void Vimme::on_pushButton_5_clicked()
{
    next_or_previos = true;
    if (ui->listWidget->currentRow() == 0)
    {
        ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
    }
    else
    {
        ui->listWidget->setCurrentRow(ui->listWidget->currentRow() - 1);
    }
    ui->pushButton_2->setStyleSheet("image: url(:/img/pause.png); background-color: rgb(54, 57, 62);"
                                    " border-radius:20px; border: 6px;");
    on_pushButton_2_clicked();
}

// Песня прослушана
void Vimme::on_horizontalSlider_valueChanged(int value)
{
    QJsonObject obj = audios[ui->listWidget->currentRow()].toObject();
    audio_name_for_vimme_window_widget = obj["artist"].toString() + " - " + obj["title"].toString();
    audio_window_widget->refresh_audio_name_lineEdit();
    if (value == ui->horizontalSlider->maximum())
    {
        on_pushButton_6_clicked();
    }
}

// Нажатие на кнопку - следующая песня
void Vimme::on_pushButton_6_clicked()
{
    next_or_previos = true;
    if (ui->listWidget->currentRow() == ui->listWidget->count() - 1)
    {
        ui->listWidget->setCurrentRow(0);
    }
    else
    {
        ui->listWidget->setCurrentRow(ui->listWidget->currentRow() + 1);
    }
    ui->pushButton_2->setStyleSheet("image: url(:/img/pause.png); background-color: rgb(54, 57, 62);"
                                    " border-radius:20px; border: 6px;");
    on_pushButton_2_clicked();
}

// Нажатие на кнопку стоп
void Vimme::on_pushButton_4_clicked()
{
    player->stop();
    ui->pushButton_2->setStyleSheet("image: url(:/img/play.png); background-color: rgb(54, 57, 62);"
                                    " border-radius:20px; border: 6px;");
    music_is_playing = true;
    //ui->pushButton_4->setEnabled(false);
}

// Изменение громкости
void Vimme::on_horizontalSlider_2_sliderMoved(int position)
{
    player->setVolume(position);
}

// Перемотка музыки
void Vimme::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position);
}

// Изменение позиции в изменении громкости
void Vimme::on_volume_changed(qint64 position)
{
    ui->horizontalSlider_2->setValue(position);
}

// Изменение позиции в перемотке музыки, началось прослушивание
void Vimme::on_duration_changed(qint64 position)
{
    ui->horizontalSlider->setMaximum(position);
    audio_window_widget->get_horizontalSlider()->setMaximum(position);
    QJsonObject obj = audios[ui->listWidget->currentRow()].toObject();
    unsigned int duration = + obj["duration"].toInt();
    unsigned int minutes = duration / 60;
    unsigned int seconds = duration - ( minutes * 60 );
    ui->lineEdit_5->setText("-" + QString::number(minutes) + ":" + QString::number(seconds));
    audio_window_widget->get_time_2_lineEdit()->setText("-" + QString::number(minutes) + ":" + QString::number(seconds));
}

// Изменение позиции в перемотке музыки, идет прослушивание
void Vimme::on_duration_changing(qint64 position)
{
    ui->horizontalSlider->setValue(position);
    audio_window_widget->get_horizontalSlider()->setValue(position);
    position /= 1000;
    unsigned int minutes = position / 60;
    unsigned int seconds = position - ( minutes * 60 );
    ui->lineEdit_4->setText("-" + QString::number(minutes) + ":" + QString::number(seconds));
    audio_window_widget->get_time_1_lineEdit()->setText("-" + QString::number(minutes) + ":" + QString::number(seconds));
}

// Закрытие Окна
void Vimme::on_pushButton_7_clicked()
{
    this->close();
}

// Нажатие на кнопку - во весь экран
void Vimme::on_pushButton_9_clicked()
{
    ui->pushButton_9->hide();
    ui->pushButton_10->show();
    this->showFullScreen();
}

// Нажатие на кнопку - уменьшить экран
void Vimme::on_pushButton_10_clicked()
{
    ui->pushButton_10->hide();
    ui->pushButton_9->show();
    this->showNormal();
}

// Скрыть (Свернуть) экран
void Vimme::on_pushButton_18_clicked()
{
    audio_window_widget->get_audio_name_lineEdit()->setText(audio_name_for_vimme_window_widget);
    audio_window_widget->show();
    this->showMinimized();
}

// Если премещется указатель мыши с зажатой ЛКМ
void Vimme::mouseMoveEvent(QMouseEvent * event)
{
    //qDebug() << "event->pos().x() = " << event->pos().x() << "event->pos().y() = " << event->pos().y();
    if (event->pos().x() <= 10 && event->pos().y() <= 10)
    {
        this->setCursor(Qt::SizeFDiagCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
    if (this->cursor().shape() == Qt::SizeFDiagCursor && event->buttons() && Qt::LeftButton)
    {
        if (!this->isMaximized())
        {
            auto dx = event->x() - mouse_position.x();
            auto dy = event->y() - mouse_position.y();
            //qDebug() << "dx = " << dx << "dy = " << dy;
            setGeometry(x() + dx, y() + dy, width() - dx, height() - dy);
            if (dx <= 0 && dy <= 0)
            {
                mouse_position = event->pos();
            }
            else if (dx >= 0 && dy >= 0)
            {
                event->pos() = mouse_position;
            }
        }
    }
    if(this->cursor().shape() == Qt::ArrowCursor && event->buttons() && Qt::LeftButton)
    {
        QPoint diff = event->pos() - mouse_position;
        QPoint new_pos = this->pos() + diff;
        this->move(new_pos);
    }
}

// Нажатие на кнопку мыши
void Vimme::mousePressEvent(QMouseEvent * event)
{
    mouse_position = event->pos();
}

// Отпускание кнопки мыши
void Vimme::mouseReleaseEvent()
{
    mouse_position = QPoint(-1,1);
    this->setCursor(Qt::ArrowCursor);
}

// Открытие/Закрытие burger-menu
void Vimme::on_pushButton_14_clicked()
{
    if (menu_was_opened)
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
        menu_was_opened = false;
        return;
    }
    ui->pushButton_14->setStyleSheet("image: url(:/img/close.png);"
                                     "background-color: rgb(54, 57, 62);"
                                     "border-radius:20px;"
                                     "border: 6px;");
    ui->burger_menu->show();
    menu_was_opened = true;
}

// Список загрузок
void Vimme::on_pushButton_11_clicked()
{
    downloads_window->show();
}

// Авторизация
void Vimme::on_pushButton_15_clicked()
{
    authorization_window = new Authorization_window(this, 0, 0);
    authorization_window->show();
    this->hide();
}

// Видео
void Vimme::on_pushButton_13_clicked()
{
    video_window->show();
    this->hide();
}

// Выбор поиска по умолчанию или по исполнителям
void Vimme::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        all_music_or_artist = "0";
        break;
    case 1:
        all_music_or_artist = "1";
        break;
    default:
        break;
    }
}

// Прокрутка колесика мышки
void Vimme::wheelEvent(QWheelEvent *e)
{
    static unsigned int index = {0};
    ++index;
//    if (index > 2)
//    {
//        up_button = new Up_button(ui->listWidget);
//        int x= ui->listWidget->geometry().right() - ui->listWidget->frameSize().width() + 90;
//        int y= ui->listWidget->geometry().bottom() - ui->listWidget->frameSize().height() ;
//        up_button->setGeometry(x, y, 62, 62);
//        up_button->show();
//    }
}

// Геттер на listWidget
QListWidget * Vimme::get_listWidget_from_vimme()
{
    return ui->listWidget;
}

QLineEdit *Vimme::get_lineEdit_5_from_vimme()
{
    return ui->lineEdit_5;
}

QLineEdit *Vimme::get_lineEdit_4_from_vimme()
{
    return ui->lineEdit_4;
}

// Геттер на horisontalSlider
QSlider * Vimme::get_horisontalSlider_from_vimme()
{
    return ui->horizontalSlider;
}


#include "video_window_widget.h"
#include "ui_video_window_widget.h"

QVector<downloaditem *> download_video_items;
unsigned int resolution = {0};
bool video_is_playing = {true};
bool next_or_previos_v = {false};

Video_window_widget::Video_window_widget(QMediaPlayer *player, QVideoWidget *video_widget, Video_window * video_window_parent, Downloads_window *downloads_window) :
    player(player), video_widget(video_widget), video_window_parent(video_window_parent), downloads_window(downloads_window),
    ui(new Ui::Video_window_widget)
{
    ui->setupUi(this);
    // Настройка UI
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    this->setMouseTracking(true);   // Включаем отслеживание курсора без нажатых кнопокы
    ui->pushButton_10->hide();
    ui->pushButton_2->setStyleSheet("image: url(:/img/pause.png); background-color: rgb(54, 57, 62);"
                                    " border-radius:20px; border: 6px;");
    ui->gridLayout->addWidget(video_widget);
    for (QString val : video_window_parent->urls)
    {
        val.chop(4);
        val.remove(0, val.lastIndexOf(".") + 1);
        ui->comboBox->addItem(val);
    }
    video_widget->show();

    connect(player, &QMediaPlayer::volumeChanged, this, &Video_window_widget::on_volume_changed);
    connect(player, &QMediaPlayer::durationChanged, this, &Video_window_widget::on_duration_changed);
    connect(player, &QMediaPlayer::positionChanged, this, &Video_window_widget::on_duration_changing);
    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(mediaPlayerError(QMediaPlayer::Error)));
}

Video_window_widget::~Video_window_widget()
{
    delete ui;
}

void Video_window_widget::mousePressEvent(QMouseEvent * event)
{
    // Запоминаем позицию при нажатии кнопки мыши
    mpos = event->pos();
}

void Video_window_widget::mouseMoveEvent(QMouseEvent * event)
{
    if (mpos.x() >= 0 && event->buttons() && Qt::LeftButton)
    {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

void Video_window_widget::mouseReleaseEvent()
{
    // Очищаем старое значение позиции нажатия мыши
    mpos = QPoint(-1, -1);
}

void Video_window_widget::on_duration_changed(qint64 position)
{
    ui->horizontalSlider->setMaximum(position);
    QJsonObject obj = video_window_parent->videos[video_window_parent->get_list_widget()->currentRow()].toObject();
    unsigned int duration = + obj["duration"].toInt();
    unsigned int minutes = duration / 60;
    unsigned int seconds = duration - ( minutes * 60 );
    ui->lineEdit_5->setText("-" + QString::number(minutes) + ":" + QString::number(seconds));
}

void Video_window_widget::on_duration_changing(qint64 position)
{
    ui->horizontalSlider->setValue(position);
    position /= 1000;
    unsigned int minutes = position / 60;
    unsigned int seconds = position - ( minutes * 60 );
    ui->lineEdit_4->setText("-" + QString::number(minutes) + ":" + QString::number(seconds));
}

void Video_window_widget::on_volume_changed(qint64 position)
{
    ui->horizontalSlider_2->setValue(position);
}

void Video_window_widget::mediaPlayerError(QMediaPlayer::Error err)
{
    qDebug() << err;
}

void Video_window_widget::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position);
}

void Video_window_widget::on_horizontalSlider_valueChanged(int value)
{
    player->setPosition(value);
}

void Video_window_widget::on_horizontalSlider_2_sliderMoved(int position)
{
    player->setVolume(position);
}

// Закрыть окно
void Video_window_widget::on_pushButton_7_clicked()
{
    player->stop();
    video_widget->close();
    this->close();
}

// Свернуть окно
void Video_window_widget::on_pushButton_18_clicked()
{
    this->showMinimized();
}

// Развернуть окно во весь экран
void Video_window_widget::on_pushButton_9_clicked()
{
    ui->pushButton_9->hide();
    ui->pushButton_10->show();
    this->showFullScreen();
}

// Уменьшить экран
void Video_window_widget::on_pushButton_10_clicked()
{
    ui->pushButton_10->hide();
    ui->pushButton_9->show();
    this->showNormal();
}

// Нажатие на кнопку play/pause
void Video_window_widget::on_pushButton_2_clicked()
{
    if (next_or_previos_v)
    {
        next_or_previos_v = false;
        delete player;
        video_is_playing = false;
        video_window_parent->on_listWidget_itemClicked(video_window_parent->get_list_widget()->currentItem());
        this->close();
        return;
    }
    if (video_is_playing)
    {
        if (player->state() != QMediaPlayer::PausedState)
        {
            player->pause();
            ui->pushButton_2->setStyleSheet("image: url(:/img/play.png); background-color: rgb(54, 57, 62);"
                                            " border-radius:20px; border: 6px;");
        }
        else
        {
            player->play();
            ui->pushButton_2->setStyleSheet("image: url(:/img/pause.png); background-color: rgb(54, 57, 62);"
                                            " border-radius:20px; border: 6px;");
            video_is_playing = true;
            return;
        }
    }
    else
    {
        player->play();
        ui->pushButton_2->setStyleSheet("image: url(:/img/pause.png); background-color: rgb(54, 57, 62);"
                                        " border-radius:20px; border: 6px;");
        video_is_playing = true;
        return;
    }
    video_is_playing = false;
    ui->pushButton_4->setEnabled(true);
    QJsonObject obj = video_window_parent->videos[video_window_parent->get_list_widget()->currentRow()].toObject();
    ui->lineEdit_3->setText(obj["artist"].toString() + " - " + obj["title"].toString());
}

// Следующее видео
void Video_window_widget::on_pushButton_6_clicked()
{
    next_or_previos_v = true;
    if (video_window_parent->get_list_widget()->currentRow() == video_window_parent->get_list_widget()->count() - 1)
    {
        video_window_parent->get_list_widget()->setCurrentRow(0);
    }
    else
    {
        video_window_parent->get_list_widget()->setCurrentRow(video_window_parent->get_list_widget()->currentRow() + 1);
    }
    ui->pushButton_2->setStyleSheet("image: url(:/img/pause.png); background-color: rgb(54, 57, 62);"
                                    " border-radius:20px; border: 6px;");
    on_pushButton_2_clicked();
}

// Предыдущее видео
void Video_window_widget::on_pushButton_5_clicked()
{
    next_or_previos_v = true;
    if (video_window_parent->get_list_widget()->currentRow() == 0)
    {
        video_window_parent->get_list_widget()->setCurrentRow(video_window_parent->get_list_widget()->count() - 1);
    }
    else
    {
        video_window_parent->get_list_widget()->setCurrentRow(video_window_parent->get_list_widget()->currentRow() - 1);
    }
    ui->pushButton_2->setStyleSheet("image: url(:/img/pause.png); background-color: rgb(54, 57, 62);"
                                    " border-radius:20px; border: 6px;");
    on_pushButton_2_clicked();
}

// Стоп
void Video_window_widget::on_pushButton_4_clicked()
{
    player->stop();
    ui->pushButton_2->setStyleSheet("image: url(:/img/play.png); background-color: rgb(54, 57, 62);"
                                    " border-radius:20px; border: 6px;");
    video_is_playing = false;
}

// Нажатие на кнопку скачать
void Video_window_widget::on_pushButton_3_clicked()
{
    if (video_window_parent->get_list_widget()->currentRow() == -1)
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите аудиозапись из списка для скачивания, нажав на нее");
        ui->pushButton_3->setEnabled(true);
        return;
    }
    Request request_;
    RequestSender request_sender_;
    QJsonObject obj = video_window_parent->videos[video_window_parent->get_list_widget()->currentRow()].toObject();
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
    j_search_result.remove(0, j_search_result.indexOf("https://cs"));
    j_search_result.chop(j_search_result.size() - j_search_result.indexOf("?extra"));
    file_name = QFileDialog::getSaveFileName(0, "Выбор места сохранения аудио", obj["title"].toString() + " - " + obj["artist"].toString(), "*.mp4");
    urls = j_search_result;
    downloaditem * download_item = new downloaditem();
    QString video_name = obj["title"].toString();
    if (video_name.size() > 75)
    {
        video_name.truncate(75);
        video_name.push_back("...");
    }
    video_name += "\n" + file_name;
    download_item->get_label_from_di(1)->setStyleSheet("QLabel#label_1 {image: url(://img/music_ico.png);}");
    download_item->get_label_from_di(2)->setText(video_name);
    QListWidgetItem * item = new QListWidgetItem(downloads_window->get_listwidget_2_from_dw());
    item->setSizeHint(download_item->sizeHint());
    downloads_window->get_listwidget_2_from_dw()->setItemWidget(item, download_item);
    download_video_items.push_back(download_item);

    QUrl url(urls);
    video_downloader = new Downloader(url, file_name, download_item, this);
}

// Геттер для задания названия видео
QLineEdit *Video_window_widget::get_lineEdit_3()
{
    return ui->lineEdit_3;
}

QListWidget *Video_window_widget::get_listWidget()
{
    return ui->listWidget;
}

// Выбор видео в боковой панели
void Video_window_widget::on_listWidget_itemClicked(QListWidgetItem *item)
{
    player->stop();
    delete player;
    this->hide();
    video_window_parent->get_list_widget()->setCurrentRow(ui->listWidget->currentRow());
    video_window_parent->on_listWidget_itemClicked(video_window_parent->get_list_widget()->currentItem());
    this->close();
}

// Выбор разрешения
void Video_window_widget::on_comboBox_currentIndexChanged(int index)
{
    resolution = index;
    switch (index) {
    case 0:
        player->stop();
        player->setMedia(QUrl(video_window_parent->urls[0]));
        video_widget->update();
        player->play();
        break;
    case 1:
        player->stop();
        player->setMedia(QUrl(video_window_parent->urls[1]));
        video_widget->update();
        player->play();
        break;
    case 2:
        player->stop();
        player->setMedia(QUrl(video_window_parent->urls[2]));
        video_widget->update();
        player->play();
        break;
    case 3:
        player->stop();
        player->setMedia(QUrl(video_window_parent->urls[3]));
        video_widget->update();
        player->play();
        break;
    case 4:
        player->stop();
        player->setMedia(QUrl(video_window_parent->urls[4]));
        video_widget->update();
        player->play();
        break;
    case 5:
        player->stop();
        player->setMedia(QUrl(video_window_parent->urls[5]));
        video_widget->update();
        player->play();
        break;
    default:
        break;
    }
}

// Открыть видео в стандартном плеере
void Video_window_widget::on_pushButton_clicked()
{
     QDesktopServices::openUrl(QUrl(video_window_parent->urls[resolution]));
}

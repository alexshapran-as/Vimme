#include "audio_window_widget.h"
#include "ui_audio_window_widget.h"

extern QString audio_name_for_vimme_window_widget;

Audio_window_widget::Audio_window_widget(Vimme * main_vimme, QMediaPlayer *player) :
    /*QWidget(parent),*/
    main_vimme(main_vimme),
    player(player),
    ui(new Ui::Audio_window_widget)
{
    ui->setupUi(this);
    // Настройка UI
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);      // Отключаем оформление окна
    this->setAttribute(Qt::WA_TranslucentBackground);   // Делаем фон главного виджета прозрачным
    this->setMouseTracking(true);   // Включаем отслеживание курсора без нажатых кнопокы

    // Создаём эффект тени
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(9); // Устанавливаем радиус размытия
    shadowEffect->setOffset(3);     // Устанавливаем смещение тени
    ui->widgetInterface->setGraphicsEffect(shadowEffect);   // Устанавливаем эффект тени на окно
    ui->widgetInterface->layout()->setMargin(0);            // Устанавливаем размер полей
    ui->widgetInterface->layout()->setSpacing(0);

    connect(player, &QMediaPlayer::durationChanged, this, &Audio_window_widget::on_duration_changed);
    connect(player, &QMediaPlayer::positionChanged, this, &Audio_window_widget::on_duration_changing);
}

void Audio_window_widget::mousePressEvent(QMouseEvent *event)
{
    // Запоминаем позицию при нажатии кнопки мыши
    mpos = event->pos();
}

void Audio_window_widget::mouseMoveEvent(QMouseEvent *event)
{
    if (mpos.x() >= 0 && event->buttons() && Qt::LeftButton)
    {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

void Audio_window_widget::mouseReleaseEvent(/*QMouseEvent *event*/)
{
    // Очищаем старое значение позиции нажатия мыши
    mpos = QPoint(-1, -1);
}

Audio_window_widget::~Audio_window_widget()
{
    delete ui;
}

void Audio_window_widget::on_duration_changed(qint64 position)
{
    main_vimme->get_horisontalSlider_from_vimme()->setMaximum(position);
    ui->horizontalSlider->setMaximum(position);
    QJsonObject obj = main_vimme->audios[main_vimme->get_listWidget_from_vimme()->currentRow()].toObject();
    unsigned int duration = + obj["duration"].toInt();
    unsigned int minutes = duration / 60;
    unsigned int seconds = duration - ( minutes * 60 );
    main_vimme->get_lineEdit_5_from_vimme()->setText("-" + QString::number(minutes) + ":" + QString::number(seconds));
    ui->lineEdit_time_2->setText("-" + QString::number(minutes) + ":" + QString::number(seconds));
}

void Audio_window_widget::on_duration_changing(qint64 position)
{
    main_vimme->get_horisontalSlider_from_vimme()->setValue(position);
    ui->horizontalSlider->setValue(position);
    position /= 1000;
    unsigned int minutes = position / 60;
    unsigned int seconds = position - ( minutes * 60 );
    main_vimme->get_lineEdit_4_from_vimme()->setText("-" + QString::number(minutes) + ":" + QString::number(seconds));
    ui->lineEdit_time_1->setText("-" + QString::number(minutes) + ":" + QString::number(seconds));
}

// Закрыть виджет
void Audio_window_widget::on_pushButton_close_widget_clicked()
{
    player->pause();
    this->close();
}

// Нажатие на кнопку play
void Audio_window_widget::on_pushButton_on_off_clicked()
{
    main_vimme->on_pushButton_2_clicked();
    ui->lineEdit_audio_name->setText(audio_name_for_vimme_window_widget);
}

// Следующая песня
void Audio_window_widget::on_pushButton_next_audio_clicked()
{
    main_vimme->on_pushButton_6_clicked();
    ui->lineEdit_audio_name->setText(audio_name_for_vimme_window_widget);
}


// Предыдущая песня
void Audio_window_widget::on_pushButton_previous_audio_clicked()
{
    main_vimme->on_pushButton_5_clicked();
    ui->lineEdit_audio_name->setText(audio_name_for_vimme_window_widget);
}

// Скачть песню
void Audio_window_widget::on_pushButton_download_audio_clicked()
{
    main_vimme->on_pushButton_3_clicked();
}

// Геттер на кнопку play/pause
QPushButton * Audio_window_widget::get_play_pause_button()
{
    return ui->pushButton_on_off;
}

// Геттер на время проигрывания
QLineEdit * Audio_window_widget::get_time_1_lineEdit()
{
    return ui->lineEdit_time_1;
}

// Геттер на продолжительность песни
QLineEdit * Audio_window_widget::get_time_2_lineEdit()
{
    return ui->lineEdit_time_2;
}

// Геттер на назвние песни
QLineEdit * Audio_window_widget::get_audio_name_lineEdit()
{
    return ui->lineEdit_audio_name;
}

// Геттер на слайдер
QSlider *Audio_window_widget::get_horizontalSlider()
{
    return ui->horizontalSlider;
}

// Обновление названия песни
void Audio_window_widget::refresh_audio_name_lineEdit()
{
    ui->lineEdit_audio_name->setText(audio_name_for_vimme_window_widget);
}

void Audio_window_widget::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position);
}

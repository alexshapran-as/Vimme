#include "downloads_window.h"
#include "ui_downloads_window.h"

extern QVector<downloaditem *> download_video_items;

Downloads_window::Downloads_window(Vimme *main_vimme) :
    main_vimme(main_vimme),
    ui(new Ui::Downloads_window)
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
    ui->listWidget_video->hide();
    ui->pushButton->setStyleSheet("QPushButton#pushButton {"
                                  "background-color: rgb(95, 101, 111);"
                                  "font: Bold  14pt \"Calibri light\";"
                                  "border-radius:20px;"
                                  "border: 6px;}"
                                  "QPushButton#pushButton:hover {"
                                  "background-color: rgb(95, 101, 111);"
                                  "border-radius:20px;"
                                  "border: 6px;}");
}

Downloads_window::~Downloads_window()
{
    delete ui;
}

void Downloads_window::mousePressEvent(QMouseEvent *event)
{
    // Запоминаем позицию при нажатии кнопки мыши
    mpos = event->pos();
}

void Downloads_window::mouseMoveEvent(QMouseEvent *event)
{
    if (mpos.x() >= 0 && event->buttons() && Qt::LeftButton)
    {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

void Downloads_window::mouseReleaseEvent()
{
    // Очищаем старое значение позиции нажатия мыши
    mpos = QPoint(-1, -1);
}

QListWidget * Downloads_window::get_listwidget_from_dw()
{
    return ui->listWidget_music;
}

QListWidget *Downloads_window::get_listwidget_2_from_dw()
{
    return ui->listWidget_video;
}

void Downloads_window::on_pushButton_7_clicked()
{
    this->close();
    main_vimme->show();
}

void Downloads_window::on_pushButton_9_clicked()
{
    ui->pushButton_9->hide();
    ui->pushButton_10->show();
    this->showFullScreen();
}

void Downloads_window::on_pushButton_10_clicked()
{
    ui->pushButton_10->hide();
    ui->pushButton_9->show();
    this->showNormal();
}

void Downloads_window::on_pushButton_18_clicked()
{
    this->showMinimized();
}

void Downloads_window::on_pushButton_14_clicked()
{
    this->close();
    main_vimme->show();
}

// Выбор - музыка
void Downloads_window::on_pushButton_clicked()
{
    ui->pushButton_2->setStyleSheet("QPushButton#pushButton_2 {"
                                  "background-color: rgb(54, 57, 62);"
                                  "border-radius:20px;"
                                  "border: 6px;}"
                                  "QPushButton#pushButton_2:hover {"
                                  "background-color: rgb(95, 101, 111);"
                                  "border-radius:20px;"
                                  "border: 6px;}");
    ui->pushButton->setStyleSheet("QPushButton#pushButton {"
                                  "background-color: rgb(95, 101, 111);"
                                  "font: Bold  14pt \"Calibri light\";"
                                  "border-radius:20px;"
                                  "border: 6px;}"
                                  "QPushButton#pushButton:hover {"
                                  "background-color: rgb(95, 101, 111);"
                                  "border-radius:20px;"
                                  "border: 6px;}");
    ui->listWidget_video->hide();
    ui->listWidget_music->show();
}

// Выбор - видео
void Downloads_window::on_pushButton_2_clicked()
{
    ui->pushButton->setStyleSheet("QPushButton#pushButton {"
                                  "background-color: rgb(54, 57, 62);"
                                  "border-radius:20px;"
                                  "border: 6px;}"
                                  "QPushButton#pushButton:hover {"
                                  "background-color: rgb(95, 101, 111);"
                                  "border-radius:20px;"
                                  "border: 6px;}");
    ui->pushButton_2->setStyleSheet("QPushButton#pushButton_2 {"
                                  "background-color: rgb(95, 101, 111);"
                                  "font: Bold  14pt \"Calibri light\";"
                                  "border-radius:20px;"
                                  "border: 6px;}"
                                  "QPushButton#pushButton_2:hover {"
                                  "background-color: rgb(95, 101, 111);"
                                  "border-radius:20px;"
                                  "border: 6px;}");
    ui->listWidget_music->hide();
    ui->listWidget_video->show();
}

void Downloads_window::on_listWidget_video_itemClicked(QListWidgetItem * item)
{
    QString file_name_for_play = download_video_items[ui->listWidget_video->currentRow()]->get_label_from_di(2)->text();
    file_name_for_play.remove(0, file_name_for_play.indexOf("\n") + 1);
    QFile * file = new QFile(file_name_for_play);
    if (!file->exists())
    {
        QMessageBox::critical(this, "Ошибка!", "Файл не найден или удален");
        return;
    }
    else
    {
        if (!file->open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, "Ошибка!", "Ошибка открытия файла");
            return;
        }
        QDesktopServices::openUrl(QUrl::fromLocalFile(file_name_for_play));
    }
}

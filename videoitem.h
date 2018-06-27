#ifndef VIDEOITEM_H
#define VIDEOITEM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class VideoItem;
}

class VideoItem : public QWidget
{
    Q_OBJECT

public:
    explicit VideoItem(QWidget *parent = 0);
    ~VideoItem();
    QLabel * get_label_from_vi(unsigned int label_index);

private slots:

private:
    Ui::VideoItem *ui;
};

#endif // VIDEOITEM_H

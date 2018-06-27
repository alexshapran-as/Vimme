#ifndef VIDEOITEM_SIDE_H
#define VIDEOITEM_SIDE_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class VideoItem_side;
}

class VideoItem_side : public QWidget
{
    Q_OBJECT

public:
    explicit VideoItem_side(QWidget *parent = 0);
    ~VideoItem_side();
    QLabel * get_label_from_vi(unsigned int label_index);

private:
    Ui::VideoItem_side *ui;
};

#endif // VIDEOITEM_SIDE_H

#ifndef MUSICITEM_H
#define MUSICITEM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class MusicItem;
}

class MusicItem : public QWidget
{
    Q_OBJECT

public:
    explicit MusicItem(QWidget *parent = 0);
    ~MusicItem();
    QLabel * get_label_from_mi(unsigned int label_index);

private:
    Ui::MusicItem *ui;
};

#endif // MUSICITEM_H

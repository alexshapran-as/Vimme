#ifndef MOREITEM_H
#define MOREITEM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class MoreItem;
}

class MoreItem : public QWidget
{
    Q_OBJECT

public:
    explicit MoreItem(QWidget *parent = 0);
    ~MoreItem();
    QLabel * get_label_from_morei();

private:
    Ui::MoreItem *ui;
};

#endif // MOREITEM_H

#ifndef DOWNLOADITEM_H
#define DOWNLOADITEM_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>

namespace Ui {
class downloaditem;
}

class downloaditem : public QWidget
{
    Q_OBJECT

public:
    explicit downloaditem(QWidget *parent = 0);
    ~downloaditem();
    QLabel * get_label_from_di(unsigned int label_index);
    QProgressBar * get_progressbar_from_di();

private:
    Ui::downloaditem *ui;
};

#endif // DOWNLOADITEM_H

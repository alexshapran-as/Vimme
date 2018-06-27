#include "vimme.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QTextCodec *utfcodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utfcodec);
    Vimme vimme_window;
    vimme_window.show();

    return a.exec();
}

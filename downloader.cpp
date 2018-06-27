#include "downloader.h"


Downloader::Downloader(QUrl Url, QString file_name, downloaditem *di, QObject *parent) :
    di(di), file_name(file_name),
    QObject(parent)
{
    QNetworkRequest request(Url);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    pReply = WebCtrl.get(request);
    file = new QFile(file_name);
    if(!file->open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка скачивания";
        delete file;
        file = 0;
    }
    connect(pReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(on_download_progress(qint64,qint64)));
    connect(pReply, SIGNAL(readyRead()), this, SLOT(ready_read()));
    connect(&WebCtrl, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileDownloaded()));
}

Downloader::~Downloader()
{

}

void Downloader::fileDownloaded()
{
    file->flush();
    file->close();
}

void Downloader::on_download_progress(qint64 bytesSent, qint64 bytesTotal)
{
    //qDebug() << 100 * bytesSent/bytesTotal;
    di->get_progressbar_from_di()->setMaximum(bytesTotal);
    di->get_progressbar_from_di()->setValue(bytesSent);
}

void Downloader::ready_read()
{
    if (file)
    {
        file->write(pReply->readAll());
    }
}

#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QProgressBar>
#include "downloads_window.h"
#include "downloaditem.h"

class Downloads_window;

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QUrl Url, QString file_name, downloaditem * di = 0, QObject *parent = 0);
    virtual ~Downloader();

private slots:
    void fileDownloaded();
    void on_download_progress(qint64 bytesSent, qint64 bytesTotal);
    void ready_read();

private:
    QNetworkAccessManager WebCtrl;
    QByteArray DownloadedData;
    Downloads_window * dw;
    downloaditem * di;
    QString file_name;
    QFile * file;
    QNetworkReply * pReply;
};

#endif // DOWNLOADER_H

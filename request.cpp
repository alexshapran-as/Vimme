#include "request.h"

namespace Network
{

    Request::Request(QString address /*= QString()*/)
    {
        setAddress(address);
    }

    QString Request::address() const
    {
        return _address;
    }

    void Request::setAddress(QString address)
    {
        for (QPair<QString, QString> value : QUrlQuery(QUrl(address)).queryItems())
            addParam(value.first, value.second);
        _address = address;
    }

    void Request::addParam(QString name, QVariant value)
    {
        _params[name] = value.toString();
    }

    bool Request::removeParam(QString name)
    {
        if (false == _params.contains(name))
            return false;
        _params.remove(name);
        return true;
    }

    QStringList Request::paramsNames() const
    {
        return _params.keys();
    }

    QMap<QString, QString> Request::params() const
    {
        return _params;
    }

    QUrl Request::url(bool forGetRequest /*= true*/) const
    {
        QUrl url(address());
        if (forGetRequest)
            url.setQuery(data());
        return url;
    }

    QNetworkRequest Request::request(bool forGetRequest /*= true*/) const
    {
        QNetworkRequest r(url(forGetRequest));

        r.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        r.setHeader(QNetworkRequest::UserAgentHeader, "VKAndroidApp/4.12-1118");
        r.setRawHeader("cookie:", "_ym_uid=1475686840781055268; remixlang=0; remixstid=1135301971_d619b7138625651976; remixdt=0; remixscreen_depth=24; remixttpid=48e51cf50ff36c847ae856e50a5bd5fbbc5231eb03; remixmdv=ptpbFoYxVziSFf5r; remixaudio_date=21-06-2018; remixaudio_background_play_time_=0; remixaudio_background_play_time_limit=1800; remixaudio_show_alert_today=0; remixmdevice=1920/1080/1/!!!!!!!; remixgp=3edad7ea86f77d49d7ed8344c2c2b76f; remixaudio_show_alert_to_three_month=0; remixaudio_show_alert_to_three_month_date=21-06-2018; remixflash=30.0.0; remixforce_full=2; remixshow_fvbar=1; remixrefkey=42ec2e9324b96655e3; remixseenads=1; remixsid=336b09553bdbfd6c682fcc92071ec868a35e9a0ef5ffca1f2f4c7; remixsts=%7B%22data%22%3A%5B%5B1529624234%2C%22time_spent%22%2C%7B%22video%22%3A%7B%22full%22%3A9058%2C%22last%22%3A1529624232617%2C%22options%22%3A%7B%7D%7D%7D%5D%5D%2C%22uniqueId%22%3A488332880%7D");



        if (!forGetRequest)
        {
            r.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        }

        return r;
    }

    QByteArray Request::data() const
    {
        auto b = _params.begin();
        auto e = _params.end();

        QByteArray byteArrayData;

        while (b != e)
        {
            byteArrayData.append(b.key());
            byteArrayData.append('=');
            byteArrayData.append(b.value());
            byteArrayData.append('&');

            b++;
        }

        byteArrayData.chop(1);

        return byteArrayData;
    }

}



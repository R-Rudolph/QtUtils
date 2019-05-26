#ifndef QTUTILS_QNETWORKPROXYSETTINGS_H
#define QTUTILS_QNETWORKPROXYSETTINGS_H

#include<QNetworkProxy>

namespace qt_utils
{
  class QNetworkProxySettings
  {
    QNetworkProxy::ProxyType type_;
    QString user_;
    QString password_;
    QString hostname_;
    quint16 port_;
  public:
    QNetworkProxySettings();
    QNetworkProxySettings(QNetworkProxy::ProxyType type, QString user, QString password, QString hostname, quint16 port);
    QNetworkProxy::ProxyType type() const;
    void setType(const QNetworkProxy::ProxyType& type);
    QString user() const;
    void setUser(const QString& user);
    QString password() const;
    void setPassword(const QString& password);
    QString hostname() const;
    void setHostname(const QString& hostname);
    quint16 port() const;
    void setPort(const quint16& port);

    void setProxy(QNetworkProxy& proxy) const;
    void setApplicationProxy() const;
    QNetworkProxy toProxy() const;
  };
}

#endif

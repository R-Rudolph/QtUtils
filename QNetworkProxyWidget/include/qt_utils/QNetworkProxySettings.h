#ifndef QTUTILS_QNETWORKPROXYSETTINGS_H
#define QTUTILS_QNETWORKPROXYSETTINGS_H

#include<QNetworkProxy>

namespace qt_utils
{
  class QNetworkProxySettingsPrivate;

  struct QNetworkProxyProperties
  {
    QString name;
    bool hasHost;
    bool hasCredentials;
  };

  class QNetworkProxySettings
  {
  public:
    static const QMap<QNetworkProxy::ProxyType, QNetworkProxyProperties> proxyTypePropertyMapping_;
    static const QNetworkProxyProperties proxyTypeNotFoundProperty_;
    static const QNetworkProxyProperties& proxyTypeProperties(QNetworkProxy::ProxyType type);
    static bool readString(const QJsonValue& value, QString& dest);
    static bool readInt(const QJsonValue& value, int& dest);
  private:
    QNetworkProxySettingsPrivate* d;
  public:
    QNetworkProxySettings();
    QNetworkProxySettings(QNetworkProxy::ProxyType type, QString user, QString password, QString hostname, quint16 port);
    QNetworkProxySettings(const QNetworkProxySettings& other);
    ~QNetworkProxySettings();
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

    QJsonObject toJson() const;
    bool loadJson(const QJsonObject& data);

    QNetworkProxySettings& operator=(const QNetworkProxySettings& other);
  };
}

#endif

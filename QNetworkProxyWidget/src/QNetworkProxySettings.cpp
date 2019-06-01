#include "qt_utils/QNetworkProxySettings.h"
#include "qt_utils/private/QNetworkProxySettingsPrivate.h"
#include <QJsonObject>

namespace qt_utils
{

  QNetworkProxy::ProxyType QNetworkProxySettings::type() const
  {
    return d->type_;
  }

  void QNetworkProxySettings::setType(const QNetworkProxy::ProxyType& type)
  {
    d->type_ = type;
  }

  QString QNetworkProxySettings::user() const
  {
    return d->user_;
  }

  void QNetworkProxySettings::setUser(const QString& user)
  {
    d->user_ = user;
  }

  QString QNetworkProxySettings::password() const
  {
    return d->password_;
  }

  void QNetworkProxySettings::setPassword(const QString& password)
  {
    d->password_ = password;
  }

  QString QNetworkProxySettings::hostname() const
  {
    return d->hostname_;
  }

  void QNetworkProxySettings::setHostname(const QString& hostname)
  {
    d->hostname_ = hostname;
  }

  quint16 QNetworkProxySettings::port() const
  {
    return d->port_;
  }

  void QNetworkProxySettings::setPort(const quint16& port)
  {
    d->port_ = port;
  }

  void QNetworkProxySettings::setApplicationProxy() const
  {
    QNetworkProxy applicationProxy = QNetworkProxy::applicationProxy();
    setProxy(applicationProxy);
    QNetworkProxy::setApplicationProxy(applicationProxy);
  }

  QNetworkProxy QNetworkProxySettings::toProxy() const
  {
    QNetworkProxy proxy;
    setProxy(proxy);
    return proxy;
  }

  QJsonObject QNetworkProxySettings::toJson() const
  {
    QJsonObject data;
    data.insert("username",d->user_);
    data.insert("password",d->password_);
    data.insert("hostname",d->hostname_);
    data.insert("port",d->port_);
    data.insert("type",d->type_);
    return data;
  }

  bool QNetworkProxySettings::loadJson(const QJsonObject& data)
  {
    d->user_     = data["username"].toString();
    d->password_ = data["password"].toString();
    d->hostname_ = data["hostname"].toString();
    d->type_     = QNetworkProxy::ProxyType(data["type"    ].toInt());
    d->port_     = static_cast<quint16>(data["port"].toInt(1));
  }

  QNetworkProxySettings& QNetworkProxySettings::operator=(const QNetworkProxySettings& other)
  {
    delete d;
    d = new QNetworkProxySettingsPrivate(*other.d);
    return *this;
  }

  void QNetworkProxySettings::setProxy(QNetworkProxy& proxy) const
  {
    proxy.setPort(d->port_);
    proxy.setUser(d->user_);
    proxy.setHostName(d->hostname_);
    proxy.setPassword(d->password_);
    proxy.setType(d->type_);
  }

  QNetworkProxySettings::QNetworkProxySettings()
  {
    d = new QNetworkProxySettingsPrivate();
  }

  QNetworkProxySettings::QNetworkProxySettings(QNetworkProxy::ProxyType type, QString user, QString password, QString hostname, quint16 port)
    : QNetworkProxySettings()
  {
    d->type_     = type;
    d->user_     = user;
    d->password_ = password;
    d->hostname_ = hostname;
    d->port_     = port;
  }

  QNetworkProxySettings::QNetworkProxySettings(const QNetworkProxySettings& other)
  {
    this->d = new QNetworkProxySettingsPrivate(*other.d);
  }

  QNetworkProxySettings::~QNetworkProxySettings()
  {
    delete d;
  }

}

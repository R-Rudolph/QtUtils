#include "QNetworkProxySettings.h"

namespace qt_utils
{

  QNetworkProxy::ProxyType QNetworkProxySettings::type() const
  {
    return type_;
  }

  void QNetworkProxySettings::setType(const QNetworkProxy::ProxyType& type)
  {
    type_ = type;
  }

  QString QNetworkProxySettings::user() const
  {
    return user_;
  }

  void QNetworkProxySettings::setUser(const QString& user)
  {
    user_ = user;
  }

  QString QNetworkProxySettings::password() const
  {
    return password_;
  }

  void QNetworkProxySettings::setPassword(const QString& password)
  {
    password_ = password;
  }

  QString QNetworkProxySettings::hostname() const
  {
    return hostname_;
  }

  void QNetworkProxySettings::setHostname(const QString& hostname)
  {
    hostname_ = hostname;
  }

  quint16 QNetworkProxySettings::port() const
  {
    return port_;
  }

  void QNetworkProxySettings::setPort(const quint16& port)
  {
    port_ = port;
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

  void QNetworkProxySettings::setProxy(QNetworkProxy& proxy) const
  {
    proxy.setPort(port_);
    proxy.setUser(user_);
    proxy.setHostName(hostname_);
    proxy.setPassword(password_);
    proxy.setType(type_);
  }

  QNetworkProxySettings::QNetworkProxySettings()
  {

  }

  QNetworkProxySettings::QNetworkProxySettings(QNetworkProxy::ProxyType type, QString user, QString password, QString hostname, quint16 port)
  {
    type_     = type;
    user_     = user;
    password_ = password;
    hostname_ = hostname;
    port_     = port;
  }

}

#include "qt_utils/QNetworkProxySettings.h"
#include "qt_utils/private/QNetworkProxySettingsPrivate.h"
#include <QJsonObject>

namespace qt_utils
{

  const QMap<QNetworkProxy::ProxyType, QString> QNetworkProxySettings::proxyTypeNameMapping_ = {{QNetworkProxy::NoProxy         , "No Proxy"},
                                                                                                {QNetworkProxy::DefaultProxy    , "Default Proxy"},
                                                                                                {QNetworkProxy::Socks5Proxy     , "Socks5 Proxy"},
                                                                                                {QNetworkProxy::HttpProxy       , "HTTP Proxy"},
                                                                                                {QNetworkProxy::HttpCachingProxy, "HTTP Caching Proxy"},
                                                                                                {QNetworkProxy::FtpCachingProxy , "FTP Caching Proxy"}};

  const QString QNetworkProxySettings::proxyTypeNotFoundName_ = "<Not found>";

  const QString& QNetworkProxySettings::proxyTypeString(QNetworkProxy::ProxyType type)
  {
    if(proxyTypeNameMapping_.contains(type))
      return proxyTypeNameMapping_.find(type).value();
    else
      return proxyTypeNotFoundName_;
  }

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
    if(!readString(data["username"],d->user_    )) return false;
    if(!readString(data["password"],d->password_)) return false;
    if(!readString(data["hostname"],d->hostname_)) return false;
    int port, type;
    if(!readInt(data["type"],type)) return false;
    if(!readInt(data["port"],port)) return false;
    if(port<1 || port > 65535) return false;
    if(!proxyTypeNameMapping_.contains(QNetworkProxy::ProxyType(type))) return false;
    d->type_ = static_cast<QNetworkProxy::ProxyType>(type);
    d->port_ = static_cast<quint16>(port);
    return true;
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

  bool QNetworkProxySettings::readString(const QJsonValue& value, QString& dest)
  {
    if(value.isString())
    {
      dest = value.toString();
      return true;
    }
    else
    {
      return false;
    }
  }

  bool QNetworkProxySettings::readInt(const QJsonValue& value, int& dest)
  {
    if(value.isDouble())
    {
      dest = value.toInt();
      return true;
    }
    else
    {
      return false;
    }
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

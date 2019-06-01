#ifndef QTUTILS_QNETWORKPROXYSETTINGSPRIVATE_H
#define QTUTILS_QNETWORKPROXYSETTINGSPRIVATE_H

#include<QNetworkProxy>

namespace qt_utils
{
  class QNetworkProxySettingsPrivate
  {
  public:
    QNetworkProxy::ProxyType type_;
    QString user_;
    QString password_;
    QString hostname_;
    quint16 port_;
  };
}

#endif

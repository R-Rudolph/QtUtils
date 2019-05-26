#ifndef QTUTILS_QNETWORKPROXYWIDGET_H
#define QTUTILS_QNETWORKPROXYWIDGET_H

#include<QWidget>
#include<QNetworkProxy>
#include "QNetworkProxySettings.h"

namespace qt_utils
{
  class QNetworkProxyWidgetPrivate;

  class QNetworkProxyWidget : public QWidget
  {
    Q_OBJECT
    QNetworkProxyWidgetPrivate* d;

    static const QMap<QNetworkProxy::ProxyType, QString> proxyTypeNameMapping_;
    static const QString proxyTypeNotFoundName_;
    static const QString& proxyTypeString(QNetworkProxy::ProxyType type);

    void addProxyButton(const QString& text, QNetworkProxy::ProxyType type);
    QNetworkProxy::ProxyType currentType() const;
    void checkType(QNetworkProxy::ProxyType type);
  public:
    QNetworkProxyWidget(const QList<QNetworkProxy::ProxyType>& availableProxyTypes, QAbstractSocket* targetSocket=nullptr, QWidget* parent=nullptr);
    ~QNetworkProxyWidget();

    QNetworkProxySettings getCurrentSettings() const;
    QNetworkProxySettings getSettings() const;
    void setSettings(const QNetworkProxySettings& settings);
  public slots:
    void accept();
    void reject();
  };
}

#endif

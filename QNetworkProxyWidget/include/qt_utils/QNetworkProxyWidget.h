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

    void addProxyButton(const QString& text, QNetworkProxy::ProxyType type);
    QNetworkProxy::ProxyType currentType() const;
    void checkType(QNetworkProxy::ProxyType type);
  public:
    QNetworkProxyWidget(const QList<QNetworkProxy::ProxyType>& availableProxyTypes, QWidget* parent=nullptr);
    ~QNetworkProxyWidget();

    QNetworkProxySettings getCurrentSettings() const;
    QNetworkProxySettings getSettings() const;
    void setSettings(const QNetworkProxySettings& settings);

    QJsonObject toJson() const;
    bool loadJson(const QJsonObject& data);
  public slots:
    void reset();
    void save();
  };
}

#endif

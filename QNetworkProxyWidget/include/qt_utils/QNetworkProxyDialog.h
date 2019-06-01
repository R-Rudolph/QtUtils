#ifndef QTUTILS_QNETWORKPROXYDIALOG_H
#define QTUTILS_QNETWORKPROXYDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QNetworkProxy>
#include "qt_utils/QNetworkProxySettings.h"

namespace qt_utils
{
  class QNetworkProxyDialogPrivate;

  class QNetworkProxyDialog : public QDialog
  {
    Q_OBJECT
    QNetworkProxyDialogPrivate* d;
  public:
    explicit QNetworkProxyDialog(const QList<QNetworkProxy::ProxyType>& availableProxyTypes, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~QNetworkProxyDialog();

    void setSettings(const QNetworkProxySettings& settings);
    QNetworkProxySettings getSettings();
  signals:

  public slots:
    void accept();
    void reject();
  };
}

#endif // QTUTILS_QNETWORKPROXYDIALOG_H

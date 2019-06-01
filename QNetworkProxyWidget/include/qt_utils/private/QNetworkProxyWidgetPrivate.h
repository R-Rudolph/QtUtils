#ifndef QTUTILS_QNETWORKPROXYWIDGETPRIVATE_H
#define QTUTILS_QNETWORKPROXYWIDGETPRIVATE_H
#include<QWidget>
#include<QNetworkProxy>
#include<QButtonGroup>
#include<QVBoxLayout>
#include<QFormLayout>
#include<QDialogButtonBox>
#include<QRadioButton>
#include<QLineEdit>
#include<QSpinBox>
#include "qt_utils/QNetworkProxySettings.h"

namespace qt_utils
{
  class QNetworkProxyWidgetPrivate
  {
  public:
    QNetworkProxyWidgetPrivate();

    QNetworkProxySettings backupSettings_;

    QButtonGroup* radioButtonGroup_;

    QVector<QPair<QRadioButton*,QNetworkProxy::ProxyType>> proxyButtons_;

    QLineEdit* serverEdit_;
    QSpinBox*  portBox_;
    QLineEdit* usernameEdit_;
    QLineEdit* passwordEdit_;

    QVBoxLayout* mainLayout_;
    QVBoxLayout* proxyButtonLayout_;
    QFormLayout* credentialsLayout_;
  };
}

#endif

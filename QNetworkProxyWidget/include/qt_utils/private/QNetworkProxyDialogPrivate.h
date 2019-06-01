#ifndef QTUTILS_QNETWORKPROXYDIALOGPRIVATE_H
#define QTUTILS_QNETWORKPROXYDIALOGPRIVATE_H
#include<QVBoxLayout>
#include<QDialogButtonBox>
#include "qt_utils/QNetworkProxyWidget.h"

namespace qt_utils
{
  class QNetworkProxyWidget;

  class QNetworkProxyDialogPrivate
  {
  public:
    QNetworkProxyDialogPrivate();

    QVBoxLayout* layout_;
    QNetworkProxyWidget* proxyWidget_;
    QDialogButtonBox* buttons_;
  };
}

#endif

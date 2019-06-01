#include "qt_utils/QNetworkProxyDialog.h"
#include "qt_utils/private/QNetworkProxyDialogPrivate.h"
#include<QJsonObject>

namespace qt_utils
{
  QNetworkProxyDialogPrivate::QNetworkProxyDialogPrivate()
  {
    layout_      = nullptr;
    proxyWidget_ = nullptr;
    buttons_     = nullptr;
  }

  QNetworkProxyDialog::QNetworkProxyDialog(const QList<QNetworkProxy::ProxyType>& availableProxyTypes, QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent,f)
  {
    d = new QNetworkProxyDialogPrivate();
    d->layout_ = new QVBoxLayout(this);
    d->proxyWidget_ = new QNetworkProxyWidget(availableProxyTypes,this);
    d->buttons_     = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    d->layout_->addWidget(d->proxyWidget_,1);
    d->layout_->addWidget(d->buttons_);

    connect(d->buttons_, &QDialogButtonBox::accepted, this, &QNetworkProxyDialog::accept);
    connect(d->buttons_, &QDialogButtonBox::rejected, this, &QNetworkProxyDialog::reject);
  }

  QNetworkProxyDialog::~QNetworkProxyDialog()
  {
    delete d;
  }

  void QNetworkProxyDialog::setSettings(const QNetworkProxySettings& settings)
  {
    d->proxyWidget_->setSettings(settings);
  }

  QNetworkProxySettings QNetworkProxyDialog::getSettings()
  {
    return d->proxyWidget_->getSettings();
  }

  QJsonObject QNetworkProxyDialog::toJson() const
  {
    return d->proxyWidget_->toJson();
  }

  bool QNetworkProxyDialog::loadJson(const QJsonObject& data)
  {
    return d->proxyWidget_->loadJson(data);
  }

  void QNetworkProxyDialog::accept()
  {
    d->proxyWidget_->save();
    QDialog::accept();
  }

  void QNetworkProxyDialog::reject()
  {
    d->proxyWidget_->reset();
    QDialog::reject();
  }
}

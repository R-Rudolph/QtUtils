#include <QNetworkProxyWidget.h>
#include<iostream>
#include<private/QNetworkProxyWidgetPrivate.h>

namespace qt_utils
{
  const QMap<QNetworkProxy::ProxyType, QString> QNetworkProxyWidget::proxyTypeNameMapping_ = {{QNetworkProxy::NoProxy         , "No Proxy"},
                                                                                              {QNetworkProxy::DefaultProxy    , "Default Proxy"},
                                                                                              {QNetworkProxy::Socks5Proxy     , "Socks5 Proxy"},
                                                                                              {QNetworkProxy::HttpProxy       , "HTTP Proxy"},
                                                                                              {QNetworkProxy::HttpCachingProxy, "HTTP Caching Proxy"},
                                                                                              {QNetworkProxy::FtpCachingProxy , "FTP Caching Proxy"}};
  QNetworkProxyWidgetPrivate::QNetworkProxyWidgetPrivate()
  {

  }

  const QString QNetworkProxyWidget::proxyTypeNotFoundName_ = "<Not found>";

  const QString& QNetworkProxyWidget::proxyTypeString(QNetworkProxy::ProxyType type)
  {
    if(proxyTypeNameMapping_.contains(type))
      return proxyTypeNameMapping_.find(type).value();
    else
      return proxyTypeNotFoundName_;
  }

  void QNetworkProxyWidget::addProxyButton(const QString& text, QNetworkProxy::ProxyType type)
  {
    QRadioButton* newProxyButton = new QRadioButton(text,this);
    d->proxyButtons_.append(QPair<QRadioButton*,QNetworkProxy::ProxyType>(newProxyButton,type));
    d->proxyButtonLayout_->addWidget(newProxyButton);
    d->radioButtonGroup_->addButton(newProxyButton);
  }

  QNetworkProxy::ProxyType QNetworkProxyWidget::currentType() const
  {
    foreach(auto button, d->proxyButtons_)
    {
      if(button.first->isChecked())
        return button.second;
    }
    return QNetworkProxy::DefaultProxy;
  }

  QNetworkProxyWidget::QNetworkProxyWidget(const QList<QNetworkProxy::ProxyType>& availableProxyTypes, QAbstractSocket* targetSocket, QWidget* parent)
    : QWidget(parent),
      d(new QNetworkProxyWidgetPrivate())
  {
    d->mainLayout_        = new QVBoxLayout(this);
    d->proxyButtonLayout_ = new QVBoxLayout();
    d->credentialsLayout_ = new QFormLayout();
    d->buttons_           = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    d->serverEdit_   = new QLineEdit(this);
    d->portBox_      = new QSpinBox(this);
    d->usernameEdit_ = new QLineEdit(this);
    d->passwordEdit_ = new QLineEdit(this);

    d->portBox_->setRange(1,65535);
    d->passwordEdit_->setEchoMode(QLineEdit::Password);

    d->credentialsLayout_->addRow("Host Name",d->serverEdit_);
    d->credentialsLayout_->addRow("Port",d->portBox_);
    d->credentialsLayout_->addRow("User",d->usernameEdit_);
    d->credentialsLayout_->addRow("Password",d->passwordEdit_);

    d->mainLayout_->addLayout(d->proxyButtonLayout_);
    d->mainLayout_->addLayout(d->credentialsLayout_);
    d->mainLayout_->addWidget(d->buttons_);

    d->radioButtonGroup_ = new QButtonGroup(this);
    d->targetSocket_     = targetSocket;

    foreach(QNetworkProxy::ProxyType proxyType, availableProxyTypes)
    {
      addProxyButton(proxyTypeString(proxyType),proxyType);
    }
    if(d->proxyButtons_.size()>0)
      d->proxyButtons_[0].first->click();

    connect(d->buttons_,&QDialogButtonBox::accepted,this,&QNetworkProxyWidget::accept);
    connect(d->buttons_,&QDialogButtonBox::rejected,this,&QNetworkProxyWidget::reject);
  }

  QNetworkProxyWidget::~QNetworkProxyWidget()
  {

  }

  QNetworkProxySettings QNetworkProxyWidget::getCurrentSettings() const
  {
    QNetworkProxySettings settings(currentType(),d->usernameEdit_->text(),d->passwordEdit_->text(),d->serverEdit_->text(),static_cast<quint16>(d->portBox_->value()));
    return settings;
  }

  QNetworkProxySettings QNetworkProxyWidget::getSettings() const
  {
    return d->backupSettings_;
  }

  void QNetworkProxyWidget::setSettings(const QNetworkProxySettings& settings)
  {
    checkType(settings.type());
    d->serverEdit_->setText(settings.hostname());
    d->portBox_->setValue(settings.port());
    d->usernameEdit_->setText(settings.user());
    d->passwordEdit_->setText(settings.password());
    d->backupSettings_ = settings;
  }

  void QNetworkProxyWidget::checkType(QNetworkProxy::ProxyType type)
  {
    foreach(auto button, d->proxyButtons_)
    {
      if(button.second == type)
      {
        button.first->click();
      }
    }
    foreach(auto button, d->proxyButtons_)
    {
      if(button.second == QNetworkProxy::DefaultProxy)
      {
        button.first->click();
      }
    }
    if(d->proxyButtons_.size()>0)
      d->proxyButtons_[0].first->click();
  }

  void QNetworkProxyWidget::accept()
  {
    setSettings(getCurrentSettings());
    if(d->targetSocket_)
      d->targetSocket_->setProxy(d->backupSettings_.toProxy());
    else
      d->backupSettings_.setApplicationProxy();
    close();
  }

  void QNetworkProxyWidget::reject()
  {
    setSettings(getSettings());
    close();
  }

}

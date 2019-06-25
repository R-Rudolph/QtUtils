#include <qt_utils/QNetworkProxyWidget.h>
#include<iostream>
#include<qt_utils/private/QNetworkProxyWidgetPrivate.h>
#include<QJsonObject>

namespace qt_utils
{
  QNetworkProxyWidgetPrivate::QNetworkProxyWidgetPrivate()
  {

  }

  void QNetworkProxyWidget::addProxyButton(QNetworkProxy::ProxyType type)
  {
    const QNetworkProxyProperties& properties = QNetworkProxySettings::proxyTypeProperties(type);
    QRadioButton* newProxyButton = new QRadioButton(properties.name,this);
    d->proxyButtons_.append(QPair<QRadioButton*,QNetworkProxy::ProxyType>(newProxyButton,type));
    d->proxyButtonLayout_->addWidget(newProxyButton);
    d->radioButtonGroup_->addButton(newProxyButton);

    if(properties.hasHost)
    {
      connect(newProxyButton,&QRadioButton::clicked,this,&QNetworkProxyWidget::enableHostFields);
    }
    else
    {
      connect(newProxyButton,&QRadioButton::clicked,this,&QNetworkProxyWidget::disableHostFields);
    }
    if(properties.hasCredentials)
    {
      connect(newProxyButton,&QRadioButton::clicked,this,&QNetworkProxyWidget::enableCredentialFields);
    }
    else
    {
      connect(newProxyButton,&QRadioButton::clicked,this,&QNetworkProxyWidget::disableCredentialFields);
    }
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

  QNetworkProxyWidget::QNetworkProxyWidget(const QList<QNetworkProxy::ProxyType>& availableProxyTypes, QWidget* parent)
    : QWidget(parent),
      d(new QNetworkProxyWidgetPrivate())
  {
    d->mainLayout_        = new QVBoxLayout(this);
    d->proxyButtonLayout_ = new QVBoxLayout();
    d->credentialsLayout_ = new QFormLayout();

    d->serverEdit_   = new QLineEdit(this);
    d->portBox_      = new QSpinBox(this);
    d->usernameEdit_ = new QLineEdit(this);
    d->passwordEdit_ = new QLineEdit(this);

    d->portBox_->setRange(1,65535);
    d->passwordEdit_->setEchoMode(QLineEdit::Password);

    d->credentialsLayout_->addRow("Hostname",d->serverEdit_);
    d->credentialsLayout_->addRow("Port",d->portBox_);
    d->credentialsLayout_->addRow("User",d->usernameEdit_);
    d->credentialsLayout_->addRow("Password",d->passwordEdit_);

    d->mainLayout_->addLayout(d->proxyButtonLayout_);
    d->mainLayout_->addLayout(d->credentialsLayout_);

    d->radioButtonGroup_ = new QButtonGroup(this);

    QSet<QNetworkProxy::ProxyType> types;
    foreach(QNetworkProxy::ProxyType proxyType, availableProxyTypes)
    {
      if(!types.contains(proxyType))
      {
        addProxyButton(proxyType);
        types.insert(proxyType);
      }
    }
    if(d->proxyButtons_.size()>0)
      d->proxyButtons_[0].first->click();
  }

  QNetworkProxyWidget::~QNetworkProxyWidget()
  {
    delete d;
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

  QJsonObject QNetworkProxyWidget::toJson() const
  {
    return getSettings().toJson();
  }

  bool QNetworkProxyWidget::loadJson(const QJsonObject& data)
  {
    QNetworkProxySettings settings;
    if(!settings.loadJson(data)) return false;
    setSettings(settings);
    return true;
  }

  void QNetworkProxyWidget::checkType(QNetworkProxy::ProxyType type)
  {
    foreach(auto button, d->proxyButtons_)
    {
      if(button.second == type)
      {
        button.first->click();
        return;
      }
    }
    foreach(auto button, d->proxyButtons_)
    {
      if(button.second == QNetworkProxy::DefaultProxy)
      {
        button.first->click();
        return;
      }
    }
    if(d->proxyButtons_.size()>0)
      d->proxyButtons_[0].first->click();
  }

  void QNetworkProxyWidget::reset()
  {
    setSettings(getSettings());
  }

  void QNetworkProxyWidget::save()
  {
    setSettings(getCurrentSettings());
  }

  void QNetworkProxyWidget::enableHostFields()
  {
    d->portBox_->setDisabled(false);
    d->serverEdit_->setDisabled(false);
  }

  void QNetworkProxyWidget::disableHostFields()
  {
    d->portBox_->setDisabled(true);
    d->serverEdit_->setDisabled(true);
  }

  void QNetworkProxyWidget::enableCredentialFields()
  {
    d->usernameEdit_->setDisabled(false);
    d->passwordEdit_->setDisabled(false);
  }

  void QNetworkProxyWidget::disableCredentialFields()
  {
    d->usernameEdit_->setDisabled(true);
    d->passwordEdit_->setDisabled(true);
  }

}


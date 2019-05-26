#include<QApplication>
#include <qt_utils/QNetworkProxyWidget>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  qt_utils::QNetworkProxyWidget proxyWidget({QNetworkProxy::NoProxy,QNetworkProxy::DefaultProxy,QNetworkProxy::Socks5Proxy});
  proxyWidget.show();
  return app.exec();
}

#include<QApplication>
#include <qt_utils/QNetworkProxyDialog.h>
#include <unistd.h>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  qt_utils::QNetworkProxyDialog proxyDialog({QNetworkProxy::NoProxy,QNetworkProxy::DefaultProxy,QNetworkProxy::Socks5Proxy});
  if(proxyDialog.exec())
  {
    proxyDialog.getSettings().setApplicationProxy();
  }
  sleep(2);
  if(proxyDialog.exec())
  {
    proxyDialog.getSettings().setApplicationProxy();
  }
  return app.exec();
}

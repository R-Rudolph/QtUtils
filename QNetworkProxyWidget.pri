QT          += network widgets
INCLUDEPATH += $$PWD/QNetworkProxyWidget/include

SOURCES += \
    $$PWD/QNetworkProxyWidget/src/QNetworkProxyWidget.cpp \
    $$PWD/QNetworkProxyWidget/src/QNetworkProxySettings.cpp

HEADERS  += \
    $$PWD/QNetworkProxyWidget/include/qt_utils/QNetworkProxyWidget.h \
    $$PWD/QNetworkProxyWidget/include/qt_utils/QNetworkProxyWidget \
    $$PWD/QNetworkProxyWidget/include/qt_utils/private/QNetworkProxyWidgetPrivate.h \
    $$PWD/QNetworkProxyWidget/include/qt_utils/QNetworkProxySettings.h  \
    $$PWD/QNetworkProxyWidget/include/qt_utils/QNetworkProxySettings

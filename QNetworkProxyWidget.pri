QT          += network widgets
INCLUDEPATH += $$PWD/QNetworkProxyWidget/include

SOURCES += \
    $$PWD/QNetworkProxyWidget/src/QNetworkProxyDialog.cpp \
    $$PWD/QNetworkProxyWidget/src/QNetworkProxyWidget.cpp \
    $$PWD/QNetworkProxyWidget/src/QNetworkProxySettings.cpp

HEADERS  += \
    $$PWD/QNetworkProxyWidget/include/qt_utils/QNetworkProxyDialog.h \
    $$PWD/QNetworkProxyWidget/include/qt_utils/QNetworkProxyWidget.h \
    $$PWD/QNetworkProxyWidget/include/qt_utils/QNetworkProxyWidget \
    $$PWD/QNetworkProxyWidget/include/qt_utils/private/QNetworkProxyWidgetPrivate.h \
    $$PWD/QNetworkProxyWidget/include/qt_utils/private/QNetworkProxyDialogPrivate.h \
    $$PWD/QNetworkProxyWidget/include/qt_utils/QNetworkProxySettings.h  \
    $$PWD/QNetworkProxyWidget/include/qt_utils/QNetworkProxySettings \
    $$PWD/QNetworkProxyWidget/include/qt_utils/private/QNetworkProxySettingsPrivate.h

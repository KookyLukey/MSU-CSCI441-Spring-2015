HEADERS += glwidget.h 
SOURCES += glwidget.cpp main.cpp

QT += opengl
CONFIG -= app_bundle
INCLUDEPATH += "/usr/local/include"

RESOURCES += shaders.qrc

FORMS += \
    mainwindow.ui

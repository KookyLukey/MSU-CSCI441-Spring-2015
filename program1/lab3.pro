HEADERS += glwidget.h \ 
    glut.h
SOURCES += glwidget.cpp main.cpp

QT += opengl
CONFIG -= app_bundle
CONFIG += console
INCLUDEPATH += "../include"

RESOURCES += \
    shaders.qrc

LIBS += -lglut32
LIBS += -LC:\Users\Luke\Downloads\glut-3.7


TEMPLATE = app

QT += core
QT += network

OBJECTS_DIR = ./Build
MOC_DIR = ./Build
RCC_DIR = ./Build
QMLCACHE_DIR = ./Build

CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

win32:LIBS += -lKernel32 \
              -lUser32 \
              -lole32 \
              -luuid \
              -loleaut32 \
              -loleacc \
              -lPsapi

SOURCES += \
        aj_client.cpp \
        aj_win.cpp \
        main.cpp

HEADERS += \
    aj_client.h \
    aj_win.h

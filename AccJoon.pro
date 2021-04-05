TEMPLATE = app

QT += core

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
        aj_win.cpp \
        main.cpp

HEADERS += \
    aj_win.h

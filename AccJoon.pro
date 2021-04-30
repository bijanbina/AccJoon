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
        Sources/aj_acc.cpp \
        Sources/aj_client.cpp \
        Sources/aj_win.cpp \
        Sources/backend.cpp \
        Sources/main.cpp

HEADERS += \
    Sources/aj_acc.h \
    Sources/aj_client.h \
    Sources/aj_win.h \
    Sources/backend.h

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
              -lDwmapi \
              -loleacc \
              -lPsapi

SOURCES += \
        Sources/aj_acc.cpp \
        Sources/aj_client.cpp \
        Sources/aj_dllgen.cpp \
        Sources/aj_executer.cpp \
        Sources/aj_keyboard.cpp \
        Sources/aj_parser.cpp \
        Sources/aj_win.cpp \
        Sources/aj_win32.cpp \
        Sources/aj_win32_launcher.cpp \
        Sources/aj_win_process.cpp \
        Sources/backend.cpp \
        Sources/main.cpp

HEADERS += \
    Sources/aj_acc.h \
    Sources/aj_client.h \
    Sources/aj_dllgen.h \
    Sources/aj_executer.h \
    Sources/aj_keyboard.h \
    Sources/aj_parser.h \
    Sources/aj_win.h \
    Sources/aj_win32.h \
    Sources/aj_win32_launcher.h \
    Sources/aj_win_process.h \
    Sources/backend.h

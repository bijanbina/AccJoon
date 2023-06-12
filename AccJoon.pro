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

DISTFILES += \
    AccJoon.exe.manifest

win32:INCLUDEPATH += ../Benjamin/PNN/lua

#QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:"level='requireAdministrator'"

win32:LIBS += -L../Benjamin/PNN/libs \
              -lKernel32 \
              -lUser32 \
              -lole32 \
              -luuid \
              -loleaut32 \
              -lDwmapi \
              -loleacc \
              -lPsapi \
              -llua54

win32-gcc*
{
    win32:LIBS += -llua54
}

win32-msvc*
{
    win32:LIBS += -L"lua54.dll"
}

SOURCES += \
        Sources/aj_acc.cpp \
        Sources/aj_acc_prop.cpp \
        Sources/aj_application.cpp \
        Sources/aj_client.cpp \
        Sources/aj_dllgen.cpp \
        Sources/aj_exec.cpp \
        Sources/aj_exec_acc.cpp \
        Sources/aj_exec_uia.cpp \
        Sources/aj_keyboard.cpp \
        Sources/aj_lua.cpp \
        Sources/aj_mouse.cpp \
        Sources/aj_parser.cpp \
        Sources/aj_uia.cpp \
        Sources/aj_uia_prop.cpp \
        Sources/aj_virt.cpp \
        Sources/aj_win.cpp \
        Sources/aj_win32.cpp \
        Sources/aj_win_process.cpp \
        Sources/backend.cpp \
        Sources/main.cpp

HEADERS += \
    Sources/aj_acc.h \
    Sources/aj_acc_prop.h \
    Sources/aj_application.h \
    Sources/aj_client.h \
    Sources/aj_dllgen.h \
    Sources/aj_exec.h \
    Sources/aj_exec_acc.h \
    Sources/aj_exec_uia.h \
    Sources/aj_keyboard.h \
    Sources/aj_lua.h \
    Sources/aj_mouse.h \
    Sources/aj_parser.h \
    Sources/aj_uia.h \
    Sources/aj_uia_prop.h \
    Sources/aj_virt.h \
    Sources/aj_win.h \
    Sources/aj_win32.h \
    Sources/aj_win_process.h \
    Sources/backend.h \
    Sources/uia_client.h \
    Sources/uia_core.h \
    Sources/uia_element.h \
    Sources/uia_pattern.h \
    Sources/uia_tree_walker.h

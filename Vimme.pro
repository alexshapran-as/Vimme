#-------------------------------------------------
#
# Project created by QtCreator 2018-04-28T19:31:14
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11
QT       += network
QT       += multimedia
QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Vimme
TEMPLATE = app
DESTDIR = C:\Vimme\desktop\app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        vimme.cpp \
    downloader.cpp \
    downloads_window.cpp \
    request.cpp \
    requestsender.cpp \
    sig_generator.cpp \
    musicitem.cpp \
    authorization_window.cpp \
    video_window.cpp \
    audio_window_widget.cpp \
    up_button.cpp \
    downloaditem.cpp \
    video_window_widget.cpp \
    videoitem.cpp \
    moreitem.cpp \
    videoitem_side.cpp

HEADERS += \
        vimme.h \
    downloader.h \
    downloads_window.h \
    request.h \
    requestsender.h \
    musicitem.h \
    authorization_window.h \
    video_window.h \
    audio_window_widget.h \
    up_button.h \
    downloaditem.h \
    video_window_widget.h \
    videoitem.h \
    moreitem.h \
    videoitem_side.h

FORMS += \
        vimme.ui \
    downloads_window.ui \
    musicitem.ui \
    authorization_window.ui \
    video_window.ui \
    audio_window_widget.ui \
    up_button.ui \
    downloaditem.ui \
    video_window_widget.ui \
    videoitem.ui \
    moreitem.ui \
    videoitem_side.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    images.qrc


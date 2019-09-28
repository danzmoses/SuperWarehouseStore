#-------------------------------------------------
#
# Project created by QtCreator 2019-09-22T18:43:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuperWarehouseStore
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    date.cpp \
    item_container.cpp \
    member.cpp \
    member_container.cpp \
    sale_container.cpp

HEADERS  += mainwindow.h \
    date.h \
    item.h \
    item_container.h \
    member.h \
    sale.h \
    sale_container.h \
    member_container.h

FORMS    += mainwindow.ui

DISTFILES += \
    SuperWarehouseStore.pro.user \
    warehouseShoppers.txt \
    items.txt

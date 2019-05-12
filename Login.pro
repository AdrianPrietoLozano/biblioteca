xxxxxxxx    #-------------------------------------------------
#
# Project created by QtCreator 2019-03-01T12:18:29
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Login
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        dialog.cpp \
    mainwindow.cpp \
    nuevo_libro.cpp \
    modificar.cpp \
    prestamo.cpp \
    infoprestamo.cpp \
    devolucion.cpp \
    infodevolucion.cpp \
    altaempleado.cpp \
    modificarempleado.cpp \
    altacliente.cpp

HEADERS += \
        dialog.h \
    mainwindow.h \
    nuevo_libro.h \
    modificar.h \
    prestamo.h \
    infoprestamo.h \
    devolucion.h \
    infodevolucion.h \
    altaempleado.h \
    modificarempleado.h \
    altacliente.h

FORMS += \
        dialog.ui \
    mainwindow.ui \
    nuevo_libro.ui \
    modificar.ui \
    prestamo.ui \
    infoprestamo.ui \
    devolucion.ui \
    infodevolucion.ui \
    altaempleado.ui \
    modificarempleado.ui \
    altacliente.ui

RESOURCES += \
    imagenes.qrc


TEMPLATE = lib
TARGET = logger
DESTDIR = ../lib
DEPENDPATH += .

INCLUDEPATH += . ..
LIBS +=

DEFINES += HAVE_LIBZ
CONFIG += sharedlib warn_on release
CONFIG -= qt

# Input
HEADERS += \
    rcg_logger.h \

SOURCES += \
    rcg_logger.cpp \

######################################################################
# Automatically generated by qmake (2.01a) ven ott 14 16:30:38 2011
######################################################################

TEMPLATE = app
TARGET = xml
DEPENDPATH += .
INCLUDEPATH += .

MOC_DIR	= build/.moc
RCC_DIR	= build/.rcc
OBJECTS_DIR = build/.obj

win32:DESTDIR	+= ./
win32:RC_FILE = win.rc


QT += xml
#### QT += network
#### QT += sql

CONFIG	+= qt release static
CONFIG   += warn_off

# Input
HEADERS += xmlhighlighter.h
SOURCES += main.cpp xmlhighlighter.cpp

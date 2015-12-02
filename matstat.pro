#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T18:12:49
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = matstat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    readcsv.cpp

HEADERS  += mainwindow.h \
    readcsv.h \

FORMS    += mainwindow.ui
CONFIG   += c++11

win32:CONFIG(release, debug|release): LIBS += -LD:/boost_1_59_0/stage/lib/ -lboost_filesystem-mgw49-s-1_59
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/boost_1_59_0/stage/lib/ -lboost_filesystem-mgw49-sd-1_59

INCLUDEPATH += D:/boost_1_59_0
DEPENDPATH += D:/boost_1_59_0

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += D:/boost_1_59_0/stage/lib/libboost_filesystem-mgw49-s-1_59.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += D:/boost_1_59_0/stage/lib/libboost_filesystem-mgw49-sd-1_59.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += D:/boost_1_59_0/stage/lib/boost_filesystem-mgw49-s-1_59.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += D:/boost_1_59_0/stage/lib/boost_filesystem-mgw49-sd-1_59.lib

win32:CONFIG(release, debug|release): LIBS += -LD:/boost_1_59_0/stage/lib/ -lboost_system-mgw49-s-1_59
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/boost_1_59_0/stage/lib/ -lboost_system-mgw49-sd-1_59


win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += D:/boost_1_59_0/stage/lib/libboost_system-mgw49-s-1_59.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += D:/boost_1_59_0/stage/lib/libboost_system-mgw49-sd-1_59.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += D:/boost_1_59_0/stage/lib/boost_system-mgw49-s-1_59.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += D:/boost_1_59_0/stage/lib/boost_system-mgw49-sd-1_59.lib

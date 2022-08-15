QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    informationdialog.cpp \
    informationmobiotdialog.cpp \
    informationmusteridialog.cpp \
    informationserverdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mobiotdialog.cpp \
    musteri.cpp \
    musteriekle.cpp \
    notekledialog.cpp \
    notlardialog.cpp \
    secdialog.cpp \
    serverdialog.cpp \
    servergetdialog.cpp \
    serverservisdialog.cpp \
    servisdialog.cpp \
    servisgetdialog.cpp \
    simkartlar.cpp \
    toolbardialog.cpp

HEADERS += \
    database.h \
    informationdialog.h \
    informationmobiotdialog.h \
    informationmusteridialog.h \
    informationserverdialog.h \
    mainwindow.h \
    mobiotdialog.h \
    musteri.h \
    musteriekle.h \
    notekledialog.h \
    notlardialog.h \
    secdialog.h \
    serverdialog.h \
    servergetdialog.h \
    serverservisdialog.h \
    servisdialog.h \
    servisgetdialog.h \
    simkartlar.h \
    toolbardialog.h

FORMS += \
    informationdialog.ui \
    informationmobiotdialog.ui \
    informationmusteridialog.ui \
    informationserverdialog.ui \
    mainwindow.ui \
    mobiotdialog.ui \
    musteri.ui \
    musteriekle.ui \
    notekledialog.ui \
    notlardialog.ui \
    secdialog.ui \
    serverdialog.ui \
    servergetdialog.ui \
    serverservisdialog.ui \
    servisdialog.ui \
    servisgetdialog.ui \
    simkartlar.ui \
    toolbardialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Desktop/lib/ -llibmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Desktop/lib/ -llibmysqld
else:unix: LIBS += -L$$PWD/../../Desktop/lib/ -llibmysql

INCLUDEPATH += $$PWD/../../Desktop
DEPENDPATH += $$PWD/../../Desktop

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Desktop/ -llibmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Desktop/ -llibmysqld

INCLUDEPATH += $$PWD/../../Desktop
DEPENDPATH += $$PWD/../../Desktop

RESOURCES += \
    images.qrc

QT += gui core widgets
QT += remoteobjects

CONFIG += c++11 app

REPC_SOURCE = RaftProtocol.rep
REPC_REPLICA = RaftProtocol.rep
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        form.cpp \
        helper.cpp \
        main.cpp \
        raftreplica.cpp \
        raftsource.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    RaftProtocol.rep

HEADERS += \
    Role.h \
    form.h \
    helper.h \
    raftreplica.h \
    raftsource.h

FORMS += \
    form.ui

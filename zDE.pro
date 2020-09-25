HEADERS += \
    dungeongenerator.h \
    enemy.h \
    gameview.h \
    levelscene.h \
    pixmapitem.h \
    player.h \
    sword.h

SOURCES += \
    dungeongenerator.cpp \
    enemy.cpp \
    gameview.cpp \
    levelscene.cpp \
    main.cpp \
    pixmapitem.cpp \
    player.cpp \
    sword.cpp

QT += \
    widgets \
    multimedia\
    core

RESOURCES += \
    res.qrc


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv4

INCLUDEPATH += include
LIBS = -Llib/ \
    -lsfml-system-d \
    -lsfml-graphics-d \
    -lsfml-window-d \
    -lsfml-audio-d \
    -lsfml-network-d
QT -= gui
QT += xml
SOURCES += main.cpp \
    application.cpp \
    ressource.cpp \
    rmusic.cpp \
    ressourcefactory.cpp \
    loadressourceexception.cpp \
    rlevel.cpp \
    rimage.cpp \
    window.cpp \
    rsprite.cpp \
    transition.cpp \
    rtext.cpp \
    rbackground.cpp \
    rmenu.cpp \
    rmap.cpp \
    rhud.cpp \
    rnetwork.cpp \
    ship.cpp \
    rships.cpp \
    inputmanager.cpp \
    rinput.cpp \
    rwait.cpp \
    rocket.cpp \
    monster.cpp \
    rmonsters.cpp \
    bullet.cpp \
    animation.cpp
HEADERS += main.hpp \
    singleton.hpp \
    application.hpp \
    ressource.hpp \
    rmusic.hpp \
    ressourcefactory.hpp \
    loadressourceexception.hpp \
    rlevel.hpp \
    rimage.hpp \
    window.hpp \
    rsprite.hpp \
    transition.hpp \
    rtext.hpp \
    rbackground.hpp \
    rmenu.hpp \
    rmap.hpp \
    rhud.hpp \
    rnetwork.hpp \
    ship.hpp \
    rships.hpp \
    inputmanager.hpp \
    rinput.hpp \
    rwait.hpp \
    rocket.hpp \
    monster.hpp \
    rmonsters.hpp \
    bullet.hpp \
    animation.hpp

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lws2_32

HEADERS += \
    server.hpp \
    level.hpp \
    monster.hpp \
    game.hpp \
    threads/iThreads.hpp \
    threads/threadException.hpp \
    sockets/iSocket.hpp \
    sockets/socketException.hpp \
    identifiable.hpp \
    player.hpp \
    rocket.hpp \
    bullet.hpp \
    math/time.hpp \
    math/vertex.hpp \
    filesystem/iFile.hpp \
    filesystem/fileException.hpp \
    monsterType.hpp \
    spawn.hpp \
    entity.hpp \
    library/iLibrary.hpp \
    library/libraryException.hpp \
    utils.hpp \
    monsters/blork/blork.hpp \
    monsters/murloc/murloc.hpp \
    monsters/boss/boss.hpp \
    monsters/boss2/boss2.hpp \
    monsters/boss3/boss3.hpp \
    monsters/iMonster.hpp

SOURCES += \
    main.cpp \
    server.cpp \
    level.cpp \
    monster.cpp \
    game.cpp \
    identifiable.cpp \
    player.cpp \
    rocket.cpp \
    bullet.cpp \
    math/time.cpp \
    math/vertex.cpp \
    monsterType.cpp \
    spawn.cpp \
    entity.cpp \
    utils.cpp \
    threads/threadException.cpp \
    sockets/socketException.cpp \
    filesystem/fileException.cpp \
    library/libraryException.cpp \
    monsters/blork/blork.cpp \
    monsters/murloc/murloc.cpp \
    monsters/boss/boss.cpp \
    monsters/boss2/boss2.cpp \
    monsters/boss3/boss3.cpp

win32 {
HEADERS += \
    threads/threadWindows.hpp \
    sockets/socketWindows.hpp \
    filesystem/fileWindows.hpp \
    library/libraryWindows.hpp

SOURCES += \
    threads/threadWindows.cpp \
    sockets/socketWindows.cpp \
    filesystem/fileWindows.cpp \
    library/libraryWindows.cpp
}

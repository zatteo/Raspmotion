TEMPLATE = app
TARGET = btchat

QT = core bluetooth

SOURCES = \
    main.cpp \
    chat.cpp \
    commandserver.cpp

HEADERS = \
    chat.h \
    commandserver.h

target.path = $$[QT_INSTALL_EXAMPLES]/bluetooth/btchat
INSTALLS += target

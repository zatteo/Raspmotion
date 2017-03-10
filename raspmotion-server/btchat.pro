TEMPLATE = app
TARGET = btchat

QT = core bluetooth

SOURCES = \
    main.cpp \
    chat.cpp \
    chatserver.cpp

HEADERS = \
    chat.h \
    chatserver.h

target.path = $$[QT_INSTALL_EXAMPLES]/bluetooth/btchat
INSTALLS += target

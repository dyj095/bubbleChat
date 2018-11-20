
INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/MessageUtil.cpp \
    $$PWD/CommonUtils.cpp \
    $$PWD/chatItemMsgText/ChatItemMsgText.cpp\
    $$PWD/chatItemMsgImg/ChatItemMsgImg.cpp
HEADERS  += \
    $$PWD/MessageUtil.h \
    $$PWD/CommonUtils.h \
    $$PWD/chatItemMsgText/ChatItemMsgText.h\
    $$PWD/chatItemMsgImg/ChatItemMsgImg.h

FORMS    += \


#include($$PWD/chatItemMsgText/chatItemMsgText.pri)
#include($$PWD/chatItemMsgImg/chatItemMsgImg.pri)
#include($$PWD/chatItemMsgFile/chatItemMsgFile.pri)

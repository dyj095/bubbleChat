
INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/MessageUtil.cpp \
    $$PWD/CommonUtils.cpp \
    $$PWD/chatItemMsgText/ChatItemMsgText.cpp\
    $$PWD/chatItemMsgImg/ChatItemMsgImg.cpp\
    $$PWD/chatItemMsgFile/ChatItemMsgFile.cpp
HEADERS  += \
    $$PWD/MessageUtil.h \
    $$PWD/CommonUtils.h \
    $$PWD/chatItemMsgText/ChatItemMsgText.h\
    $$PWD/chatItemMsgImg/ChatItemMsgImg.h\
    $$PWD/chatItemMsgFile/ChatItemMsgFile.h

FORMS    += \
    $$PWD/chatItemMsgFile/ChatItemMsgFile.ui

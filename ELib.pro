TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/Object.cpp \
    src/Exception.cpp \

HEADERS += \
    include/Object.h \
    include/SmartPointer.h \
    include/Exception.h \
    include/List.h \
    include/StaticList.h \
    include/Array.h \
    include/StaticArray.h \
    include/DynamicList.h \
    include/DynamicArray.h \
    include/LinkList.h \
    include/MyLinkList.h \
    include/DynamicArray.h \
    include/StaticLinkList.h \
    include/Pointer.h \
    include/SharedPointer.h \
    include/CricleList.h \
    include/StaticLinkList.h \
    include/DynamicList.h \
    include/SeqList.h \
    include/DualLinkList.h

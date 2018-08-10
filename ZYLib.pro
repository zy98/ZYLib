TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    Array/Array.h \
    Array/DynamicArray.h \
    Array/StaticArray.h \
    List/CircleList.h \
    List/DualLinkList.h \
    List/DynamicList.h \
    List/LinkList.h \
    List/List.h \
    List/SeqList.h \
    List/StaticLinkList.h \
    List/StaticList.h \
    Pointer/Pointer.h \
    Pointer/SharedPointer.h \
    Pointer/SmartPointer.h \
    Queue/LinkQueue.h \
    Queue/Queue.h \
    Queue/StaticQueue.h \
    Stack/LinkStack.h \
    Stack/Stack.h \
    Stack/StaticStack.h \
    String/String.h \
    Test.h \
    Object/Exception.h \
    Object/Object.h \
    QueenSolution.h \
    Sort/Sort.h \
    Other/Proxy.h \
    Other/Problems.h \
    Other/QueenSolution.h \
    Other/Test.h

SOURCES += \
    String/String.cpp \
    main.cpp \
    Object/Exception.cpp \
    Object/Object.cpp


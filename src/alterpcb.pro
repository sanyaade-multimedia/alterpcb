QT += core gui

TARGET = alterpcb
TEMPLATE = app

INCLUDEPATH += common core gui
DEPENDPATH += common core gui

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
	common/Json.cpp \
	common/StringRegistry.cpp \
	core/Drawing.cpp \
	core/Library.cpp \
	core/LibraryManager.cpp \
	core/Shape.cpp \
	gui/MainWindow.cpp \
	Main.cpp \
        common/VData.cpp \
        gui/Editor.cpp \
    gui/components/TabbedDocumentViewer.cpp

HEADERS += \
	common/Basics.h \
	common/Cow.h \
	common/EnumTranslator.h \
	common/HashTable.h \
	common/Json.h \
	common/MurmurHash.h \
	common/StringRegistry.h \
	common/VData.h \
	core/Drawing.h \
	core/Library.h \
	core/LibraryManager.h \
	core/Shape.h \
	gui/MainWindow.h \
        core/CoreBasics.h \
        common/BackPointer.h \
        gui/Editor.h \
    gui/components/TabbedDocumentViewer.h

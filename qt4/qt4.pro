CONFIG += release

TEMPLATE = app
QT += network
TARGET = rcg_player
DESTDIR = ../bin

DEPENDPATH += . ../rcg

INCLUDEPATH += . ..
win32 {
  INCLUDEPATH +=  ../../boost
}
unix {
  INCLUDEPATH += /opt/local/include
}
macx {
  INCLUDEPATH += /opt/local/include
}

LIBS += -L../lib -lrcssrcgparser
win32 {
  LIBS += ../../zlib123-dll/zlib1.dll -lwsock32
}
unix {
  LIBS += -L/opt/local/lib
  LIBS += -lboost_program_options -lz
}
macx {
  LIBS += -L/opt/local/lib
  LIBS += -lboost_program_options -lz
}

DEFINES += HAVE_LIBZ
win32 {
  DEFINES += HAVE_WINDOWS_H
}
unix {
  DEFINES += HAVE_NETINET_IN_H
  DEFINES += HAVE_BOOST_PROGRAM_OPTIONS
}
macx {
  DEFINES += HAVE_NETINET_IN_H
  DEFINES += HAVE_BOOST_PROGRAM_OPTIONS
}
DEFINES += PACKAGE="\\\"rcg_player\\\""
DEFINES += PACKAGE_NAME="\\\"rcg_player\\\"" VERSION="\\\"1.0\\\""

CONFIG += qt warn_on release
win32 {
  CONFIG += windows
}

#QMAKE_LFLAGS_DEBUG += -static
#QMAKE_LFLAGS_DEBUG += -pg
#QMAKE_CFLAGS_DEBUG += -pg -static -DQABSTRACTSOCKET_DEBUG
#QMAKE_CXXFLAGS += -static
#QMAKE_CXXFLAGS_DEBUG += -pg -static -DQABSTRACTSOCKET_DEBUG

# Input
HEADERS += \
	config_dialog.h \
	disp_holder.h \
	draw_info_painter.h \
	field_canvas.h \
	field_painter.h \
	log_player.h \
	log_player_tool_bar.h \
	log_slider_tool_bar.h \
	main_data.h \
	main_window.h \
	options.h \

SOURCES += \
	config_dialog.cpp \
	disp_holder.cpp \
	draw_info_painter.cpp \
	field_canvas.cpp \
	field_painter.cpp \
	log_player.cpp \
	log_player_tool_bar.cpp \
	log_slider_tool_bar.cpp \
	main.cpp \
	main_data.cpp \
	main_window.cpp \
	options.cpp \

nodist_rcg_player_SOURCES = \
	moc_config_dialog.cpp \
	moc_field_canvas.cpp \
	moc_log_player.cpp \
	moc_log_player_tool_bar.cpp \
	moc_log_slider_tool_bar.cpp \
	moc_main_window.cpp \

win32 {
RC_FILE = rcg_player.rc
}
macx {
ICON = ../icons/rcss.icns
}

TEMPLATE = app
QT += network
TARGET = uniplayer
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
  LIBS += -lboost_program_options-mt -lz
}
macx {
  LIBS += -L/opt/local/lib
  LIBS += -lboost_program_options-mt -lz
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
DEFINES += PACKAGE="\\\"uniplayer\\\""
DEFINES += PACKAGE_NAME="\\\"uniplayer\\\"" VERSION="\\\"14.0.1\\\""

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
	angle_deg.h \
	circle_2d.h \
	config_dialog.h \
	disp_holder.h \
	draw_info_painter.h \
	field_canvas.h \
	field_painter.h \
	line_2d.h \
	log_player.h \
	log_player_tool_bar.h \
	log_slider_tool_bar.h \
	main_data.h \
	main_window.h \
	options.h \
	vector_2d.h

SOURCES += \
	angle_deg.cpp \
	circle_2d.cpp \
	config_dialog.cpp \
	disp_holder.cpp \
	draw_info_painter.cpp \
	field_canvas.cpp \
	field_painter.cpp \
	line_2d.cpp \
	log_player.cpp \
	log_player_tool_bar.cpp \
	log_slider_tool_bar.cpp \
	main.cpp \
	main_data.cpp \
	main_window.cpp \
	options.cpp \
	vector_2d.cpp

nodist_uniplayer_SOURCES = \
	moc_config_dialog.cpp \
	moc_field_canvas.cpp \
	moc_log_player.cpp \
	moc_log_player_tool_bar.cpp \
	moc_log_slider_tool_bar.cpp \
	moc_main_window.cpp \

win32 {
RC_FILE = uniplayer.rc
}
macx {
ICON = ../icons/rcss.icns
}

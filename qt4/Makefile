#############################################################################
# Makefile for building: ../bin/rcg_player
# Generated by qmake (2.01a) (Qt 4.8.7) on: Fri Jun 10 12:28:15 2016
# Project:  qt4.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake -o Makefile qt4.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DHAVE_LIBZ -DHAVE_NETINET_IN_H -DHAVE_BOOST_PROGRAM_OPTIONS -DPACKAGE=\"rcg_player\" -DPACKAGE_NAME=\"rcg_player\" -DVERSION=\"1.0\" -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.. -I/opt/local/include -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -L../lib -lrcssrcgparser -L/opt/local/lib -lboost_program_options -lz -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = config_dialog.cpp \
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
		options.cpp moc_config_dialog.cpp \
		moc_field_canvas.cpp \
		moc_log_player.cpp \
		moc_log_player_tool_bar.cpp \
		moc_log_slider_tool_bar.cpp \
		moc_main_window.cpp
OBJECTS       = config_dialog.o \
		disp_holder.o \
		draw_info_painter.o \
		field_canvas.o \
		field_painter.o \
		log_player.o \
		log_player_tool_bar.o \
		log_slider_tool_bar.o \
		main.o \
		main_data.o \
		main_window.o \
		options.o \
		moc_config_dialog.o \
		moc_field_canvas.o \
		moc_log_player.o \
		moc_log_player_tool_bar.o \
		moc_log_slider_tool_bar.o \
		moc_main_window.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		qt4.pro
QMAKE_TARGET  = rcg_player
DESTDIR       = ../bin/
TARGET        = ../bin/rcg_player

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) ../bin/ || $(MKDIR) ../bin/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: qt4.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtNetwork.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile qt4.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtNetwork.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile qt4.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/rcg_player1.0.0 || $(MKDIR) .tmp/rcg_player1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/rcg_player1.0.0/ && $(COPY_FILE) --parents config_dialog.h disp_holder.h draw_info_painter.h field_canvas.h field_painter.h log_player.h log_player_tool_bar.h log_slider_tool_bar.h main_data.h main_window.h options.h .tmp/rcg_player1.0.0/ && $(COPY_FILE) --parents config_dialog.cpp disp_holder.cpp draw_info_painter.cpp field_canvas.cpp field_painter.cpp log_player.cpp log_player_tool_bar.cpp log_slider_tool_bar.cpp main.cpp main_data.cpp main_window.cpp options.cpp .tmp/rcg_player1.0.0/ && (cd `dirname .tmp/rcg_player1.0.0` && $(TAR) rcg_player1.0.0.tar rcg_player1.0.0 && $(COMPRESS) rcg_player1.0.0.tar) && $(MOVE) `dirname .tmp/rcg_player1.0.0`/rcg_player1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/rcg_player1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_config_dialog.cpp moc_field_canvas.cpp moc_log_player.cpp moc_log_player_tool_bar.cpp moc_log_slider_tool_bar.cpp moc_main_window.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_config_dialog.cpp moc_field_canvas.cpp moc_log_player.cpp moc_log_player_tool_bar.cpp moc_log_slider_tool_bar.cpp moc_main_window.cpp
moc_config_dialog.cpp: config_dialog.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) config_dialog.h -o moc_config_dialog.cpp

moc_field_canvas.cpp: main_data.h \
		disp_holder.h \
		mouse_state.h \
		field_canvas.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) field_canvas.h -o moc_field_canvas.cpp

moc_log_player.cpp: log_player.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) log_player.h -o moc_log_player.cpp

moc_log_player_tool_bar.cpp: log_player_tool_bar.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) log_player_tool_bar.h -o moc_log_player_tool_bar.cpp

moc_log_slider_tool_bar.cpp: log_slider_tool_bar.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) log_slider_tool_bar.h -o moc_log_slider_tool_bar.cpp

moc_main_window.cpp: main_data.h \
		disp_holder.h \
		main_window.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) main_window.h -o moc_main_window.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

config_dialog.o: config_dialog.cpp config_dialog.h \
		options.h \
		main_data.h \
		disp_holder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o config_dialog.o config_dialog.cpp

disp_holder.o: disp_holder.cpp disp_holder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o disp_holder.o disp_holder.cpp

draw_info_painter.o: draw_info_painter.cpp draw_info_painter.h \
		painter_interface.h \
		main_data.h \
		disp_holder.h \
		options.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o draw_info_painter.o draw_info_painter.cpp

field_canvas.o: field_canvas.cpp field_canvas.h \
		main_data.h \
		disp_holder.h \
		mouse_state.h \
		field_painter.h \
		painter_interface.h \
		draw_info_painter.h \
		options.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o field_canvas.o field_canvas.cpp

field_painter.o: field_painter.cpp field_painter.h \
		painter_interface.h \
		field_canvas.h \
		main_data.h \
		disp_holder.h \
		mouse_state.h \
		options.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o field_painter.o field_painter.cpp

log_player.o: log_player.cpp main_data.h \
		disp_holder.h \
		log_player.h \
		options.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o log_player.o log_player.cpp

log_player_tool_bar.o: log_player_tool_bar.cpp log_player_tool_bar.h \
		log_player.h \
		main_data.h \
		disp_holder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o log_player_tool_bar.o log_player_tool_bar.cpp

log_slider_tool_bar.o: log_slider_tool_bar.cpp log_slider_tool_bar.h \
		log_player.h \
		main_data.h \
		disp_holder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o log_slider_tool_bar.o log_slider_tool_bar.cpp

main.o: main.cpp main_window.h \
		main_data.h \
		disp_holder.h \
		options.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

main_data.o: main_data.cpp main_data.h \
		disp_holder.h \
		options.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main_data.o main_data.cpp

main_window.o: main_window.cpp main_window.h \
		main_data.h \
		disp_holder.h \
		config_dialog.h \
		field_canvas.h \
		mouse_state.h \
		log_player.h \
		log_player_tool_bar.h \
		log_slider_tool_bar.h \
		options.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main_window.o main_window.cpp

options.o: options.cpp options.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o options.o options.cpp

moc_config_dialog.o: moc_config_dialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_config_dialog.o moc_config_dialog.cpp

moc_field_canvas.o: moc_field_canvas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_field_canvas.o moc_field_canvas.cpp

moc_log_player.o: moc_log_player.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_log_player.o moc_log_player.cpp

moc_log_player_tool_bar.o: moc_log_player_tool_bar.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_log_player_tool_bar.o moc_log_player_tool_bar.cpp

moc_log_slider_tool_bar.o: moc_log_slider_tool_bar.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_log_slider_tool_bar.o moc_log_slider_tool_bar.cpp

moc_main_window.o: moc_main_window.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_main_window.o moc_main_window.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:


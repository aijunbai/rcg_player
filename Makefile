#############################################################################
# Makefile for building: rcg_player
# Generated by qmake (2.01a) (Qt 4.8.1) on: Thu Oct 1 01:23:04 2015
# Project:  rcg_player.pro
# Template: subdirs
# Command: /opt/bin/qmake -o Makefile rcg_player.pro
#############################################################################

first: make_default
MAKEFILE      = Makefile
QMAKE         = /opt/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
SUBTARGETS    =  \
		sub-rcg \
		sub-qt4 \
		sub-rcg_logger

rcg//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) rcg/ || $(MKDIR) rcg/ 
	cd rcg/ && $(QMAKE) /home/baj/Dropbox/Workspace/rcg_player/rcg/rcg.pro -o $(MAKEFILE)
sub-rcg-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) rcg/ || $(MKDIR) rcg/ 
	cd rcg/ && $(QMAKE) /home/baj/Dropbox/Workspace/rcg_player/rcg/rcg.pro -o $(MAKEFILE)
sub-rcg: rcg//$(MAKEFILE) FORCE
	cd rcg/ && $(MAKE) -f $(MAKEFILE)
sub-rcg-make_default: rcg//$(MAKEFILE) FORCE
	cd rcg/ && $(MAKE) -f $(MAKEFILE) 
sub-rcg-make_first: rcg//$(MAKEFILE) FORCE
	cd rcg/ && $(MAKE) -f $(MAKEFILE) first
sub-rcg-all: rcg//$(MAKEFILE) FORCE
	cd rcg/ && $(MAKE) -f $(MAKEFILE) all
sub-rcg-clean: rcg//$(MAKEFILE) FORCE
	cd rcg/ && $(MAKE) -f $(MAKEFILE) clean
sub-rcg-distclean: rcg//$(MAKEFILE) FORCE
	cd rcg/ && $(MAKE) -f $(MAKEFILE) distclean
sub-rcg-install_subtargets: rcg//$(MAKEFILE) FORCE
	cd rcg/ && $(MAKE) -f $(MAKEFILE) install
sub-rcg-uninstall_subtargets: rcg//$(MAKEFILE) FORCE
	cd rcg/ && $(MAKE) -f $(MAKEFILE) uninstall
qt4//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) qt4/ || $(MKDIR) qt4/ 
	cd qt4/ && $(QMAKE) /home/baj/Dropbox/Workspace/rcg_player/qt4/qt4.pro -o $(MAKEFILE)
sub-qt4-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) qt4/ || $(MKDIR) qt4/ 
	cd qt4/ && $(QMAKE) /home/baj/Dropbox/Workspace/rcg_player/qt4/qt4.pro -o $(MAKEFILE)
sub-qt4: qt4//$(MAKEFILE) FORCE
	cd qt4/ && $(MAKE) -f $(MAKEFILE)
sub-qt4-make_default: qt4//$(MAKEFILE) FORCE
	cd qt4/ && $(MAKE) -f $(MAKEFILE) 
sub-qt4-make_first: qt4//$(MAKEFILE) FORCE
	cd qt4/ && $(MAKE) -f $(MAKEFILE) first
sub-qt4-all: qt4//$(MAKEFILE) FORCE
	cd qt4/ && $(MAKE) -f $(MAKEFILE) all
sub-qt4-clean: qt4//$(MAKEFILE) FORCE
	cd qt4/ && $(MAKE) -f $(MAKEFILE) clean
sub-qt4-distclean: qt4//$(MAKEFILE) FORCE
	cd qt4/ && $(MAKE) -f $(MAKEFILE) distclean
sub-qt4-install_subtargets: qt4//$(MAKEFILE) FORCE
	cd qt4/ && $(MAKE) -f $(MAKEFILE) install
sub-qt4-uninstall_subtargets: qt4//$(MAKEFILE) FORCE
	cd qt4/ && $(MAKE) -f $(MAKEFILE) uninstall
rcg_logger//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) rcg_logger/ || $(MKDIR) rcg_logger/ 
	cd rcg_logger/ && $(QMAKE) /home/baj/Dropbox/Workspace/rcg_player/rcg_logger/rcg_logger.pro -o $(MAKEFILE)
sub-rcg_logger-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) rcg_logger/ || $(MKDIR) rcg_logger/ 
	cd rcg_logger/ && $(QMAKE) /home/baj/Dropbox/Workspace/rcg_player/rcg_logger/rcg_logger.pro -o $(MAKEFILE)
sub-rcg_logger: rcg_logger//$(MAKEFILE) FORCE
	cd rcg_logger/ && $(MAKE) -f $(MAKEFILE)
sub-rcg_logger-make_default: rcg_logger//$(MAKEFILE) FORCE
	cd rcg_logger/ && $(MAKE) -f $(MAKEFILE) 
sub-rcg_logger-make_first: rcg_logger//$(MAKEFILE) FORCE
	cd rcg_logger/ && $(MAKE) -f $(MAKEFILE) first
sub-rcg_logger-all: rcg_logger//$(MAKEFILE) FORCE
	cd rcg_logger/ && $(MAKE) -f $(MAKEFILE) all
sub-rcg_logger-clean: rcg_logger//$(MAKEFILE) FORCE
	cd rcg_logger/ && $(MAKE) -f $(MAKEFILE) clean
sub-rcg_logger-distclean: rcg_logger//$(MAKEFILE) FORCE
	cd rcg_logger/ && $(MAKE) -f $(MAKEFILE) distclean
sub-rcg_logger-install_subtargets: rcg_logger//$(MAKEFILE) FORCE
	cd rcg_logger/ && $(MAKE) -f $(MAKEFILE) install
sub-rcg_logger-uninstall_subtargets: rcg_logger//$(MAKEFILE) FORCE
	cd rcg_logger/ && $(MAKE) -f $(MAKEFILE) uninstall

Makefile: rcg_player.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf
	$(QMAKE) -o Makefile rcg_player.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
qmake: qmake_all FORCE
	@$(QMAKE) -o Makefile rcg_player.pro

qmake_all: sub-rcg-qmake_all sub-qt4-qmake_all sub-rcg_logger-qmake_all FORCE

make_default: sub-rcg-make_default sub-qt4-make_default sub-rcg_logger-make_default FORCE
make_first: sub-rcg-make_first sub-qt4-make_first sub-rcg_logger-make_first FORCE
all: sub-rcg-all sub-qt4-all sub-rcg_logger-all FORCE
clean: sub-rcg-clean sub-qt4-clean sub-rcg_logger-clean FORCE
distclean: sub-rcg-distclean sub-qt4-distclean sub-rcg_logger-distclean FORCE
	-$(DEL_FILE) Makefile
install_subtargets: sub-rcg-install_subtargets sub-qt4-install_subtargets sub-rcg_logger-install_subtargets FORCE
uninstall_subtargets: sub-rcg-uninstall_subtargets sub-qt4-uninstall_subtargets sub-rcg_logger-uninstall_subtargets FORCE

sub-rcg-check: rcg/$(MAKEFILE)
	cd rcg/ && $(MAKE) -f $(MAKEFILE) check
sub-qt4-check: qt4/$(MAKEFILE)
	cd qt4/ && $(MAKE) -f $(MAKEFILE) check
sub-rcg_logger-check: rcg_logger/$(MAKEFILE)
	cd rcg_logger/ && $(MAKE) -f $(MAKEFILE) check
check: sub-rcg-check sub-qt4-check sub-rcg_logger-check

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all
install: install_subtargets  FORCE

uninstall:  uninstall_subtargets FORCE

FORCE:


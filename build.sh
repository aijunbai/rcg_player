#! /bin/bash

do_qmake() {
    cd $1
    qmake
    cd ..
}

find -name 'Makefile' -exec rm '{}' \;

do_qmake rcg
do_qmake rcg_logger
do_qmake qt4

qmake
make


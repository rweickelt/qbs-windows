#!/usr/bin/env bash

set -eux

source /etc/profile

QT_VERSION=${QT_VERSION:-5.9.7}
QBS=${QBS:-/usr/local/Qt/Tools/QtCreator/bin/qbs}
QMAKE=${QMAKE:-${QTDIR}/bin/qmake}

export QBS_AUTOTEST_PROFILE=qt

$QMAKE -r qbs.pro
make -j $(nproc)

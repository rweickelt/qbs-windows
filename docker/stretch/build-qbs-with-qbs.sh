#!/usr/bin/env bash

set -eux

source /etc/profile

QT_VERSION=${QT_VERSION:-5.9.7}
QBS=${QBS:-/usr/local/Qt/Tools/QtCreator/bin/qbs}
QMAKE=${QMAKE:-${QTDIR}/bin/qmake}

export QBS_AUTOTEST_PROFILE=qt

$QBS build profile:qt
$QBS run -p qbs_app profile:qt -- setup-toolchains --detect
$QBS run -p qbs_app profile:qt -- setup-qt $QMAKE qt
$QBS run -p qbs_app profile:qt -- config defaultProfile qt
$QBS build -p "autotest-runner" profile:qt

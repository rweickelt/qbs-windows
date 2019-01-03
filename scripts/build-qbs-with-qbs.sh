#!/usr/bin/env bash

set -e

#
# Builds QBS and runs all autotests.
#
#

source /etc/profile

QT_VERSION=${QT_VERSION:-5.9.7}
QBS=${QBS:-/usr/local/Qt/Tools/QtCreator/bin/qbs}
QMAKE=${QMAKE:-${QTDIR}/bin/qmake}
QBS_AUTOTEST_PROFILE=qt

export QBS_AUTOTEST_PROFILE

$QBS build profile:qt
$QBS run -p qbs_app profile:qt -- setup-toolchains --detect
$QBS run -p qbs_app profile:qt -- setup-qt $QMAKE qt
$QBS run -p qbs_app profile:qt -- config defaultProfile qt
$QBS build -p "autotest-runner" profile:qt

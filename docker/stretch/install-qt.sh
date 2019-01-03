#!/usr/bin/env bash
set -e

#############################################################################
##
## Copyright (C) 2018 Richard Weickelt.
## Contact: https://www.qt.io/licensing/
##
## This file is part of Qbs.
##
## $QT_BEGIN_LICENSE:LGPL$
## Commercial License Usage
## Licensees holding valid commercial Qt licenses may use this file in
## accordance with the commercial license agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and The Qt Company. For licensing terms
## and conditions see https://www.qt.io/terms-conditions. For further
## information use the contact form at https://www.qt.io/contact-us.
##
## GNU Lesser General Public License Usage
## Alternatively, this file may be used under the terms of the GNU Lesser
## General Public License version 3 as published by the Free Software
## Foundation and appearing in the file LICENSE.LGPL3 included in the
## packaging of this file. Please review the following information to
## ensure the GNU Lesser General Public License version 3 requirements
## will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
##
## GNU General Public License Usage
## Alternatively, this file may be used under the terms of the GNU
## General Public License version 2.0 or (at your option) the GNU General
## Public license version 3 or any later version approved by the KDE Free
## Qt Foundation. The licenses are as published by the Free Software
## Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
## included in the packaging of this file. Please review the following
## information to ensure the GNU General Public License requirements will
## be met: https://www.gnu.org/licenses/gpl-2.0.html and
## https://www.gnu.org/licenses/gpl-3.0.html.
##
## $QT_END_LICENSE$
##
#############################################################################

test $# -eq 1 || { echo "Usage: $(basename "$0") <Qt version>" >&2; exit 1; }

#
# Install Qt framework from the official installer and removes examples and
# documentation.
# Tested with 5.9.7 and 5.12.0.
#
QT_VERSION=$1
QT_VERSION_MAJOR="$(echo ${QT_VERSION} | cut -d '.' -f 1)"
QT_VERSION_MINOR="$(echo ${QT_VERSION} | cut -d '.' -f 2)"
QT_VERSION_PATCH="$(echo ${QT_VERSION} | cut -d '.' -f 3)"
export QT_INSTALL_DIR="/usr/local/Qt"
export QTDIR="${QT_INSTALL_DIR}/${QT_VERSION}/gcc_64"

QT_URL=https://download.qt.io/official_releases/qt/${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}/${QT_VERSION}/qt-opensource-linux-x64-${QT_VERSION}.run

curl -L -o /qt-installer.run ${QT_URL}

chmod +x /qt-installer.run

/qt-installer.run --platform minimal --script "/install-qt.qs"

find ${QT_INSTALL_DIR}/Docs -not -name '*qdocconf' -type f -and -not -wholename '*/template/*' -type f -exec rm -f {} +
rm -rf ${QT_INSTALL_DIR}/Examples
rm -f /qt-installer.run
rm -f /qtifwsilent.qs

#
# Export for later when the entrypoint script switches from root to devel user.
#
echo "export PATH=\"${QTDIR}/bin:${QT_INSTALL_DIR}/Tools/QtCreator/bin:\${PATH}\"" > /etc/profile.d/qt-tools.sh
echo "export QTDIR=\"${QTDIR}\"" >> /etc/profile.d/qt-tools.sh

#!/usr/bin/env bash

if [ -z "$1" ]; then
    echo "This script requires a Qt version x.y.z as argument."
    exit 1
fi

set -eux

#
# Install Qt framework from the official installer.
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

rm -rf ${QT_INSTALL_DIR}/Docs
rm -rf ${QT_INSTALL_DIR}/Examples
rm -f /qt-installer.run
rm -f /qtifwsilent.qs

echo "export PATH=\"${QTDIR}/bin:${QT_INSTALL_DIR}/Tools/QtCreator/bin:\${PATH}\"" > /etc/profile.d/qt-tools.sh
echo "export QTDIR=\"${QTDIR}\"" >> /etc/profile.d/qt-tools.sh

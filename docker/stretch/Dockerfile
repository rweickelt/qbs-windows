FROM debian:9
LABEL Description="Debian development environment for Qbs with Qt 5.9 and various dependencies for testing Qbs modules and functionality"

#
# Allow colored output on command line.
#
ENV TERM=xterm-color

#
# Make it possible to change the user in the entrypoint script.
# The docker container usually runs as root user. This usually causes permission
# problems on files created during build in the project directory.
# Thus we create a user here who's UID will be changed in the entrypoint
# script to match the UID of the current host user.
#
ARG USER_UID=1000
ARG USER_NAME=devel
RUN apt-get update && apt-get install -y gosu && \
    groupadd -g ${USER_UID} ${USER_NAME} && \
    useradd -s /bin/bash -u ${USER_UID} -g ${USER_NAME} -o -c "" -m ${USER_NAME}
COPY entrypoint.sh entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]

#
# Dependencies of the Qt offline installer
#
RUN apt-get update && apt-get -y update && apt-get install -y \
    curl \
    libdbus-1-3 \
    libexpat1 \
    libfontconfig1 \
    libfreetype6 \
    libgl1-mesa-glx \
    libglib2.0-0 \
    libx11-6 \
    libx11-xcb1

#
# Install Qt and a prebuilt Qbs.
#
ARG QT_INSTALL_DIR=/usr/local/Qt
ENV QTDIR=${QT_INSTALL_DIR}/5.9.7/gcc_64
ENV PATH="/usr/local/Qt/Tools/QtCreator/bin:${PATH}"
COPY qtifwsilent.qs qtifwsilent.qs
RUN curl -L -O 'https://download.qt.io/official_releases/qt/5.9/5.9.7/qt-opensource-linux-x64-5.9.7.run' && \
    chmod +x qt-opensource-linux-x64-5.9.7.run && \
    ./qt-opensource-linux-x64-5.9.7.run --platform minimal --script qtifwsilent.qs && \
    rm -rf ${QT_INSTALL_DIR}/Docs && \
    rm -rf ${QT_INSTALL_DIR}/Examples && \
    rm -f qt-opensource-linux-x64-5.9.7.run \
    rm -f qtifwsilent.qs

#
# Install development tools
#
RUN apt-get update && apt-get install -y \
    g++ \
    gcc \
    git \
    help2man \
    python-pip && \
    pip install beautifulsoup4 lxml # for building the documentation

#
# Configure the pre-installed qbs instance
#
USER $USER_NAME
RUN qbs-setup-toolchains --detect && \
    qbs-setup-qt ${QTDIR}/bin/qmake qt

#
# Switch back to root user for the entrypoint script.
#
USER root

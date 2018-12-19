#!/usr/bin/env bash

#
# Try to determine the uid of the working directory and adjust the current
# user's uid/gid accordingly.
#
USER_GID=${USER_GID:-$(stat -c "%g" .)}
USER_UID=${USER_UID:-$(stat -c "%u" .)}
USER_NAME=${USER_NAME:-devel}
EXEC=""
export HOME=/home/${USER_NAME}

if [ $(id -u ${USER_NAME}) != "${USER_UID}"  ] && [ $(id -u ${USER_NAME}) != "0" ]; then
    usermod  -u ${USER_UID} ${USER_NAME}
    groupmod -g ${USER_GID} ${USER_NAME}
    chown -R -h ${USER_UID} /home;
    chgrp -R -h ${USER_GID} /home;
    EXEC="exec gosu ${USER_NAME}:${USER_NAME}"
fi

if [ -z "$1" ]; then
    ${EXEC} bash --login
else
    ${EXEC} "$@"
fi
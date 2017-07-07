#!/bin/bash

BASE="$(/bin/readlink -m $(/usr/bin/dirname "$0"))"

# read windows path
if [[ -r $BASE/env ]]; then
  . "$BASE/env"
fi

# /etc/pam.d/login like
if [[ -r /etc/environment ]]; then
  . /etc/environment
fi
if [[ -n $WINPATH ]]; then
  PATH="$PATH:$WINPATH"
fi
export PATH

if [[ -r /etc/default/locale ]]; then
  . /etc/default/locale
  export LANG
fi

ENT="$(getent passwd "$UID")"
export USER="$(cut -d: -f1 <<<"$ENT")"
export LOGNAME="$USER"
export HOME="$(cut -d: -f6 <<<"$ENT")"
export SHELL="$(cut -d: -f7 <<<"$ENT")"

cd "$HOME"
exec "$SHELL" --login

#!/bin/bash
BASE="$(readlink -m $(dirname "$0"))"
if [[ $PATH =~ :(/mnt/[a-z].+)$ ]]; then
  echo "WINPATH=\"${BASH_REMATCH[1]}\"" >"$BASE/env"
fi
exec "$BASE/src/main" -d 127.0.0.1 10023 "$BASE/telnetd" -L "$BASE/login"

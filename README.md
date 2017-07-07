# wsltelnetd
telnetd for bash on windows

# How to use

1. get this repository
2. run run.sh from cmd.exe

```console
c:\User\exmaple> bash.exe ~ -c "/path/to/run.sh"
ipv4: addr:127.0.0.1, port:10023
```

3. login to 127.0.0.1:10023 by telnet client

# file

## run.sh
startup script

## src/main

lightweight inetd server (not required root privilege)

## telnetd

this telnetd binary is patched that WSL is not implemented TCP OOB flag operation.(issue: https://github.com/Microsoft/BashOnWindows/issues/989 )

see telnetd-disable-oob.patch

### Source

Original: http://www.hcs.harvard.edu/~dholland/computers/netkit.html
Debian: https://packages.debian.org/source/sid/netkit-telnet
Ubuntu: https://launchpad.net/netkit-telnet

## login

dummy login(1) (see also man 1 login)


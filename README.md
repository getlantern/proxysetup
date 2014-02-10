Overview
--------

proxysetup runs the /usr/sbin/networksetup utility using whatever parameters
were passed to the program.  This is useful if you want to be able to run
networksetup and make network changes without having to sudo or supply your
password interactively.

To do so, make root own proxysetup and set the setuid bit to allow anyone to execute
it as root.

```
chown root:wheel proxysetup
chmod 4755 proxysetup
```

Since proxysetup is intended primarily for managing proxy settings, it
only allows the following networksetup commands to be run:

```
-listallnetworkservices
-getwebproxy
-setwebproxy
-setwebproxystate
-getsecurewebproxy
-setsecurewebproxy
-setsecurewebproxystate
-getautoproxyurl
-setautoproxyurl
-setautoproxystate
-getproxybypassdomains
-setproxybypassdomains
-help
-printcommands
```

Building
--------

```
git clone https://github.com/oxtoacart/proxysetup.git
make
```
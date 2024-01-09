# Media Controller Inspector

This is base on a [project written in 2010](https://gitorious.org/mci/mci) that
aims to show and interact with
[media devices](https://www.kernel.org/doc/html/v6.4/driver-api/media/mc-core.html) in Linux.

It is a C++ application using the Qt framework.

# Building

To build this project, you need Qt 5 at least and Qt development files installed.
You also need the linux kernel headers.

Run:
```
qmake5 -makefile
make
```

Then `mci` can be run. It shows all detected devices as well as a fake device.


# ToyJVM

Install [libzip](https://github.com/nih-at/libzip). (see [INSTALL.md](https://github.com/nih-at/libzip/blob/master/INSTALL.md))

#### error while loading shared libraries: libzip.so.5: cannot open shared object file: No such file or directory:
```
$ LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/my_library
$ export LD_LIBRARY_PATH
```

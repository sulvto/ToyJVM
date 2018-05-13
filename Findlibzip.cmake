# Find libzip

MESSAGE(STATUS "Using bundled Findlibzip.cmake...")

FIND_PATH(
        LIBZIP_INCLUDE_DIR
        zip.h
        /usr/include/
        /usr/local/include/ )

FIND_LIBRARY(
        LIBZIP_LIBRARY NAMES  libzip.so
        PATHS /usr/lib/ /usr/local/lib/ /usr/lib64/ /usr/local/lib64/)


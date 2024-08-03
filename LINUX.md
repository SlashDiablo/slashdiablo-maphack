# It's time to crosscompile stuff

## Setup

Based on this question and answer https://stackoverflow.com/questions/63178407/cmake-compile-in-linux-execute-in-windows

Using mingw-w64-cmake (https://www.mingw-w64.org/)

Arch: https://aur.archlinux.org/packages/mingw-w64-cmake

## Building

regular `cmake` commands are replaced with the windows compatible `x86_64-w64-mingw32-cmake`

```
mkdir build
cd build
x86_64-w64-mingw32-cmake -DBUILD_SHARED_LIBS=TRUE -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE ..



```
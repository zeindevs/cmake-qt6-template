# cmake-qt6-template

## Setup

### Shared (MSYS2)

```sh
# Install Qt6 Lib
pacman -S mingw-w64-ucrt-x86_64-qt6-base

cd build
mkdir msys && cd msys
cmake -G "Ninja" ..\.. -DCMAKE_BUILD_TYPE="Debug" # for Debug
cmake -G "Ninja" ..\.. -DCMAKE_BUILD_TYPE="Release" # for Release
```

### Static (MSVC)

```sh
# Download Qt6 Static from https://github.com/gmh5225/static-build-qt6/releases/tag/qt6_660_static

cd build
mkdir msvc && cd msvc
cmake -G "Visual Studio 17 2022" ..\.. -DCMAKE_CONFIGURATION_TYPES="Release"
cmake --build . --config Release
cmake --install .
```

## Run

```sh
# msys
make run-debug
make run-release

# msvc
make run-static-release
```

## License

Copyright (c) 2024 zeindevs. Licensed under The MIT License

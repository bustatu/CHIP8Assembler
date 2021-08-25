# CHIP8 Assembler

## How to build

First you need to install *vcpkg*.

Depending on your platform, make a build file called *build.sh* or *build.bat* with the following contents, changing the contents in <> to fit your requirements:

```shell
mkdir build
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=<Path to vcpkg>/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=<Release \ Debug>
cmake --build build
```

After executing this, the executable should be in the */build/* file.

## Currently included sources:

- (WIP) https://github.com/dmatlack/chip8/blob/master/roms/programs/Minimal%20game%20%5BRevival%20Studios%2C%202007%5D.ch8

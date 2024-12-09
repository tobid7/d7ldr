# D7LDR

Nintendo 3ds Homebrew Library to Set 3DSX Executable to launch on Next App Exit

**THIS WILL NOT WORK FROM CIA LAUNCHED APPS!!!**

**NO HAX 2.x SUPPORT FOR NOW!!!**

For C there is a C Wrapper called `d7ldr.h`

## Building

To build this Project you need the following Packages

```bash
(dkp-)pacman -S 3ds-dev 3ds-cmake 3ds-portlibs
# Portlibs is optional but you should have them installed as well
```

After getting the Packages installed its just

```bash
mkdir -p build                          # create build dir
cd build                                # go into build dir
cmake .. -DCMAKE_BUILD_TYPE=Release     # generate build files (optional BUILD_TYPE could be Debug)
make                                    # build the library
make install                            # install to portlibs dir
```

## Credits

- [tobid7](https://github.com/tobid7): Main Dev of this LIB
- [devkitpro](https://github.com/devkitpro): (fincs) 3ds-hbmenu for the codebase of loader / rosalina
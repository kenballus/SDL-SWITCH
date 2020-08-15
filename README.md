# SDL-SWITCH
SDL 1.2.15 port for Nintendo Switch

This is a fork of [nop90's SDL-SWITCH](https://github.com/Nop90-Switch/SDL-SWITCH). His is no longer maintained, so I merged the PRs and fixed a couple things and am putting this up.

## Build instructions:

-- Get the devkitpro switch toolchain set up. (Instructions are available on devkitpro's website)

-- Stick [this file](https://raw.githubusercontent.com/switchbrew/libnx/e04f311dd4dd8c986db65693d0bce6c5abcfbb8f/nx/source/display/gfx.c) and [this file](https://raw.githubusercontent.com/switchbrew/libnx/e04f311dd4dd8c986db65693d0bce6c5abcfbb8f/nx/include/switch/display/gfx.h) in $DEVKITPRO/libnx/include/switch/display/.

-- Add ```#include "switch/display/gfx.h``` to $DEVKITPRO/libnx/include/switch/switch.h, right before the rest of the graphics headers.

-- Run make && make install

Basically, we're just undoing the [commit in which the old gfx API was removed](https://github.com/switchbrew/libnx/commit/e708372dcab2d555d9d7d3d64222486cc087c096) because nop90's SDL port uses it.

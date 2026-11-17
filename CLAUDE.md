# rpi5cpc: the Amstrad CPC on the Raspberry Pi 5

esp32cpc's CPC (`../esp32cpc/components/cpc`, platform independent) on the
rpi5emu runtime (`../rpi5emu`, its CLAUDE.md: the workflow, the Pi, the
lessons), the Z80 (`CONFIG_Z80_TIMING_CPC`) and uPD765 esp32emu's. The
machine's own behaviour, lessons and tests are esp32cpc's CLAUDE.md; this
project is the glue.

## Layout

| Path | What |
|---|---|
| `src/main.c` | The CPC as an `emu_machine_t`: esp32cpc's `main/main.c` through `../rpi5emu/tools/port_glue.py`, then the ROM message, `shutdown()` |
| `src/settings.c` | esp32cpc's, over `emu/nvs.h` (section `cpc`: `model`) |
| `src/rom_store.c` | `~/rpi5emu/cpc/roms/` through `emu_rom_read()`: os464.rom ... system.cpr |

Keep `src/main.c` in step with esp32cpc's `main/main.c`.

## Build, run, check

```sh
../rpi5emu/tools/pi.sh rpi5cpc build
../rpi5emu/tools/pi.sh rpi5cpc headless     # or run: the window here
../rpi5emu/tools/console.sh i 'T CAT\n'
../rpi5emu/tools/pi.sh rpi5cpc shot out.png
```

Console: the runtime's (`h`) and esp32cpc's: `k <n>` tap key n (line * 8
+ bit, 18 RETURN), `K <n> 0|1`, `T <text>` (`\n` RETURN), `j <bits>`
(1 up 2 down 4 left 8 right 16 fire 32 fire 1), `m <dx> <dy> <btn>`,
`R <model>` restart as 0 464, 1 664, 2 6128, 3 464 Plus, 4 6128 Plus.

Checked on the Pi (2026-11-15, headless): the 6128 at 100% (the emulation
thread ~3-4% of a core), BASIC 1.1 typed into; a blank disk made, a
program saved and CAT (TEST.BAS, 177K free), the file in the image after
quitting; the 6128 Plus's system cartridge menu. Not yet: the window by
hand, sound heard, games, CP/M.

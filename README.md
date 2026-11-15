# rpi5cpc

An Amstrad CPC 464, 664, 6128, 464 Plus and 6128 Plus for the Raspberry
Pi 5, in a window of its own: [esp32cpc](https://github.com/rlucencic/esp32cpc)'s
CPC on the [rpi5emu](https://github.com/rlucencic/rpi5emu) runtime.

- The Z80 with the CPC's real timing, the CRTC, the Gate Array, the AY,
  the uPD765 with DSK disks; the Plus's hardware sprites and 4096 colours,
  cartridges (CPR); an AMX mouse.
- The setup screen (model, sound, the drives), the web page for the disk
  images, the console, as the rest of the family.

## Building

See [rpi5emu](https://github.com/rlucencic/rpi5emu#building): esp32emu,
rpi5emu, esp32cpc and rpi5cpc cloned side by side, then

```sh
cd rpi5cpc && cmake -S . -B build -G Ninja && cmake --build build
```

## ROMs

In the data folder's `roms/` (`~/rpi5emu/roms`), named as esp32cpc's:
`os464.rom`, `basic10.rom`, `os664.rom`, `basic664.rom`, `os6128.rom`,
`basic11.rom`, `amsdos.rom` (16 KB each); for the Plus `system.cpr`, or
`osplus.rom` and `basicplus.rom`. Not part of this repository.

## Running

```sh
build/rpi5cpc                         # the setup screen first
build/rpi5cpc -S --choice Model=6128  # straight into a 6128
build/rpi5cpc game.dsk                # with a disk in A:
```

Disks and cartridges live in `~/rpi5emu/cpc/`. Keys by position (a UK or
US keyboard onto the CPC's): F1-F10 the CPC's f1-f0 keypad keys, Insert
COPY, Delete CLR; the numeric keypad is joystick 0 (8 4 6 2, 0 or 5 fire);
F12 makes the cursor keys the joystick too (Alt fire). A mouse (AMX) after
a click in the window.

## Licence

MIT.

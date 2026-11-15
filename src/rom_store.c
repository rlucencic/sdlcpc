#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emu/emu.h"
#include "rom_store.h"

static const char *const names[ROM_COUNT] = {
    "os464.rom", "basic10.rom", "os664.rom", "basic664.rom", "os6128.rom", "basic11.rom",
    "amsdos.rom", "osplus.rom", "basicplus.rom",
};

const char *rom_store_name(rom_id_t id)
{
    return id < ROM_COUNT ? names[id] : "";
}

/* Something there: not erased, not zeros */
static bool plausible(const uint8_t *p)
{
    bool ff = true, zero = true;
    for (int i = 0; i < 64; i++) {
        ff &= p[i] == 0xFF;
        zero &= p[i] == 0x00;
    }
    return !ff && !zero;
}

bool rom_store_load(rom_id_t id, uint8_t *buf)
{
    return id < ROM_COUNT && emu_rom_read(names[id], buf, CPC_ROM_SIZE) == CPC_ROM_SIZE && plausible(buf);
}

uint32_t rom_store_system_cart(uint8_t *pages, const char **name)
{
    uint32_t size = 0;
    uint8_t *file = malloc(CPC_CART_MAX + 4096);
    long n = file ? emu_rom_read("system.cpr", file, CPC_CART_MAX + 4096) : -1;
    if (n > 0) {
        size = cpc_cpr_pages(file, n, pages);
    }
    free(file);
    if (size) {
        *name = "system cartridge";
        return size;
    }
    memset(pages, 0xFF, 4 * CPC_ROM_SIZE);
    if (rom_store_load(ROM_OSPLUS, pages) && rom_store_load(ROM_BASICPLUS, pages + CPC_ROM_SIZE)) {
        rom_store_load(ROM_AMSDOS, pages + 3 * CPC_ROM_SIZE);
        *name = "OS and BASIC (Plus)";
        return 4 * CPC_ROM_SIZE;
    }
    return 0;
}

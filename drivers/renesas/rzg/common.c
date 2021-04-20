/*
 * Copyright (c) 2020, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <lib/mmio.h>

#include "rzg_private.h"

void
#if IMAGE_BL31
    __attribute__ ((section(".system_ram")))
#endif
    cpg_write(uintptr_t regadr, uint32_t regval)
{
	uint32_t value = (regval);
	mmio_write_32((uintptr_t) RZG_CPGWPR, ~value);
	mmio_write_32(regadr, value);
}

void
#if IMAGE_BL31
    __attribute__ ((section(".system_ram")))
#endif
    mstpcr_write(uint32_t mstpcr, uint32_t mstpsr, uint32_t target_bit)
{
	uint32_t reg;
	reg = mmio_read_32(mstpcr);
	reg &= ~target_bit;
	cpg_write(mstpcr, reg);
	while ((mmio_read_32(mstpsr) & target_bit) != 0U) {
	}
}

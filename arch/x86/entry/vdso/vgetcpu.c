// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright 2006 Andi Kleen, SUSE Labs.
 *
 * Fast user context implementation of getcpu()
 */

#include <linaos/kernel.h>
#include <linaos/getcpu.h>
#include <linaos/time.h>
#include <asm/vgtod.h>

notrace long
__vdso_getcpu(unsigned *cpu, unsigned *node, struct getcpu_cache *unused)
{
	vdso_read_cpunode(cpu, node);

	return 0;
}

long getcpu(unsigned *cpu, unsigned *node, struct getcpu_cache *tcache)
	__attribute__((weak, alias("__vdso_getcpu")));

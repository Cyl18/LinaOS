// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#include <linaos/clocksource.h>
#include <linaos/of_clk.h>

void __init time_init(void)
{
	of_clk_init(NULL);
	timer_probe();
}

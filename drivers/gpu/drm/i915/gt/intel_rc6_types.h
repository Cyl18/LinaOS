/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef INTEL_RC6_TYPES_H
#define INTEL_RC6_TYPES_H

#include <linaos/spinlock.h>
#include <linaos/types.h>

#include "intel_engine_types.h"

struct drm_i915_gem_object;

struct intel_rc6 {
	u64 prev_hw_residency[4];
	u64 cur_residency[4];

	u32 ctl_enable;

	struct drm_i915_gem_object *pctx;

	bool supported : 1;
	bool enabled : 1;
	bool manual : 1;
	bool wakeref : 1;
};

#endif /* INTEL_RC6_TYPES_H */

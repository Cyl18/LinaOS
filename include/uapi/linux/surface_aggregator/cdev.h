/* SPDX-License-Identifier: GPL-2.0+ WITH LinaOS-syscall-note */
/*
 * Surface System Aggregator Module (SSAM) user-space EC interface.
 *
 * Definitions, structs, and IOCTLs for the /dev/surface/aggregator misc
 * device. This device provides direct user-space access to the SSAM EC.
 * Intended for debugging and development.
 *
 * Copyright (C) 2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#ifndef _UAPI_LINUX_SURFACE_AGGREGATOR_CDEV_H
#define _UAPI_LINUX_SURFACE_AGGREGATOR_CDEV_H

#include <linaos/ioctl.h>
#include <linaos/types.h>

/**
 * enum ssam_cdev_request_flags - Request flags for SSAM cdev request IOCTL.
 *
 * @SSAM_CDEV_REQUEST_HAS_RESPONSE:
 *	Specifies that the request expects a response. If not set, the request
 *	will be directly completed after its underlying packet has been
 *	transmitted. If set, the request transport system waits for a response
 *	of the request.
 *
 * @SSAM_CDEV_REQUEST_UNSEQUENCED:
 *	Specifies that the request should be transmitted via an unsequenced
 *	packet. If set, the request must not have a response, meaning that this
 *	flag and the %SSAM_CDEV_REQUEST_HAS_RESPONSE flag are mutually
 *	exclusive.
 */
enum ssam_cdev_request_flags {
	SSAM_CDEV_REQUEST_HAS_RESPONSE = 0x01,
	SSAM_CDEV_REQUEST_UNSEQUENCED  = 0x02,
};

/**
 * struct ssam_cdev_request - Controller request IOCTL argument.
 * @target_category: Target category of the SAM request.
 * @target_id:       Target ID of the SAM request.
 * @command_id:      Command ID of the SAM request.
 * @instance_id:     Instance ID of the SAM request.
 * @flags:           Request flags (see &enum ssam_cdev_request_flags).
 * @status:          Request status (output).
 * @payload:         Request payload (input data).
 * @payload.data:    Pointer to request payload data.
 * @payload.length:  Length of request payload data (in bytes).
 * @response:        Request response (output data).
 * @response.data:   Pointer to response buffer.
 * @response.length: On input: Capacity of response buffer (in bytes).
 *                   On output: Length of request response (number of bytes
 *                   in the buffer that are actually used).
 */
struct ssam_cdev_request {
	__u8 target_category;
	__u8 target_id;
	__u8 command_id;
	__u8 instance_id;
	__u16 flags;
	__s16 status;

	struct {
		__u64 data;
		__u16 length;
		__u8 __pad[6];
	} payload;

	struct {
		__u64 data;
		__u16 length;
		__u8 __pad[6];
	} response;
} __attribute__((__packed__));

#define SSAM_CDEV_REQUEST	_IOWR(0xA5, 1, struct ssam_cdev_request)

#endif /* _UAPI_LINUX_SURFACE_AGGREGATOR_CDEV_H */

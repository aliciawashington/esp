// Copyright (c) 2011-2021 Columbia University, System Level Design Group
// SPDX-License-Identifier: Apache-2.0
#ifndef __ESP_CFG_000_H__
#define __ESP_CFG_000_H__

#include "libesp.h"
#include "2048_stratus.h"

typedef int64_t token_t;

/* <<--params-def-->> */
#define ROW 1
#define BOARD 1

/* <<--params-->> */
const int32_t row = ROW;
const int32_t board = BOARD;

#define NACC 1

struct 2048_stratus_access 2048_cfg_000[] = {
	{
		/* <<--descriptor-->> */
		.row = ROW,
		.board = BOARD,
		.src_offset = 0,
		.dst_offset = 0,
		.esp.coherence = ACC_COH_NONE,
		.esp.p2p_store = 0,
		.esp.p2p_nsrcs = 0,
		.esp.p2p_srcs = {"", "", "", ""},
	}
};

esp_thread_info_t cfg_000[] = {
	{
		.run = true,
		.devname = "2048_stratus.0",
		.ioctl_req = 2048_STRATUS_IOC_ACCESS,
		.esp_desc = &(2048_cfg_000[0].esp),
	}
};

#endif /* __ESP_CFG_000_H__ */

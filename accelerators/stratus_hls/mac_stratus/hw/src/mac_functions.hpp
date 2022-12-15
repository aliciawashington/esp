// Copyright (c) 2011-2021 Columbia University, System Level Design Group
// SPDX-License-Identifier: Apache-2.0

#include "mac.hpp"
#include "mac_datatypes.hpp"

// Optional application-specific helper functions
static inline void print_board(board_t board) {
    int i,j;
    for(i=0; i<4; i++) {
        for(j=0; j<4; j++) {
            uint8_t powerVal = (board) & 0xf;
            printf("%6u", (powerVal == 0) ? 0 : 1 << powerVal);
            board >>= 4;
        }
        printf("\n");
    }
    printf("\n");
}

static inline board_t unpack_col(row_t row) {
    board_t tmp = row;
    return (tmp | (tmp << 12ULL) | (tmp << 24ULL) | (tmp << 36ULL)) & COL_MASK;
}
static inline row_t reverse_row(row_t row) {
    return (row >> 12) | ((row >> 4) & 0x00F0)  | ((row << 4) & 0x0F00) | (row << 12);
}


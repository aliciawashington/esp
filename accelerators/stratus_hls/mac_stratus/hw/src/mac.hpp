// Copyright (c) 2011-2021 Columbia University, System Level Design Group
// SPDX-License-Identifier: Apache-2.0

#ifndef __MAC_HPP__
#define __MAC_HPP__

#include "mac_conf_info.hpp"
#include "mac_debug_info.hpp"

#include "esp_templates.hpp"

#include "mac_directives.hpp"

#define __round_mask(x, y) ((y)-1)
#define round_up(x, y) ((((x)-1) | __round_mask(x, y))+1)
/* <<--defines-->> */
//#define DATA_WIDTH 32
#define DATA_WIDTH 64
#define DMA_SIZE SIZE_WORD
#define PLM_OUT_WORD 100
#define PLM_IN_WORD 6400

class mac : public esp_accelerator_3P<DMA_WIDTH>
{
public:
    // Constructor
    SC_HAS_PROCESS(mac);
    mac(const sc_module_name& name)
    : esp_accelerator_3P<DMA_WIDTH>(name)
        , cfg("config")
    {
        // Signal binding
        cfg.bind_with(*this);

        // Map arrays to memories
        /* <<--plm-bind-->> */
        HLS_MAP_plm(plm_out_pong, PLM_OUT_NAME);
        HLS_MAP_plm(plm_out_ping, PLM_OUT_NAME);
        HLS_MAP_plm(plm_in_pong, PLM_IN_NAME);
        HLS_MAP_plm(plm_in_ping, PLM_IN_NAME);
    }

    // Processes

    // Load the input data
    void load_input();

    // Computation
    void compute_kernel();

    // Store the output data
    void store_output();

    // Configure mac
    esp_config_proc cfg;

    // Functions
    
    //initialize the game board
    void init_tables();

    float score_heur_board(board_t board);
    // score a single board actually (adding in the score from spawned 4 tiles)
    float score_board(board_t board);
    // score over all possible moves
    float score_move_node(eval_state &state, board_t board, float cprob);
    // score over all possible tile choices and placements
    float score_tilechoose_node(eval_state &state, board_t board, float cprob);


    float score_toplevel_move(board_t board, int move);
    int find_best_move(board_t board);
    int ask_for_move(board_t board);
    void play_game(get_move_func_t get_move);



    // Private local memories
    sc_dt::sc_int<DATA_WIDTH> plm_in_ping[PLM_IN_WORD];
    sc_dt::sc_int<DATA_WIDTH> plm_in_pong[PLM_IN_WORD];
    sc_dt::sc_int<DATA_WIDTH> plm_out_ping[PLM_OUT_WORD];
    sc_dt::sc_int<DATA_WIDTH> plm_out_pong[PLM_OUT_WORD];

};


#endif /* __MAC_HPP__ */
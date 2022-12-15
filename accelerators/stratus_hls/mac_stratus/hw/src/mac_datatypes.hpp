/* Copyright 2021 Columbia University, SLD Group */

//
// conv_layer_datatypes - Paolo Mantovani
//

#include "systemc.h"

#ifndef __MAC_DATATYPES_H__
#define __MAC_DATATYPES_H__

#ifndef mac_conf_t_SC_WRAPPER_TYPE
#define mac_conf_t_SC_WRAPPER_TYPE 1

typedef sc_uint<64> board_t;
typedef sc_uint<16> row_t;

typedef int (*get_move_func_t)(board_t);

typedef std::unordered_map<board_t, trans_table_entry_t> trans_table_t;

const board_t ROW_MASK = 0xFFFFULL;
const board_t COL_MASK = 0x000F000F000F000FULL;

struct trans_table_entry_t{
    uint8_t depth;
    float heuristic;

    trans_table_entry_t() {}

    trans_table_entry_t(const trans_table_entry_t &other) {
            depth = other.depth;
            heuristic = other.heuristic;
        }

    trans_table_entry_t(uint8_t depth_in, uint32_t heuristic_in) {
        depth = depth_in;
        heuristic = heuristic_in;
    }

    inline bool operator==(const trans_table_entry_t &other) {
        if (depth != other.depth)
            return false;
        if (heuristic != other.heuristic)
            return false;
        return true;
    }

    inline trans_table_entry_t &operator=(const trans_table_entry_t &other) {
        depth = other.depth;
        heuristic = other.heuristic;
        return *this;
    }

    friend void sc_trace(sc_trace_file *tf, const trans_table_entry_t &object, const std::string &in_name) {
        sc_trace(tf, object.depth, in_name + std::string(".depth"));
        sc_trace(tf, object.heuristic, in_name + std::string(".heuristic"));
    }

    friend ostream &operator<<(ostream &os, const trans_table_entry_t &object) {
        os << "( ";
        os << object.depth << " ";
        os << object.heuristic << " ";
        os << ")";
        return os;
    }
    
};

struct eval_state {
    trans_table_t trans_table; // transposition table, to cache previously-seen moves
    int maxdepth;
    int curdepth;
    int cachehits;
    unsigned long moves_evaled;
    int depth_limit;

    eval_state() : maxdepth(0), curdepth(0), cachehits(0), moves_evaled(0), depth_limit(0) {
    }

    eval_state() {}

    eval_state(const eval_state &other)
    {
        trans_table = other.trans_table;
        maxdepth = other.maxdepth;
        curdepth = other.curdepth;
        cachehits = other.cachehits;
        moves_evaled = other.moves_evaled;
        depth_limit = other.depth_limit;
    }

    eval_state(trans_table_t trans_table_in, int maxdepth_in, int curdepth_in, int cachehits_in, unsigned long moves_evaled_in, int depth_limit_in)
    {
        trans_table = trans_table_in;
        maxdepth = maxdepth_in;
        curdepth = curdepth_in;
        cachehits = cachehits_in;
        moves_evaled = moves_evaled_in;
        depth_limit = depth_limit_in;
    }

    inline bool operator==(const eval_state &other)
    {
        if (trans_table != other.trans_table)
            return false;
        if (maxdepth != other.maxdepth)
            return false;
        if (curdepth != other.curdepth)
            return false;
        if (cachehits != other.cachehits)
            return false;
        if (moves_evaled != other.moves_evaled)
            return false;
        if (depth_limit != other.depth_limit)
            return false;
        return true
    }

    inline eval_state &operator=(const eval_state &other)
    {
        trans_table = other.trans_table;
        maxdepth = other.maxdepth;
        curdepth = other.curdepth;
        cachehits = other.cachehits;
        moves_evaled = other.moves_evaled;
        depth_limit = other.depth_limit;
        return *this;
    }

    friend void sc_trace(sc_trace_file *tf, const eval_state &object, const std::string &in_name)
    {
        sc_trace(tf, object.trans_table, in_name + std::string(".trans_table"));
        sc_trace(tf, object.maxdepth, in_name + std::string(".maxdepth"));
        sc_trace(tf, object.curdepth, in_name + std::string(".curdepth"));
        sc_trace(tf, object.cachehits, in_name + std::string(".cachehits"));
        sc_trace(tf, object.moves_evaled, in_name + std::string(".moves_evaled"));
        sc_trace(tf, object.depth_limit, in_name + std::string(".depth_limit"));
    }

    friend ostream &operator<<(ostream &os, const eval_state &object)
    {
        os << "( ";
        os << object.trans_table << " ";
        os << object.maxdepth << " ";
        os << object.curdepth << " ";
        os << object.cachehits << " ";
        os << object.moves_evaled << " ";
        os << object.depth_limit << " ";
        os << ")";
        return os;
    }
};


#endif // mac_conf_t_SC_WRAPPER_TYPE

#endif // __MAC_DATATYPES_H__
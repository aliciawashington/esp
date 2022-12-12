/* Copyright 2021 Columbia University, SLD Group */

//
// conv_layer_datatypes - Paolo Mantovani
//

#include "systemc.h"

#ifndef __MAC_DATATYPES_H__
#define __MAC_DATATYPES_H__

#ifndef mac_conf_t_SC_WRAPPER_TYPE
#define mac_conf_t_SC_WRAPPER_TYPE 1


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

#endif // trans_table_entry_t_SC_WRAPPER_TYPE

#endif // __CONV_LAYER_DATATYPES_H__
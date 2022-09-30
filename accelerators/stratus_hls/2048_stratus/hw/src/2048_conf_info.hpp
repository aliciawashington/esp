// Copyright (c) 2011-2021 Columbia University, System Level Design Group
// SPDX-License-Identifier: Apache-2.0

#ifndef __2048_CONF_INFO_HPP__
#define __2048_CONF_INFO_HPP__

#include <systemc.h>

//
// Configuration parameters for the accelerator.
//
class conf_info_t
{
public:

    //
    // constructors
    //
    conf_info_t()
    {
        /* <<--ctor-->> */
        this->row = 1;
        this->board = 1;
    }

    conf_info_t(
        /* <<--ctor-args-->> */
        int32_t row, 
        int32_t board
        )
    {
        /* <<--ctor-custom-->> */
        this->row = row;
        this->board = board;
    }

    // equals operator
    inline bool operator==(const conf_info_t &rhs) const
    {
        /* <<--eq-->> */
        if (row != rhs.row) return false;
        if (board != rhs.board) return false;
        return true;
    }

    // assignment operator
    inline conf_info_t& operator=(const conf_info_t& other)
    {
        /* <<--assign-->> */
        row = other.row;
        board = other.board;
        return *this;
    }

    // VCD dumping function
    friend void sc_trace(sc_trace_file *tf, const conf_info_t &v, const std::string &NAME)
    {}

    // redirection operator
    friend ostream& operator << (ostream& os, conf_info_t const &conf_info)
    {
        os << "{";
        /* <<--print-->> */
        os << "row = " << conf_info.row << ", ";
        os << "board = " << conf_info.board << "";
        os << "}";
        return os;
    }

        /* <<--params-->> */
        int32_t row;
        int32_t board;
};

#endif // __2048_CONF_INFO_HPP__

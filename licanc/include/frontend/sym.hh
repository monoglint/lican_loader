#pragma once

#include <deque>

#include "base.hh"

namespace frontend::sym {
    enum class t_sym_type {};

    using t_sym_id = u64;
    using t_sym_ids = std::deque<t_sym_id>;

    struct t_sym {
        t_sym(t_sym_type type)
            : type(type) {}

        t_sym_type type;
    };

    struct t_symbol_table {

    };
}
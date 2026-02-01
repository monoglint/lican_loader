/*

used for processing the frontend and spitting out something final for the code generator to use

*/

#pragma once

#include <string>

#include "frontend/token.hh"
#include "frontend/ast.hh"
#include "frontend/sym.hh"

namespace frontend::delivery {
    struct t_log {
        std::string message;
    };

    struct t_compilation_file {
        std::string source_code;
        ast::t_ast ast;
        sym::t_symbol_table symbol_table;
    };

    // DELIVERY OUTPUT
    struct t_compilation_unit {
        std::vector<t_compilation_file> files;
    };

    // DELIVERY INPUT
    struct t_delivery_config {
        const std::string directory_path;
        // more info like flags etc.
    };

    t_compilation_unit deliver_that_shit(const t_delivery_config& config);
};
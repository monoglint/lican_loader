/*

used for processing the frontend and spitting out something final for the code generator to use

*/

#pragma once

#include <string>

#include "frontend/token.hh"
#include "frontend/ast.hh"
#include "frontend/sym.hh"

namespace frontend::manager {
    struct t_log {
        std::string message;
    };

    struct t_compilation_file {
        t_compilation_file(std::string path, std::string source_code)
            : path(std::move(path)), source_code(std::move(source_code)) {}

        std::string path;
        std::string source_code;
        ast::t_ast ast;
        sym::t_symbol_table symbol_table;
    };

    using t_file_id = size_t; // index of t_compilation_file in t_compilation_unit::files

    // DELIVERY INPUT
    struct t_frontend_config {
        // all of this is temporary, so cd does not matter... only as long as cd stays consistent throughout the run of the entire program
        const std::string project_path;

        // path to the starting point file.
        const std::string start_subpath;
        // more info like flags etc.
    };

    // DELIVERY OUTPUT
    struct t_compilation_unit {
        std::string project_path;

        t_file_id add_file(std::string path);
        t_compilation_file& get_file(size_t file_id);
    private:
        std::vector<t_compilation_file> files;
    };

    t_compilation_unit compile_that_shit(const t_frontend_config& config);
};
#pragma once

#include <string>

#include "sym.hh"
#include "ast.hh"

namespace frontend::semantic_analyzer {
    struct t_analyzer_state {
        t_analyzer_state(ast::t_ast& ast)
            : ast(ast) {}

        // input information
        
        // remember: analyzer can modify the ast, especially for template instantiation
        ast::t_ast& ast; 

        // stuff the lexer uses

        sym::t_symbol_table symbol_table;
    };

    void analyze(t_analyzer_state& analyzer_state);
}
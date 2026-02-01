#pragma once

#include <string>

#include "sym.hh"
#include "ast.hh"

namespace frontend::semantic_analyzer {
    struct t_analyzer_state {
        // input information
        
        const std::string source_code;
        const ast::t_ast ast;

        // stuff the lexer uses

        u32 ptr = 0; // dont name it like this, this is example for later
        token::t_token_list& tokens;
    };

    sym::t_symbol_table analyze(t_analyzer_state& parser_state);
}
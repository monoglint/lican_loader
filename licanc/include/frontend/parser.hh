#pragma once

#include <string>

#include "base.hh"
#include "frontend/ast.hh"

namespace frontend::parser {
    struct t_parser_state {
        // input information
        
        const std::string& source_code;
        const token::t_token_list& tokens;

        // stuff the parser uses

        u32 ptr = 0; // dont name it like this, this is example for later
    };

    ast::t_ast parse(t_parser_state& parser_state);
}
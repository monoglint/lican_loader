#pragma once

#include <string>

#include "base.hh"
#include "frontend/token.hh"

namespace frontend::lexer {
    struct t_lexer_state {
        // input information
        
        const std::string& source_code;

        // stuff the lexer uses

        u32 ptr = 0; // dont name it like this, this is example for later
        token::t_token_list& tokens;
    };

    token::t_token_list lex(t_lexer_state& lexer_state);
}
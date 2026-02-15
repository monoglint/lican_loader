#pragma once

#include <string>

#include "base.hh"
#include "frontend/ast.hh"

namespace frontend::parser {
    struct t_parser_state {
        t_parser_state(const std::string& source_code, const token::t_token_list& tokens)
            : source_code(source_code), tokens(tokens) {}

        // input information
        
        const std::string& source_code;
        const token::t_token_list& tokens;

        // stuff the parser uses

        u32 ptr = 0;
        ast::t_ast ast;

        // keep track of any import "statements" to preemptively load any modules
        ast::t_node_ids import_node_ids;
    };

    void parse(t_parser_state& parser_state);
    void build_test_ast(t_parser_state& parser_state);
}
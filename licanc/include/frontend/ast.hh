#pragma once

#include <vector>
#include <variant>

#include "base.hh"
#include "frontend/token.hh"

namespace frontend::ast {
    enum class t_ast_node_type {
        // -- EXPRESSIONS

        // embeddable

        EXPR_IDENTIFIER,
        EXPR_UNARY,
        EXPR_BINARY,
        EXPR_TERNARY,

        // -- EXPRESSION DEPENDENT MISC

        TYPE,

        // -- ITEMS

        ITEM_DECLARATION,
        ITEM_TYPE_DECLARATION,
        
        // -- STATEMENTS

        // control flow

        STMT_IF,
        STMT_WHILE,
        STMT_FOR,
        STMT_EXPRESSION,

        // instance

        STMT_DECLARATION,
        STMT_CHUNK,


    };

    using t_node_id = u64;
    using t_node_ids = std::vector<t_node_id>;

    struct t_node {
        t_node(const base::t_span& span, t_ast_node_type type)
            : span(span), type(type) {}

        base::t_span span;
        t_ast_node_type type;
    };

    // -- EXPRESSIONS

    struct t_expr_identifier : t_node {
        t_expr_identifier(const base::t_span& span)
            : t_node(span, t_ast_node_type::EXPR_IDENTIFIER) {}
    };

    struct t_expr_unary : t_node {
        t_expr_unary(const base::t_span& span, t_node_id operand, token::t_token_type opr)
            : t_node(span, t_ast_node_type::EXPR_UNARY), operand(operand), opr(opr) {}

        t_node_id operand; // t_expr
        token::t_token_type opr;
    };

    struct t_expr_binary : t_node {
        t_expr_binary(const base::t_span& span, t_node_id operand0, t_node_id operand1, token::t_token_type opr)
            : t_node(span, t_ast_node_type::EXPR_UNARY), operand0(operand0), operand1(operand1), opr(opr) {}

        t_node_id operand0; // t_expr
        t_node_id operand1; // t_expr
        token::t_token_type opr;
    };

    struct t_expr_ternary : t_node {
        t_expr_ternary(const base::t_span& span, t_node_id condition, t_node_id consequent, t_node_id alternate, token::t_token_type opr)
            : t_node(span, t_ast_node_type::EXPR_UNARY), condition(condition), consequent(consequent), alternate(alternate), opr(opr) {}

        t_node_id condition; // t_expr
        t_node_id consequent; // t_expr
        t_node_id alternate; // t_expr
        token::t_token_type opr;
    };

    struct t_type : t_node {
        t_node_id source; // t_type | t_expr_identifier | t_expr_binary (scope resolution)
        t_node_ids arguments;

        token::t_token_type qualifier;
    };

    // -- ITEMS

    struct t_item_declaration : t_node {
        t_item_declaration(const base::t_span& span, t_node_id&& name, t_node_id&& type, t_node_id&& value)
            : t_node(span, t_ast_node_type::ITEM_DECLARATION), name(name), type(type), value(value) {}

        t_node_id name, type, value; // t_expr_identifier, t_type, t_expr
    };

    struct t_item_type_declaration : t_node {
        t_item_type_declaration(const base::t_span& span, t_node_id&& name, t_node_id&& type)
            : t_node(span, t_ast_node_type::ITEM_TYPE_DECLARATION), name(name), type(type) {}

        t_node_id name, type; // expr_identifier, t_type
    };

    // -- STATEMENTS

    struct t_stmt_if : t_node {

    };

    struct t_stmt_while : t_node {

    };

    struct t_stmt_for : t_node {

    };

    struct t_stmt_expression : t_node {

    };

    struct t_stmt_declaration : t_node {

    };

    struct t_stmt_chunk : t_node {

    };

    //
    //
    //

    using t_node_variation = std::variant<
        t_expr_identifier,
        t_expr_unary,
        t_expr_binary,
        t_expr_ternary,

        t_type,

        t_item_declaration,
        t_item_type_declaration,

        t_stmt_if,
        t_stmt_while,
        t_stmt_for,
        t_stmt_expression,
        t_stmt_declaration,
        t_stmt_chunk
    >;

    struct t_ast {

    };
}
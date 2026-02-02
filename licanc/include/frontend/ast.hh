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
        t_node(base::t_span span, t_ast_node_type type)
            : span(std::move(span)), type(type) {}

        base::t_span span;
        t_ast_node_type type;
    };

    // -- EXPRESSIONS

    struct t_expr_identifier : t_node {
        t_expr_identifier(base::t_span span)
            : t_node(std::move(span), t_ast_node_type::EXPR_IDENTIFIER) {}
    };

    struct t_expr_unary : t_node {
        t_expr_unary(base::t_span span, t_node_id operand, token::t_token_type opr)
            : t_node(std::move(span), t_ast_node_type::EXPR_UNARY), operand(operand), opr(opr) {}

        t_node_id operand; // t_expr
        token::t_token_type opr;
    };

    struct t_expr_binary : t_node {
        t_expr_binary(base::t_span span, t_node_id operand0, t_node_id operand1, token::t_token_type opr)
            : t_node(std::move(span), t_ast_node_type::EXPR_BINARY), operand0(operand0), operand1(operand1), opr(opr) {}

        t_node_id operand0; // t_expr
        t_node_id operand1; // t_expr
        token::t_token_type opr;
    };

    struct t_expr_ternary : t_node {
        t_expr_ternary(base::t_span span, t_node_id condition, t_node_id consequent, t_node_id alternate, token::t_token_type opr)
            : t_node(std::move(span), t_ast_node_type::EXPR_TERNARY), condition(condition), consequent(consequent), alternate(alternate), opr(opr) {}

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
        t_item_declaration(base::t_span span, t_node_id name, t_node_id type, t_node_id value)
            : t_node(std::move(span), t_ast_node_type::ITEM_DECLARATION), name(name), type(type), value(value) {}

        t_node_id name, type, value; // t_expr_identifier, t_type, t_expr
    };

    struct t_item_type_declaration : t_node {
        t_item_type_declaration(base::t_span span, t_node_id name, t_node_id type)
            : t_node(std::move(span), t_ast_node_type::ITEM_TYPE_DECLARATION), name(name), type(type) {}

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

    // note: this is initialized before parsing or even lexing occurs. DESIGN IT TO WORK THAT WAY, FUTURE ME!!
    struct t_ast {
        std::vector<t_node_variation> raw;

        inline t_ast_node_type get_node_id_type(t_node_id node_id) {
            return get_node_base_ptr(node_id)->type;
        }

        inline t_node* get_node_base_ptr(t_node_id node_id) {
            return std::visit([](auto& n) { return (t_node*)(&n); }, raw[node_id]);
        }
    };
}
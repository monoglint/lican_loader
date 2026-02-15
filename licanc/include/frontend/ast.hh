#pragma once

#include <deque>
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

        ITEM_IMPORT,
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
    using t_node_ids = std::deque<t_node_id>;

    struct t_node {
        t_node(base::t_span span)
            : span(std::move(span)) {}

        base::t_span span;
    };

    // -- EXPRESSIONS

    struct t_expr_identifier {
        t_expr_identifier(base::t_span span)
            : _node(std::move(span)) {}

        t_node _node;
    };

    struct t_expr_unary {
        t_expr_unary(base::t_span span, t_node_id operand, token::t_token_type opr)
            : _node(std::move(span)), operand(operand), opr(opr) {}

        t_node _node;

        t_node_id operand; // t_expr
        token::t_token_type opr;
    };

    struct t_expr_binary {
        t_expr_binary(base::t_span span, t_node_id operand0, t_node_id operand1, token::t_token_type opr)
            : _node(std::move(span)), operand0(operand0), operand1(operand1), opr(opr) {}

        t_node _node;

        t_node_id operand0; // t_expr
        t_node_id operand1; // t_expr
        token::t_token_type opr;
    };

    struct t_expr_ternary {
        t_expr_ternary(base::t_span span, t_node_id condition, t_node_id consequent, t_node_id alternate, token::t_token_type opr)
            : _node(std::move(span)), condition(condition), consequent(consequent), alternate(alternate), opr(opr) {}

        t_node _node;

        t_node_id condition; // t_expr
        t_node_id consequent; // t_expr
        t_node_id alternate; // t_expr
        token::t_token_type opr;
    };

    struct t_type {
        t_node _node;

        t_node_id source; // t_type | t_expr_identifier | t_expr_binary (scope resolution)
        t_node_ids arguments;

        token::t_token_type qualifier;
    };

    // -- ITEMS

    struct t_item_import {
        t_item_import(base::t_span span, t_node_id file_path)
            : _node(std::move(span)), file_path(file_path) {}

        t_node _node;

        t_node_id file_path; // string
    };

    struct t_item_declaration {
        t_item_declaration(base::t_span span, t_node_id name, t_node_id type, t_node_id value)
            : _node(std::move(span)), name(name), type(type), value(value) {}

        t_node _node;

        t_node_id name, type, value; // t_expr_identifier, t_type, t_expr
    };

    struct t_item_type_declaration {
        t_item_type_declaration(base::t_span span, t_node_id name, t_node_id type)
            : _node(std::move(span)), name(name), type(type) {}

        t_node _node;

        t_node_id name, type; // expr_identifier, t_type
    };

    // -- STATEMENTS

    struct t_stmt_if {

        t_node _node;
    };

    struct t_stmt_while {

        t_node _node;
    };

    struct t_stmt_for {

        t_node _node;
    };

    struct t_stmt_expression {

        t_node _node;
    };

    struct t_stmt_declaration {

        t_node _node;
    };

    struct t_stmt_chunk {

        t_node _node;
    };

    //
    //
    //

    template <typename T>
    concept c_has_t_node = requires {
        { std::declval<T>()._node } -> std::convertible_to<t_node>;
    };

    template <c_has_t_node... TS>
    using constrained_variant = std::variant<TS...>;

    using t_node_variation = constrained_variant<
        t_expr_identifier,
        t_expr_unary,
        t_expr_binary,
        t_expr_ternary,

        t_type,

        t_item_import,
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
        std::deque<t_node_variation> raw;

        inline t_node& get_base(t_node_id node_id) {
            return std::visit([](auto& n) -> t_node& { return n._node; }, raw[node_id]);
        }

        template <c_has_t_node T>
        inline T& get(t_node_id node_id) {
            return std::get<T>(raw[node_id]);
        }

        template <c_has_t_node T, typename... ARGS>
        inline t_node_id emplace(ARGS&&... args) {
            raw.emplace_back(std::forward<ARGS>(args)...);
            return raw.size() - 1;
        }

        template <c_has_t_node T>
        inline t_node_id push(T node) {
            raw.push_back(std::move(node));
            return raw.size() - 1;
        }
    };
}
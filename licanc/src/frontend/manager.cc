#include "frontend/manager.hh"

#include <fstream>
#include <iostream>
#include <iterator>

#include "frontend/lexer.hh"
#include "frontend/parser.hh"
#include "frontend/semantic_analyzer.hh"

std::string read_file(std::string file_path) {
    std::ifstream input_file(file_path);

    if (!input_file) {
        std::cerr << "Could not open \"" << file_path << "\".";
        return "";
    }

    return std::string(std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>());    
}

void process_file(frontend::manager::t_compilation_file& file) {
    using namespace frontend;

    //
    lexer::t_lexer_state lexer_state(file.source_code);
    lexer::lex(lexer_state);
    //

    //
    parser::t_parser_state parser_state(file.source_code, lexer_state.tokens);
    parser::parse(parser_state);
    //

    // track the inclusion of any files from the ast
    // proceed to run them here
    for (ast::t_node_id node_id : parser_state.import_node_ids) {
        // check if there is an include item anywhere in the ast.
        // parser_state.ast.get<ast::t_item_import>(node_id).file_path;

        // if one is detected, immediately completely parse and analyze until there is a complete compilation file before continuing on.
    }

    //
    semantic_analyzer::t_analyzer_state analyzer_state(parser_state.ast);
    semantic_analyzer::analyze(analyzer_state);
    //
}

// -> t_compilation_unit

frontend::manager::t_file_id frontend::manager::t_compilation_unit::add_file(std::string path) {
    files.emplace_back(path, read_file(path));
    return files.size() - 1;
}

frontend::manager::t_compilation_file& frontend::manager::t_compilation_unit::get_file(size_t file_id) {
    return files.at(file_id);
}

// -> namespace bound

frontend::manager::t_compilation_unit frontend::manager::compile_that_shit(const t_frontend_config& config) {
    t_compilation_unit compilation_unit;

    compilation_unit.project_path = config.project_path;
    
    t_file_id start_file_id = compilation_unit.add_file(config.project_path + '/' + config.start_subpath);

    process_file(compilation_unit.get_file(start_file_id));

    return compilation_unit;
}
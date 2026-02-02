/*

primary interface header

*/

#pragma once

#include <string>

namespace licanc {
    struct t_lican_config {
        // directory for the entire lican project
        const std::string& project_path;
    };

    void compile(const t_lican_config& config);
}
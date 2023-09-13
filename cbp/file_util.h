/*
 File Name: file_util.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-08
 Last Modified: 2023-09-08
*/
#pragma once
#include <string>
namespace croot {
namespace lltg {
std::string trim_path(const std::string &path);


std::string cut_prefix_path(const std::string& prefix,
                            const std::string& path);


std::string get_file_by_path(const std::string& path);
std::string get_dir_by_path(const std::string& path);



}  // namespace lltg
}  // namespace croot


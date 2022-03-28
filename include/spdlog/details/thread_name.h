#pragma once

#include <string>

namespace spdlog {
namespace details {
namespace os {

const std::string& thread_name();
void set_os_thread_name(const std::string& name);
void set_thread_name(const std::string& name);

} // namespace os
} // namespace details
} // namespace spdlog

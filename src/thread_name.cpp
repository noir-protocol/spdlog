#ifndef SPDLOG_COMPILED_LIB
#    error Please define SPDLOG_COMPILED_LIB to compile this file.
#endif

#include <spdlog/details/thread_name.h>

#include <pthread.h>
#include <string>

static thread_local std::string thread_name;

const std::string& spdlog::details::os::thread_name() {
  if (::thread_name.empty()) {
    char name[64];
    if (pthread_getname_np(pthread_self(), name, 64) == 0) {
      ::thread_name = name;
    }
    static int thread_count = 0;
    ::thread_name = "thread-" + std::to_string(thread_count++);
  }
  return ::thread_name;
}

void spdlog::details::os::set_os_thread_name(const std::string& name) {
#if defined(__linux__)
  pthread_setname_np(pthread_self(), name.c_str());
#elif defined(__APPLE__)
  pthread_setname_np(name.c_str());
#endif
}

void spdlog::details::os::set_thread_name(const std::string& name) {
  ::thread_name = name;
}

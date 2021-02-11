#ifndef INCLUDE_TEST_TEST_HELPERS_H
#define INCLUDE_TEST_TEST_HELPERS_H

#include <iostream>
#include <chrono>

// ===============================================================================================

class ScopedTimer {
 public:
  ScopedTimer(const std::string& name = "")
    : name_(name),
      start_(std::chrono::high_resolution_clock::now()) {
  }

  ~ScopedTimer() {
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start_).count();
    std::cout << "Scope [" << name_ << "] duration: " << duration << " ms." << std::endl;
  }

  std::string name_;
  std::chrono::high_resolution_clock::time_point start_;
};

// ===============================================================================================

#endif  // INCLUDE_TEST_TEST_HELPERS_H

#include <vector>
#include "test/test_helpers.h"
#include "cpptbb/shared_ptr.h"

#include "tbb/tbb.h"

struct SimpleStruct {
  SimpleStruct(int a, int b) : a_(a), b_(b) {
  }

  int a_;
  int b_;
};

int main() {
  const size_t kNumberOfIterations = 15000000;

  tbb::task_group tasks;

  tasks.run([&]() {
    std::vector<std::shared_ptr<SimpleStruct>> shared_simple_structures_std;
    shared_simple_structures_std.reserve(kNumberOfIterations);
    {
      ScopedTimer t("std::make_shared<SimpleStruct>");
      for (size_t i = 0; i < kNumberOfIterations; i++) {
        shared_simple_structures_std[i] = std::make_shared<SimpleStruct>(i, i+1);
      }
      for (auto&& element : shared_simple_structures_std) {
        element.reset();
      }
    }
  });

  tasks.run([&]() {
    std::vector<std::shared_ptr<SimpleStruct>> shared_simple_structures_custom;
    shared_simple_structures_custom.reserve(kNumberOfIterations);
    {
      ScopedTimer t("cpptbb::make_shared<SimpleStruct>");
      for (size_t i = 0; i < kNumberOfIterations; i++) {
        shared_simple_structures_custom[i] = cpptbb::make_shared<SimpleStruct>(i, i+1);
      }
      for (auto&& element : shared_simple_structures_custom) {
        element.reset();
      }
    }
  });

  tasks.run([&]() {
    std::vector<std::shared_ptr<uint8_t>> shared_uints_std;
    shared_uints_std.reserve(kNumberOfIterations);
    {
      ScopedTimer t("malloc/free");
      for (size_t i = 0; i < kNumberOfIterations; i++) {
        shared_uints_std[i] = std::shared_ptr<uint8_t>(reinterpret_cast<uint8_t*>(malloc(512)), free);
      }
      for (auto&& element : shared_uints_std) {
        element.reset();
      }
    }
  });

  tasks.run([&]() {
    std::vector<std::shared_ptr<uint8_t>> shared_uints_custom;
    shared_uints_custom.reserve(kNumberOfIterations);
    {
      ScopedTimer t("cpptbb::make_shared_raw<uint8_t>");
      for (size_t i = 0; i < kNumberOfIterations; i++) {
        shared_uints_custom[i] = cpptbb::make_shared_raw<uint8_t>(512);
      }
      for (auto&& element : shared_uints_custom) {
        element.reset();
      }
    }
  });

  tasks.wait();

  return 0;
}

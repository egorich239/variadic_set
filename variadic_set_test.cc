#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <variadic_set.h>

namespace {

TEST(VariadicSet, Main) {
  static constexpr auto s = variadic_set<int, 1, 2, 3>();
  static_assert(s.contains(1));
  static_assert(s.contains(2));
  static_assert(s.contains(3));
  static_assert(!s.contains(0));
  static_assert(s.size() == 3);
}

}  // namespace

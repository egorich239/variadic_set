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

  static constexpr auto s2 = variadic_set<int, 3, 2, 1>();
  static_assert(std::is_same_v<decltype(s), decltype(s2)>);
}

}  // namespace

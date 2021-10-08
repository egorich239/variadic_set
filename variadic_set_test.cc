#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <variadic_set.h>

namespace {
TEST(Sorting, SmallList) {
  static constexpr auto s1 = internal_variadic_set::sorted_<int, 1, 2, 3>();
  static_assert(s1.list[0] == 1);
  static_assert(s1.list[1] == 2);
  static_assert(s1.list[2] == 3);
  static_assert(s1.data_index[0] == 0);
  static_assert(s1.data_index[1] == 1);
  static_assert(s1.data_index[2] == 2);

  static constexpr auto s2 = internal_variadic_set::sorted_<int, 3, 2, 1>();
  static_assert(s2.list[0] == 1);
  static_assert(s2.list[1] == 2);
  static_assert(s2.list[2] == 3);
  static_assert(s2.data_index[0] == 2);
  static_assert(s2.data_index[1] == 1);
  static_assert(s2.data_index[2] == 0);
}

template <typename C, C... vs>
constexpr auto sort_list(std::integer_sequence<C, vs...>) noexcept {
  return internal_variadic_set::sorted_<C, vs...>();
}

template <typename C, C... vs>
constexpr auto inverted_list(std::integer_sequence<C, vs...>) noexcept {
  return std::integer_sequence<C, (sizeof...(vs) - 1 - vs)...>{};
}

template <typename C, C... v2s, size_t... is>
constexpr bool lists_eq(std::array<C, sizeof...(is)> a1,
                        std::integer_sequence<C, v2s...>,
                        std::index_sequence<is...>) noexcept {
  constexpr std::array<C, sizeof...(v2s)> a2{v2s...};
  return ((a1[is] == a2[is]) && ...);
}

TEST(Sorting, LargeList) {
  static constexpr auto s1 = sort_list(std::make_integer_sequence<int, 250>{});
  static_assert(lists_eq(s1.list, std::make_integer_sequence<int, 250>{},
                         std::make_index_sequence<250>{}));
  static_assert(lists_eq(s1.data_index, std::make_index_sequence<250>{},
                         std::make_index_sequence<250>{}));

  static constexpr auto s2 =
      sort_list(inverted_list(std::make_integer_sequence<int, 250>{}));
  static_assert(lists_eq(s2.list, std::make_integer_sequence<int, 250>{},
                         std::make_index_sequence<250>{}));
  static_assert(lists_eq(s2.data_index,
                         inverted_list(std::make_index_sequence<250>{}),
                         std::make_index_sequence<250>{}));
}

TEST(VariadicSet, SmallSet) {
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

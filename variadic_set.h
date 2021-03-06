#pragma once

#include <array>
#include <cstddef>
#include <exception>
#include <type_traits>
#include <utility>

namespace internal_variadic_set {
template <typename C, C... vs>
constexpr C get_at_(size_t idx) noexcept {
  return std::data({vs...})[idx];
}

#include "variadic_set-index_of_impl-inl.h"

template <typename C, C... vs, size_t l, size_t w>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...> a,
                              std::index_sequence<l, w>, size_t& res) noexcept {
  if constexpr (w <= 2 * index_of_impl_max_base_case_) {
    constexpr size_t m = l + w / 2;
    constexpr std::integral_constant<C, get_at_<C, vs...>(m)> p{};

    return ((v < decltype(p)::value) &&
            index_of_impl_(v, a, std::index_sequence<l, m - l>{}, res)) ||
           index_of_impl_(v, a, std::index_sequence<m, l + w - m>{}, res);
  } else {
    constexpr size_t m1 = l + w / 4;
    constexpr size_t m2 = l + w / 2;
    constexpr size_t m3 = l + w / 2 + w / 4;

    const int marker = (int)(v < m1) + (int)(v < m2) + (int)(v < m3);
    switch (marker) {
      case 0:
        return index_of_impl_(v, a, std::index_sequence<m3, l + w - m3>{}, res);
      case 1:
        return index_of_impl_(v, a, std::index_sequence<m2, m3 - m2>{}, res);
      case 2:
        return index_of_impl_(v, a, std::index_sequence<m1, m2 - m1>{}, res);
      case 3:
        return index_of_impl_(v, a, std::index_sequence<l, m1 - l>{}, res);
    }

    // unreachable
    return false;
  }
}

template <typename C, C... vs>
constexpr bool index_of_(C v, size_t& res) noexcept {
  return index_of_impl_(v, std::integer_sequence<C, vs...>{},
                        std::index_sequence<0, sizeof...(vs)>{}, res);
}

template <typename C, size_t N, typename Idx>
struct Sorted_;

template <typename C, size_t N, size_t... idx>
struct Sorted_<C, N, std::index_sequence<idx...>> {
  constexpr Sorted_(std::array<C, N> in) noexcept
      : list{in[idx]...}, data_index{} {
    for (size_t p = 1; p < N; ++p) {
      C v = list[p];
      size_t q = 0;
      while (q < p && list[q] < v) ++q;
      for (size_t r = p; r > q; --r) {
        list[r] = list[r - 1];
        data_index[r] = data_index[r - 1];
      }
      list[q] = v;
      data_index[q] = p;
    }
  }

  std::array<C, N> list;
  std::array<size_t, N> data_index;
};

template <typename C, C... vs>
constexpr auto sorted_() noexcept {
  return Sorted_<C, sizeof...(vs), std::make_index_sequence<sizeof...(vs)>>(
      {vs...});
}

template <typename C, C c1, C c2>
constexpr bool is_ordered_list_without_duplications_atom_() noexcept {
  // Triggers compilation error when c1 == c2 with good diagnostics.
  switch (c1) {
    case c1:
    case c2:;
  }
  return c1 < c2;
}

template <typename C>
constexpr bool is_ordered_list_without_duplications_(
    std::integer_sequence<C>, std::index_sequence<>) noexcept {
  return true;
}

template <typename C, C c>
constexpr bool is_ordered_list_without_duplications_(
    std::integer_sequence<C, c>, std::index_sequence<0>) noexcept {
  return true;
}

template <typename C, C... vs, size_t... is>
constexpr bool is_ordered_list_without_duplications_(
    std::integer_sequence<C, vs...>, std::index_sequence<0, is...>) noexcept {
  constexpr std::array<C, sizeof...(vs)> values{vs...};
  return (is_ordered_list_without_duplications_atom_<C, values[is - 1],
                                                     values[is]>() &&
          ...);
}

template <typename C, C... vs>
struct Set_ {
  static_assert(is_ordered_list_without_duplications_(
      std::integer_sequence<C, vs...>{},
      std::make_index_sequence<sizeof...(vs)>{}));

  static constexpr size_t size() noexcept { return sizeof...(vs); }
  static constexpr bool contains(C v) noexcept {
    size_t ign = 0;
    return index_of_<C, vs...>(v, ign);
  }
};

template <typename C, C... vs, size_t... is>
constexpr auto variadic_set_impl(std::integer_sequence<C, vs...>,
                                 std::index_sequence<is...>) {
  constexpr auto vs_sorted = sorted_<C, vs...>();
  return Set_<C, vs_sorted.list[is]...>{};
}

template <typename K, typename V, typename Ks, typename Vs>
struct Map_;

template <typename K, typename V, typename Vs, K... ks>
struct Map_<K, V, std::integer_sequence<K, ks...>, Vs> {
  using keys_type = Set_<K, ks...>;

  static constexpr size_t size() noexcept { return keys_type::size(); }
  static constexpr bool contains(K v) noexcept {
    return keys_type::contains(v);
  }

  template <size_t... dis>
  constexpr Map_(Vs& vs, std::index_sequence<dis...>) noexcept
      : values_{vs}, data_indices_{dis...} {}

  constexpr auto operator()(K k) const noexcept {
    size_t offs = 0;
    return index_of_<K, ks...>(k, offs)
               ? std::data(values_) + data_indices_[offs]
               : nullptr;
  }

  constexpr auto operator()(K k, V def) const noexcept {
    size_t offs = 0;
    return index_of_<K, ks...>(k, offs) ? values_[data_indices_[offs]] : def;
  }

 private:
  Vs& values_;
  std::array<size_t, sizeof...(ks)> data_indices_;
};

template <typename K, typename V, typename Vs, K... ks, size_t... is>
constexpr auto variadic_map_impl(Vs& values, std::integer_sequence<K, ks...>,
                                 std::index_sequence<is...>) {
  constexpr auto k_sorted = sorted_<K, ks...>();
  return Map_<K, V, std::integer_sequence<K, k_sorted.list[is]...>, Vs>{
      values, std::index_sequence<k_sorted.data_index[is]...>{}};
}

template <typename L, typename V, L label>
struct Case_ {
  static constexpr L label_() noexcept { return label; }
  V value;
};
}  // namespace internal_variadic_set

template <typename C, C... vs>
constexpr auto variadic_set() {
  return internal_variadic_set::variadic_set_impl<C>(
      std::integer_sequence<C, vs...>{},
      std::make_index_sequence<sizeof...(vs)>{});
}

template <typename K, K... ks, typename Vs>
constexpr auto variadic_map(Vs& values) noexcept {
  return internal_variadic_set::variadic_map_impl<
      K, std::remove_reference_t<decltype(*std::data(values))>>(
      values, std::integer_sequence<K, ks...>{},
      std::make_index_sequence<sizeof...(ks)>{});
}

template <typename L, L label, typename V>
constexpr auto variadic_case(V v) noexcept {
  return internal_variadic_set::Case_<L, V, label>{v};
}

template <typename L, typename... Ls>
class variadic_switch;

template <typename L, typename... Vs, L... labels>
class variadic_switch<L, internal_variadic_set::Case_<L, Vs, labels>...> {
  using common_type_ = std::common_type_t<Vs...>;
  using array_type_ = std::array<common_type_, sizeof...(labels)>;
  using map_type_ =
      decltype(variadic_map<L, labels...>(std::declval<array_type_&>()));

 public:
  static constexpr size_t size() noexcept { return sizeof...(labels); }

  constexpr variadic_switch(internal_variadic_set::Case_<L, Vs, labels>... ls)
      : values_{ls.value...}, map_{variadic_map<L, labels...>(values_)} {}

  template <typename V>
  constexpr common_type_ operator()(L label, V def) const noexcept {
    return map_(label, def);
  }

 private:
  array_type_ values_;
  map_type_ map_;
};

template <typename L, typename... Vs, L... labels>
variadic_switch(internal_variadic_set::Case_<L, Vs, labels>...)
    -> variadic_switch<L, internal_variadic_set::Case_<L, Vs, labels>...>;

#if 0
void verify_sorting_algo() {
  static constexpr auto ss =
      internal_variadic_set::sorted_<int, 5, 4, 3, 2, 1>();
  static_assert(ss.list[0] == 1);
  static_assert(ss.list[1] == 2);
  static_assert(ss.list[2] == 3);
  static_assert(ss.list[3] == 4);
  static_assert(ss.list[4] == 5);

  static_assert(ss.data_index[0] == 4);
  static_assert(ss.data_index[1] == 3);
  static_assert(ss.data_index[2] == 2);
  static_assert(ss.data_index[3] == 1);
  static_assert(ss.data_index[4] == 0);
}

void verify_set() {
  variadic_set<int, 1, 2>();
  variadic_set<int, 1, 1>();
}

char foo(int x) {
  static constexpr std::array<const char, 5> vs{'a', 'b', 'r', 'q', 'w'};
  static constexpr auto m = variadic_map<int, 5, 4, 3, 2, 1>(vs);

  static_assert(m(1, '!') == 'w');
  static_assert(m(5, '!') == 'a');
  static_assert(m(-5, '!') == '!');
  return m(x, '!');
}

char foo2(int x) {
  static constexpr const char str[] = "abc";
  static constexpr auto mOfArray = variadic_map<int, 1, 2, 3, 4>(str);
  static_assert(mOfArray(1, '!') == 'a');
  return mOfArray(x, '!');
}

char bar(int x) {
  static constexpr auto sw = variadic_switch{
      variadic_case<int, 1>('a'),
      variadic_case<int, 2>('b'),
      variadic_case<int, 3>('c'),
  };

  static_assert(sw(1, '!') == 'a');
  return sw(x, '!');
}
#endif
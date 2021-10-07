#pragma once

#include <array>
#include <cstddef>
#include <exception>
#include <type_traits>
#include <utility>

namespace internal_variadic_set {
template <typename C>
class duplicate_element : public std::exception {
 public:
  duplicate_element(C v) : value(v) {}
  C value;
};

template <size_t idx, typename C, C... vs>
constexpr C get_at_() noexcept {
  return std::data({vs...})[idx];
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...> a,
                              std::index_sequence<l, 0>, size_t& res) noexcept {
  return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...> a,
                              std::index_sequence<l, 1>, size_t& res) noexcept {
  switch (v) {
    case get_at_<l, C, vs...>():
      return (res = l), true;
  }
  return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...> a,
                              std::index_sequence<l, 2>, size_t& res) noexcept {
  switch (v) {
    case get_at_<l, C, vs...>():
      return (res = l), true;
    case get_at_<l + 1, C, vs...>():
      return (res = l + 1), true;
  }
  return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...> a,
                              std::index_sequence<l, 3>, size_t& res) noexcept {
  switch (v) {
    case get_at_<l, C, vs...>():
      return (res = l), true;
    case get_at_<l + 1, C, vs...>():
      return (res = l + 1), true;
    case get_at_<l + 2, C, vs...>():
      return (res = l + 2), true;
  }
  return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...> a,
                              std::index_sequence<l, 4>, size_t& res) noexcept {
  switch (v) {
    case get_at_<l, C, vs...>():
      return (res = l), true;
    case get_at_<l + 1, C, vs...>():
      return (res = l + 1), true;
    case get_at_<l + 2, C, vs...>():
      return (res = l + 2), true;
    case get_at_<l + 3, C, vs...>():
      return (res = l + 3), true;
  }
  return false;
}

template <typename C, C... vs, size_t l, size_t w>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...> a,
                              std::index_sequence<l, w>, size_t& res) noexcept {
  constexpr size_t m = l + w / 2;
  return index_of_impl_(v, a, std::index_sequence<l, m - l>{}, res) ||
         index_of_impl_(v, a, std::index_sequence<m, l + w - m>{}, res);
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
  constexpr Sorted_(std::array<C, N> in)
      : list{in[idx]...}, original_poisition{} {
    for (size_t p = 1; p < N; ++p) {
      C v = list[p];
      size_t q = 0;
      while (q < p && list[q] < v) ++q;
      if (q == p) continue;
      if (list[q] == v) throw duplicate_element<C>{v};
      for (size_t r = p; r > q; --r) {
        list[r] = list[r - 1];
        original_poisition[r] = original_poisition[r - 1];
      }
      list[q] = v;
      original_poisition[q] = p;
    }
  }

  std::array<C, N> list;
  std::array<size_t, N> original_poisition;
};

template <typename C, C... vs>
constexpr auto sorted_() {
  return Sorted_<C, sizeof...(vs), std::make_index_sequence<sizeof...(vs)>>(
      {vs...});
}

template <typename C, C... vs>
struct Set_ {
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

template <typename K, typename V, K... ks>
struct Map_ {
  using keys_type = Set_<K, ks...>;

  static constexpr size_t size() noexcept { return keys_type::size(); }
  static constexpr bool contains(K v) noexcept {
    return keys_type::contains(v);
  }

  constexpr auto operator()(K k) const noexcept {
    size_t offs = 0;
    return index_of_<K, ks...>(k, offs) ? &values[offs] : nullptr;
  }

  constexpr auto operator()(K k, V def) const noexcept {
    size_t offs = 0;
    return index_of_<K, ks...>(k, offs) ? values[offs] : def;
  }

  std::array<V, sizeof...(ks)> values;
};

template <typename K, typename V, K... ks, size_t... is>
constexpr auto variadic_map_impl(const std::array<V, sizeof...(ks)>& values,
                                 std::integer_sequence<K, ks...>,
                                 std::index_sequence<is...>) {
  constexpr auto k_sorted = sorted_<K, ks...>();
  std::array<V, sizeof...(ks)> values_sorted{
      values[k_sorted.original_poisition[is]]...};
  return Map_<K, V, k_sorted.list[is]...>{values_sorted};
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

template <typename K, K... ks, typename V>
constexpr auto variadic_map(
    const std::array<V, sizeof...(ks)>& values) noexcept {
  return internal_variadic_set::variadic_map_impl<K, V>(
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
  using map_type_ = decltype(variadic_map<L, labels...>(
      std::declval<std::array<common_type_, sizeof...(labels)>>()));

 public:
  static constexpr size_t size() noexcept { return sizeof...(labels); }

  constexpr variadic_switch(internal_variadic_set::Case_<L, Vs, labels>... ls)
      : map_(variadic_map<L, labels...>(
            std::array<common_type_, sizeof...(labels)>{ls.value...})) {}

  template <typename V>
  constexpr common_type_ operator()(L label, V def) const noexcept {
    return map_(label, def);
  }

 private:
  map_type_ map_;
};

template <typename L, typename... Vs, L... labels>
variadic_switch(internal_variadic_set::Case_<L, Vs, labels>...)
    -> variadic_switch<L, internal_variadic_set::Case_<L, Vs, labels>...>;

char foo(int x) {
  static constexpr std::array<const char, 5> vs{'a', 'b', 'r', 'q', 'w'};
  static constexpr auto m = variadic_map<int, 5, 4, 3, 2, 1>(vs);

  static constexpr auto ss =
      internal_variadic_set::sorted_<int, 5, 4, 3, 2, 1>();
  static_assert(ss.list[0] == 1);
  static_assert(ss.list[1] == 2);
  static_assert(ss.list[2] == 3);
  static_assert(ss.list[3] == 4);
  static_assert(ss.list[4] == 5);

  static_assert(ss.original_poisition[0] == 4);
  static_assert(ss.original_poisition[1] == 3);
  static_assert(ss.original_poisition[2] == 2);
  static_assert(ss.original_poisition[3] == 1);
  static_assert(ss.original_poisition[4] == 0);

  static_assert(m(1, '!') == 'w');
  static_assert(m(5, '!') == 'a');
  static_assert(m(-5, '!') == '!');
  return m(x, '!');
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

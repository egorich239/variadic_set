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
  constexpr std::array<C, sizeof...(vs)> vs_ordered = [] {
    std::array<C, sizeof...(vs)> res{vs...};
    for (size_t p = 1; p < res.size(); ++p) {
      C v = res[p];
      size_t q = 0;
      while (q < p && res[q] < v) ++q;
      if (q == p) continue;
      if (res[q] == v) throw duplicate_element<C>{v};
      for (size_t r = p; r > q; --r) {
        res[r] = res[r - 1];
      }
      res[q] = v;
    }
    return res;
  }();
  return Set_<C, vs_ordered[is]...>{};
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

  V (&values)[sizeof...(ks)];
};
}  // namespace internal_variadic_set

template <typename I, I... is>
constexpr auto variadic_set() {
  return internal_variadic_set::variadic_set_impl<I>(
      std::integer_sequence<I, is...>{},
      std::make_index_sequence<sizeof...(is)>{});
}

template <typename K, typename V, K... ks>
constexpr auto variadic_map(internal_variadic_set::Set_<K, ks...>,
                            V (&values)[sizeof...(ks)]) noexcept {
  // order mismatch!
  return internal_variadic_set::Map_<K, V, ks...>{values};
}

template <typename K, typename... Ls>
class variadic_switch {
  // TODO
};

char foo(int x) {
  static constexpr const char vs[] = "abra";
  static constexpr auto m =
      variadic_map(variadic_set<int, 1, 2, 3, 4, 5>(), vs);
  return m(x, '!');
}
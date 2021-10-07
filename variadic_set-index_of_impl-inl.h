// clang-format off
template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 0>, size_t& res) noexcept {
    switch (v) {
        
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 1>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 2>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 3>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 4>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 5>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
        case get_at_<C, vs...>(l + 4): return (res = l + 4), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 6>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
        case get_at_<C, vs...>(l + 4): return (res = l + 4), true;
        case get_at_<C, vs...>(l + 5): return (res = l + 5), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 7>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
        case get_at_<C, vs...>(l + 4): return (res = l + 4), true;
        case get_at_<C, vs...>(l + 5): return (res = l + 5), true;
        case get_at_<C, vs...>(l + 6): return (res = l + 6), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 8>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
        case get_at_<C, vs...>(l + 4): return (res = l + 4), true;
        case get_at_<C, vs...>(l + 5): return (res = l + 5), true;
        case get_at_<C, vs...>(l + 6): return (res = l + 6), true;
        case get_at_<C, vs...>(l + 7): return (res = l + 7), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 9>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
        case get_at_<C, vs...>(l + 4): return (res = l + 4), true;
        case get_at_<C, vs...>(l + 5): return (res = l + 5), true;
        case get_at_<C, vs...>(l + 6): return (res = l + 6), true;
        case get_at_<C, vs...>(l + 7): return (res = l + 7), true;
        case get_at_<C, vs...>(l + 8): return (res = l + 8), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 10>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
        case get_at_<C, vs...>(l + 4): return (res = l + 4), true;
        case get_at_<C, vs...>(l + 5): return (res = l + 5), true;
        case get_at_<C, vs...>(l + 6): return (res = l + 6), true;
        case get_at_<C, vs...>(l + 7): return (res = l + 7), true;
        case get_at_<C, vs...>(l + 8): return (res = l + 8), true;
        case get_at_<C, vs...>(l + 9): return (res = l + 9), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 11>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
        case get_at_<C, vs...>(l + 4): return (res = l + 4), true;
        case get_at_<C, vs...>(l + 5): return (res = l + 5), true;
        case get_at_<C, vs...>(l + 6): return (res = l + 6), true;
        case get_at_<C, vs...>(l + 7): return (res = l + 7), true;
        case get_at_<C, vs...>(l + 8): return (res = l + 8), true;
        case get_at_<C, vs...>(l + 9): return (res = l + 9), true;
        case get_at_<C, vs...>(l + 10): return (res = l + 10), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 12>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
        case get_at_<C, vs...>(l + 4): return (res = l + 4), true;
        case get_at_<C, vs...>(l + 5): return (res = l + 5), true;
        case get_at_<C, vs...>(l + 6): return (res = l + 6), true;
        case get_at_<C, vs...>(l + 7): return (res = l + 7), true;
        case get_at_<C, vs...>(l + 8): return (res = l + 8), true;
        case get_at_<C, vs...>(l + 9): return (res = l + 9), true;
        case get_at_<C, vs...>(l + 10): return (res = l + 10), true;
        case get_at_<C, vs...>(l + 11): return (res = l + 11), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 13>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
        case get_at_<C, vs...>(l + 4): return (res = l + 4), true;
        case get_at_<C, vs...>(l + 5): return (res = l + 5), true;
        case get_at_<C, vs...>(l + 6): return (res = l + 6), true;
        case get_at_<C, vs...>(l + 7): return (res = l + 7), true;
        case get_at_<C, vs...>(l + 8): return (res = l + 8), true;
        case get_at_<C, vs...>(l + 9): return (res = l + 9), true;
        case get_at_<C, vs...>(l + 10): return (res = l + 10), true;
        case get_at_<C, vs...>(l + 11): return (res = l + 11), true;
        case get_at_<C, vs...>(l + 12): return (res = l + 12), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 14>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
        case get_at_<C, vs...>(l + 4): return (res = l + 4), true;
        case get_at_<C, vs...>(l + 5): return (res = l + 5), true;
        case get_at_<C, vs...>(l + 6): return (res = l + 6), true;
        case get_at_<C, vs...>(l + 7): return (res = l + 7), true;
        case get_at_<C, vs...>(l + 8): return (res = l + 8), true;
        case get_at_<C, vs...>(l + 9): return (res = l + 9), true;
        case get_at_<C, vs...>(l + 10): return (res = l + 10), true;
        case get_at_<C, vs...>(l + 11): return (res = l + 11), true;
        case get_at_<C, vs...>(l + 12): return (res = l + 12), true;
        case get_at_<C, vs...>(l + 13): return (res = l + 13), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 15>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
        case get_at_<C, vs...>(l + 4): return (res = l + 4), true;
        case get_at_<C, vs...>(l + 5): return (res = l + 5), true;
        case get_at_<C, vs...>(l + 6): return (res = l + 6), true;
        case get_at_<C, vs...>(l + 7): return (res = l + 7), true;
        case get_at_<C, vs...>(l + 8): return (res = l + 8), true;
        case get_at_<C, vs...>(l + 9): return (res = l + 9), true;
        case get_at_<C, vs...>(l + 10): return (res = l + 10), true;
        case get_at_<C, vs...>(l + 11): return (res = l + 11), true;
        case get_at_<C, vs...>(l + 12): return (res = l + 12), true;
        case get_at_<C, vs...>(l + 13): return (res = l + 13), true;
        case get_at_<C, vs...>(l + 14): return (res = l + 14), true;
    }
    return false;
}

template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, 16>, size_t& res) noexcept {
    switch (v) {
        case get_at_<C, vs...>(l + 0): return (res = l + 0), true;
        case get_at_<C, vs...>(l + 1): return (res = l + 1), true;
        case get_at_<C, vs...>(l + 2): return (res = l + 2), true;
        case get_at_<C, vs...>(l + 3): return (res = l + 3), true;
        case get_at_<C, vs...>(l + 4): return (res = l + 4), true;
        case get_at_<C, vs...>(l + 5): return (res = l + 5), true;
        case get_at_<C, vs...>(l + 6): return (res = l + 6), true;
        case get_at_<C, vs...>(l + 7): return (res = l + 7), true;
        case get_at_<C, vs...>(l + 8): return (res = l + 8), true;
        case get_at_<C, vs...>(l + 9): return (res = l + 9), true;
        case get_at_<C, vs...>(l + 10): return (res = l + 10), true;
        case get_at_<C, vs...>(l + 11): return (res = l + 11), true;
        case get_at_<C, vs...>(l + 12): return (res = l + 12), true;
        case get_at_<C, vs...>(l + 13): return (res = l + 13), true;
        case get_at_<C, vs...>(l + 14): return (res = l + 14), true;
        case get_at_<C, vs...>(l + 15): return (res = l + 15), true;
    }
    return false;
}

constexpr size_t index_of_impl_max_base_case_ = 16;
// clang-format on

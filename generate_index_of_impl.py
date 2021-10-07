#!python3

LIMIT = 16
print("// clang-format off")

for p in range(LIMIT + 1):
    print("""template <typename C, C... vs, size_t l>
constexpr bool index_of_impl_(C v, std::integer_sequence<C, vs...>,
                              std::index_sequence<l, {p}>, size_t& res) noexcept {{
    switch (v) {{
        {cases}
    }}
    return false;
}}
""".format(p=p,
           cases="\n        ".join(f"case get_at_<C, vs...>(l + {i}): return (res = l + {i}), true;" for i in range(p))))

print(f"constexpr size_t index_of_impl_max_base_case_ = {LIMIT};")
print("// clang-format on")

#ifndef N_DIMENSIONAL_VECTOR_HH
#define N_DIMENSIONAL_VECTOR_HH

////////////////////////////////////////////////////////////////
/// Nd vector
////////////////////////////////////////////////////////////////

template <typename T, size_t N>
struct VectorN
{
    typedef T value_type;

    static constexpr size_t size() noexcept { return N; }

    const T &operator[](size_t i) const { return v[i]; }
    T &operator[](size_t i) { return v[i]; }

    operator const T *() const { return &v[0]; }
    operator T *() { return &v[0]; }

    T v[N] {0};
};

#endif // N_DIMENSIONAL_VECTOR_HH

#include "vector_n.impl.hh"

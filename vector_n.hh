#ifndef N_DIMENSIONAL_VECTOR_HH
#define N_DIMENSIONAL_VECTOR_HH

#include <utility> // std::index_sequence

#if __cplusplus >= 201703L
#define ENABLED_CPP_STD_17
#endif

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

////////////////////////////////////////////////////////////////
/// Nd vector Ops Impl
////////////////////////////////////////////////////////////////

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_set(const T &s, std::index_sequence<I...>)
{ using _ = int[]; VectorN<T, N> p {}; (void)_{ (p[I] = s, 0)... }; return p; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_neg(const VectorN<T, N> &p, std::index_sequence<I...>)
{ return { (-p[I])... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_add(const VectorN<T, N> &a, const VectorN<T, N> &b, std::index_sequence<I...>)
{ return { (a[I] + b[I])... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_add(const VectorN<T, N> &p, const T &s, std::index_sequence<I...>)
{ return { (p[I] + s)... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_sub(const VectorN<T, N> &a, const VectorN<T, N> &b, std::index_sequence<I...>)
{ return { (a[I] - b[I])... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_sub(const VectorN<T, N> &p, const T &s, std::index_sequence<I...>)
{ return { (p[I] - s)... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_mul(const VectorN<T, N> &a, const VectorN<T, N> &b, std::index_sequence<I...>)
{ return { (a[I] * b[I])... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_mul(const VectorN<T, N> &p, const T &s, std::index_sequence<I...>)
{ return { (p[I] * s)... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_div(const VectorN<T, N> &a, const VectorN<T, N> &b, std::index_sequence<I...>)
{ return { (a[I] / b[I])... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_div(const VectorN<T, N> &p, const T &s, std::index_sequence<I...>)
{ return { (p[I] / s)... }; } // to optimize for large size

template <typename T, size_t N, size_t... I>
inline T op_impl_sum(const VectorN<T, N> &p, std::index_sequence<I...>)
#ifdef ENABLED_CPP_STD_17
{ return ((p[I]) + ...); }
#else
{ using _ = int[]; T r {}; (void)_{ (r += p[I], 0)... }; return r; }
#endif

template <typename T, size_t N, size_t... I>
inline T op_impl_dot(const VectorN<T, N> &a, const VectorN<T, N> &b, std::index_sequence<I...>)
#ifdef ENABLED_CPP_STD_17
{ return ((a[I] * b[I]) + ...); }
#else
{ using _ = int[]; T r {}; (void)_{ (r += a[I] * b[I], 0)... }; return r; }
#endif

template <typename T, size_t N, size_t... I>
inline T op_impl_max(const VectorN<T, N> &p, std::index_sequence<I...>)
{ using _ = int[]; T r = p[0]; (void)_{ (r = std::max(r, p[I]), 0)... }; return r; }

template <typename T, size_t N, size_t... I>
inline size_t op_impl_argmax(const VectorN<T, N> &p, std::index_sequence<I...>)
{ using _ = int[]; size_t k {}; (void)_{ (k = p[k] < p[I] ? I : k, 0)... }; return k; }

template <typename T, size_t N, size_t... I>
inline T op_impl_min(const VectorN<T, N> &p, std::index_sequence<I...>)
{ using _ = int[]; T r = p[0]; (void)_{ (r = std::min(r, p[I]), 0)... }; return r; }

template <typename T, size_t N, size_t... I>
inline size_t op_impl_argmin(const VectorN<T, N> &p, std::index_sequence<I...>)
{ using _ = int[]; size_t k {}; (void)_{ (k = p[k] > p[I] ? I : k, 0)... }; return k; }

template <typename T, size_t N, class Stream, size_t... I>
inline Stream &op_impl_out(Stream &os, const VectorN<T, N>& p, const char *sep, std::index_sequence<I...>)
#ifdef ENABLED_CPP_STD_17
{ ((os << (I == 0 ? "" : sep) << p[I]), ...); return os; }
#else
{ using _ = int[]; (void)_{ (os << (I == 0 ? "" : sep) << p[I], 0)... }; return os; }
#endif

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_fun(const VectorN<T, N> &p, T (*fun)(T), std::index_sequence<I...>)
{ return { fun(p[I])... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_fun(const VectorN<T, N> &p, const T &s, T (*fun)(T, T), std::index_sequence<I...>)
{ return { fun(p[I], s)... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_fun(const VectorN<T, N> &a, const VectorN<T, N> &b, T (*fun)(T, T), std::index_sequence<I...>)
{ return { fun(a[I], b[I])... }; }

////////////////////////////////////////////////////////////////
/// Nd vector Ops
////////////////////////////////////////////////////////////////

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> operator+(const VectorN<T, N> &a, const VectorN<T, N> &b)
{ return op_impl_add(a, b, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> operator+(const VectorN<T, N> &p, const T &s)
{ return op_impl_add(p, s, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> operator-(const VectorN<T, N> &a, const VectorN<T, N> &b)
{ return op_impl_sub(a, b, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> operator-(const VectorN<T, N> &p, const T &s)
{ return op_impl_sub(p, s, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> operator*(const VectorN<T, N> &a, const VectorN<T, N> &b)
{ return op_impl_mul(a, b, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> operator*(const VectorN<T, N> &p, const T &s)
{ return op_impl_mul(p, s, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> operator/(const VectorN<T, N> &a, const VectorN<T, N> &b)
{ return op_impl_div(a, b, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> operator/(const VectorN<T, N> &p, const T &s)
{ return op_impl_div(p, s, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> operator-(const VectorN<T, N> &p)
{ return op_impl_neg(p, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline T sum(const VectorN<T, N> &p)
{ return op_impl_sum(p, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline T dot(const VectorN<T, N> &a, const VectorN<T, N> &b)
{ return op_impl_dot(a, b, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline T max(const VectorN<T, N> &p)
{ return op_impl_max(p, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline size_t argmax(const VectorN<T, N> &p)
{ return op_impl_argmax(p, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline T min(const VectorN<T, N> &p)
{ return op_impl_min(p, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline size_t argmin(const VectorN<T, N> &p)
{ return op_impl_argmin(p, Indices{}); }

template <typename T, size_t N>
inline VectorN<T, N> &operator+=(VectorN<T, N> &a, const VectorN<T, N> &b)
{ a = a + b; return a; }

template <typename T, size_t N>
inline VectorN<T, N> &operator-=(VectorN<T, N> &a, const VectorN<T, N> &b)
{ a = a - b; return a; }

template <typename T, size_t N>
inline VectorN<T, N> &operator*=(VectorN<T, N> &p, const T &s)
{ p = p * s; return p; }

template <typename T, size_t N>
inline VectorN<T, N> &operator/=(VectorN<T, N> &p, const T &s)
{ p = p / s; return p; }

#endif // N_DIMENSIONAL_VECTOR_HH

#include "vector_n.impl.hh"

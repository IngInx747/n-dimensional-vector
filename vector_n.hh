#ifndef N_DIMENSIONAL_VECTOR_HH
#define N_DIMENSIONAL_VECTOR_HH

#include <cmath>
#include <utility> // std::index_sequence
#include <iostream>

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
inline VectorN<T, N> op_impl_neg(const VectorN<T, N> &p, std::index_sequence<I...>)
{ return { (-p[I])... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_abs(const VectorN<T, N> &p, std::index_sequence<I...>)
{ return { std::abs(p[I])... }; }

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
inline VectorN<T, N> op_impl_max(const VectorN<T, N> &a, const VectorN<T, N> &b, std::index_sequence<I...>)
{ return { std::max(a[I], b[I])... }; }

template <typename T, size_t N, size_t... I>
inline T op_impl_max(const VectorN<T, N> &p, std::index_sequence<I...>)
{ using _ = int[]; T r = p[0]; (void)_{ (r = std::max(r, p[I]), 0)... }; return r; }

template <typename T, size_t N, size_t... I>
inline size_t op_impl_argmax(const VectorN<T, N> &p, std::index_sequence<I...>)
{ using _ = int[]; size_t k {}; (void)_{ (k = p[k] < p[I] ? I : k, 0)... }; return k; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_min(const VectorN<T, N> &a, const VectorN<T, N> &b, std::index_sequence<I...>)
{ return { std::min(a[I], b[I])... }; }

template <typename T, size_t N, size_t... I>
inline T op_impl_min(const VectorN<T, N> &p, std::index_sequence<I...>)
{ using _ = int[]; T r = p[0]; (void)_{ (r = std::min(r, p[I]), 0)... }; return r; }

template <typename T, size_t N, size_t... I>
inline size_t op_impl_argmin(const VectorN<T, N> &p, std::index_sequence<I...>)
{ using _ = int[]; size_t k {}; (void)_{ (k = p[k] > p[I] ? I : k, 0)... }; return k; }

template <typename T, size_t N, size_t... I>
inline std::ostream &op_impl_out(std::ostream &os, const VectorN<T, N>& p, const char *sep, std::index_sequence<I...>)
#ifdef ENABLED_CPP_STD_17
{ ((os << (I == 0 ? "" : sep) << p[I]), ...); return os; }
#else
{ using _ = int[]; (void)_{ (os << (I == 0 ? "" : sep) << p[I], 0)... }; return os; }
#endif

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_pow(const VectorN<T, N> &p, const T &s, std::index_sequence<I...>)
{ return { std::pow(p[I], s)... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_exp(const VectorN<T, N> &p, std::index_sequence<I...>)
{ return { std::exp(p[I])... }; }

template <typename T, size_t N, size_t... I>
inline VectorN<T, N> op_impl_log(const VectorN<T, N> &p, std::index_sequence<I...>)
{ return { std::log(p[I])... }; }

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
inline VectorN<T, N> abs(const VectorN<T, N> &p)
{ return op_impl_abs(p, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline T sum(const VectorN<T, N> &p)
{ return op_impl_sum(p, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline T dot(const VectorN<T, N> &a, const VectorN<T, N> &b)
{ return op_impl_dot(a, b, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> max(const VectorN<T, N> &a, const VectorN<T, N> &b)
{ return op_impl_max(a, b, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline T max(const VectorN<T, N> &p)
{ return op_impl_max(p, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline size_t argmax(const VectorN<T, N> &p)
{ return op_impl_argmax(p, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> min(const VectorN<T, N> &a, const VectorN<T, N> &b)
{ return op_impl_min(a, b, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline T min(const VectorN<T, N> &p)
{ return op_impl_min(p, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline size_t argmin(const VectorN<T, N> &p)
{ return op_impl_argmin(p, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline std::ostream &operator<<(std::ostream &os, const VectorN<T, N>& p)
{ os << "("; op_impl_out(os, p, ", ", Indices{}) << ")"; return os; }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> pow(const VectorN<T, N> &p, const T &s)
{ return op_impl_pow(p, s, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> exp(const VectorN<T, N> &p)
{ return op_impl_exp(p, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> log(const VectorN<T, N> &p)
{ return op_impl_log(p, Indices{}); }

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

template <typename T, size_t N>
inline T norm1(const VectorN<T, N> &p)
{ return sum(abs(p)); }

template <typename T, size_t N>
inline T norm2(const VectorN<T, N> &p)
{ return std::sqrt(dot(p, p)); }

template <typename T, size_t N>
inline T norm8(const VectorN<T, N> &p)
{ return max(abs(p)); }

template <typename T, size_t N>
inline T norm(const VectorN<T, N> &p, const T &s)
{ return std::pow(sum(pow(abs(p), s)), (T)1 / s); }

template <typename T, size_t N>
inline VectorN<T, N> normalize(const VectorN<T, N> &p)
{ return p / norm2(p); }

////////////////////////////////////////////////////////////////
/// Nd vector ctors
////////////////////////////////////////////////////////////////

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> make_vector(const T &s)
{ return op_impl_set<T, N>(s, Indices{}); }

////////////////////////////////////////////////////////////////
/// 3d vector Ops
////////////////////////////////////////////////////////////////

template <typename T>
inline VectorN<T, 3> cross(const VectorN<T, 3> &a, const VectorN<T, 3> &b)
{ return { a[1]*b[2] - a[2]*b[1], a[2]*b[0] - a[0]*b[2], a[0]*b[1] - a[1]*b[0] }; }

////////////////////////////////////////////////////////////////
/// 2d vector Ops
////////////////////////////////////////////////////////////////

template <typename T>
inline T cross(const VectorN<T, 2> &a, const VectorN<T, 2> &b)
{ return a[0]*b[1] - a[1]*b[0]; }

#endif

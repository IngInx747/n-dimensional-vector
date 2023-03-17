#ifndef N_DIMENSIONAL_VECTOR_IMPL_HH
#define N_DIMENSIONAL_VECTOR_IMPL_HH

#include "vector_n.hh"

#include <cmath>
#include <iostream>

//template <typename T, size_t N, size_t... I>
//inline VectorN<T, N> op_impl_max(const VectorN<T, N> &a, const VectorN<T, N> &b, std::index_sequence<I...>)
//{ return { std::max(a[I], b[I])... }; }

//template <typename T, size_t N, size_t... I>
//inline VectorN<T, N> op_impl_min(const VectorN<T, N> &a, const VectorN<T, N> &b, std::index_sequence<I...>)
//{ return { std::min(a[I], b[I])... }; }

//template <typename T, size_t N, size_t... I>
//inline VectorN<T, N> op_impl_abs(const VectorN<T, N> &p, std::index_sequence<I...>)
//{ return { std::abs(p[I])... }; }

//template <typename T, size_t N, size_t... I>
//inline VectorN<T, N> op_impl_pow(const VectorN<T, N> &p, const T &s, std::index_sequence<I...>)
//{ return { std::pow(p[I], s)... }; }

//template <typename T, size_t N, size_t... I>
//inline VectorN<T, N> op_impl_exp(const VectorN<T, N> &p, std::index_sequence<I...>)
//{ return { std::exp(p[I])... }; }

//template <typename T, size_t N, size_t... I>
//inline VectorN<T, N> op_impl_log(const VectorN<T, N> &p, std::index_sequence<I...>)
//{ return { std::log(p[I])... }; }

////////////////////////////////////////////////////////////////
/// Nd vector Ops
////////////////////////////////////////////////////////////////

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline std::ostream &operator<<(std::ostream &os, const VectorN<T, N>& p)
{ os << "("; op_impl_out(os, p, ", ", Indices{}) << ")"; return os; }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> abs(const VectorN<T, N> &p)
{ return op_impl_fun<T, N>(p, [] (T x) { return std::abs(x); }, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> max(const VectorN<T, N> &a, const VectorN<T, N> &b)
{ return op_impl_fun<T, N>(a, b, [] (T x, T y) { return std::max(x, y); }, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> min(const VectorN<T, N> &a, const VectorN<T, N> &b)
{ return op_impl_fun<T, N>(a, b, [] (T x, T y) { return std::min(x, y); }, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> pow(const VectorN<T, N> &p, const T &s)
{ return op_impl_fun<T, N>(p, s, [] (T x, T y) { return std::pow(x, y); }, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> exp(const VectorN<T, N> &p)
{ return op_impl_fun<T, N>(p, [] (T x) { return std::exp(x); }, Indices{}); }

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> log(const VectorN<T, N> &p)
{ return op_impl_fun<T, N>(p, [] (T x) { return std::log(x); }, Indices{}); }

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

////////////////////////////////////////////////////////////////
/// Nd vector ctors
////////////////////////////////////////////////////////////////

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
inline VectorN<T, N> make_vector(const T &s)
{ return op_impl_set<T, N>(s, Indices{}); }

#endif // N_DIMENSIONAL_VECTOR_IMPL_HH

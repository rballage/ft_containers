#pragma once

#include <memory>
#include <exception>
#include "iterators.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <exception>
#include <limits>
// #include <vector>

namespace ft
{

// 	Le trait enable_if est une technique permettant de contrôler l'application de SFINAE. Cette technique est due à Andrew Lumsdaine. L'idée générale va comme suit :
//
// Ce trait exprime un type interne et public type
// Sa signature est enable_if<bool,T=void> ce qui signifie qu'il est défini sur la base d'une condition statique de d'un type (qui sera void par défaut)
// L'expression std::enable_if<true,T>::type équivaut à T
// L'expression std::enable_if<false,T>::type est indéfinie (le type résultant est incomplet), ce qui peut (selon les circonstances) éliminer un template de ceux
// examinés pour la génération du code ou tout simplement bloquer la compilation
	template <class T>
	void swap(T &a, T &b)
	{
		T	tmp(a);
		a = b;
		b = tmp;
	};

	template <bool B, typename T = void> struct enable_if {};
	template <typename T> struct enable_if<true, T> {typedef T type;};

	struct true_type
	{
		static const bool value = true;
		typedef true_type type;
	};

	struct false_type
	{
		static const bool value = false;
		typedef false_type type;
	};

	template <typename T> struct remove_const {typedef T type;};
	template <typename T> struct remove_const<const T> {typedef T type;};
	template <typename T> struct remove_volatile {typedef T type;};
	template <typename T> struct remove_volatile<volatile T> {typedef T type;};
	template <typename T>struct remove_cv {typedef typename remove_volatile<typename remove_const<T>::type>::type type;};
	template <typename>struct is_integral_base : public false_type {};
	template <> struct is_integral_base<bool> : public true_type {};
	template <> struct is_integral_base<char> : public true_type {};
	template <> struct is_integral_base<signed char> : public true_type {};
	template <> struct is_integral_base<short int> : public true_type {};
	template <> struct is_integral_base<int> : public true_type {};
	template <> struct is_integral_base<long int> : public true_type {};
	template <> struct is_integral_base<unsigned char> : public true_type {};
	template <> struct is_integral_base<unsigned short int> : public true_type {};
	template <> struct is_integral_base<unsigned int> : public true_type {};
	template <> struct is_integral_base<unsigned long int> : public true_type {};
	template <typename T> struct is_integral : is_integral_base<typename remove_cv<T>::type> {};
	template <typename T, typename U> struct is_same : public false_type {};
	template <typename T> struct is_same<T, T> : public true_type {};

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		if ((first1 == last1 && first2 == last2))
			return true;
		if ((first1 == last1 && first2 != last2) || (first1 != last1 && first2 == last2))
			return false;
		for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	};

	template<typename T1, typename T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;
		first_type first;
		second_type second;
		pair(void) : first(first_type()), second(second_type()) {};
		pair(const first_type& a, const second_type& b) : first(a), second(b) {};
		template<typename U, typename V>
		pair(const pair<U,V>& x) : first(x.first), second(x.second) {};
		pair &operator=(const pair& x) {first = x.first; second = x.second; return *this;};
	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first==rhs.first && lhs.second==rhs.second; };
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs==rhs); };
	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); };
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs<lhs); };
	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs<lhs; };
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs<rhs); };
	template <typename T1, typename T2>
	pair<T1,T2> make_pair(T1 x, T2 y) {return (pair<T1,T2>(x,y));};
}

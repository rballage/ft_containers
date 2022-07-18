#pragma once

#include <memory>
#include <exception>
#include "iterators.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <exception>
#include <vector>

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

	template<bool condition, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <bool is_integral, typename T>
	struct is_integral_struct
	{
		typedef T type;
		static const bool value = is_integral;
	};

/*
** default template of the structure is_integral_type.
** If the type given in argument is from the list, the structure
** will be overiden by nexts, according to it's type.
** If the type given argument isn't in this list,
** is_integral_struct::value will be false if it's not an integral type.
*/

	template <typename> struct is_integral_type : public is_integral_struct<false, bool> {};
	template <> struct is_integral_type<bool> : public is_integral_struct<true, bool> {};
	template <> struct is_integral_type<char> : public is_integral_struct<true, char> {};
	template <> struct is_integral_type<signed char> : public is_integral_struct<true, signed char> {};
	template <> struct is_integral_type<short int> : public is_integral_struct<true, short int> {};
	template <> struct is_integral_type<int> : public is_integral_struct<true, int> {};
	template <> struct is_integral_type<long int> : public is_integral_struct<true, long int> {};
	template <> struct is_integral_type<long long int> : public is_integral_struct<true, long long int> {};
	template <> struct is_integral_type<unsigned char> : public is_integral_struct<true, unsigned char> {};
	template <> struct is_integral_type<unsigned short int> : public is_integral_struct<true, unsigned short int> {};
	template <> struct is_integral_type<unsigned int> : public is_integral_struct<true, unsigned int> {};
	template <> struct is_integral_type<unsigned long int> : public is_integral_struct<true, unsigned long int> {};
	template <> struct is_integral_type<unsigned long long int> : public is_integral_struct<true, unsigned long long int> {};

	/*
	** Gives a structure which contains the
	** typename given in template param if the type given is integral,
	*/

	template <typename T>
	struct is_integral : public is_integral_type<T> { };


	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
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

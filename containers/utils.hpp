namespace ft
{
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
** is_integral_struct::value will be false aka it's not a integral type.
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
}

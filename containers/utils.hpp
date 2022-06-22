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
** @brief default template of the structure is_integral_type.
** If the type given in argument is from the list, the structure
** will be overide by nexts, in according to it type.
** If the type given is argument isn't in the list,
** stocked value will be false. So it's not a integral type.
*/

	template <typename>
	struct is_integral_type : public is_integral_struct<false, bool> {};

	/* @brief is_integral_type for bool. "value is true".*/
	template <>
	struct is_integral_type<bool> : public is_integral_struct<true, bool> {};

	/* @brief is_integral_type for char. "value is true".*/
	template <>
	struct is_integral_type<char> : public is_integral_struct<true, char> {};

	/* @brief is_integral_type for signed char. "value is true".*/
	template <>
	struct is_integral_type<signed char> : public is_integral_struct<true, signed char> {};

	/* @brief is_integral_type for short int. "value is true".*/
	template <>
	struct is_integral_type<short int> : public is_integral_struct<true, short int> {};

	/* @brief is_integral_type for int. "value is true".*/
	template <>
	struct is_integral_type<int> : public is_integral_struct<true, int> {};

	/* @brief is_integral_type for long int. "value is true".*/
	template <>
	struct is_integral_type<long int> : public is_integral_struct<true, long int> {};

	/* @brief is_integral_type for long long int. "value is true".*/
	template <>
	struct is_integral_type<long long int> : public is_integral_struct<true, long long int> {};

	/* @brief is_integral_type for unsigned char. "value is true".*/
	template <>
	struct is_integral_type<unsigned char> : public is_integral_struct<true, unsigned char> {};

	/* @brief is_integral_type for unsigned short int. "value is true".*/
	template <>
	struct is_integral_type<unsigned short int> : public is_integral_struct<true, unsigned short int> {};

	/* @brief is_integral_type for unsigned int. "value is true".*/
	template <>
	struct is_integral_type<unsigned int> : public is_integral_struct<true, unsigned int> {};

	/* @brief is_integral_type for unsigned long int. "value is true".*/
	template <>
	struct is_integral_type<unsigned long int> : public is_integral_struct<true, unsigned long int> {};

	/* @brief is_integral_type for unsigned long long int. "value is true".*/
	template <>
	struct is_integral_type<unsigned long long int> : public is_integral_struct<true, unsigned long long int> {};

	/*
	** @brief Give a structure who contain is the
	** typename given in template is integral or not,
	** stocked in "value".
	*/
	template <typename T>
	struct is_integral : public is_integral_type<T> { };

}

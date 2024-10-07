

#ifndef __FMT_TYPE_TRAITS_HPP__
#define __FMT_TYPE_TRAITS_HPP__

#include <type_traits>
#include "utils.hpp"
#if !FMT_ENABEL_EXIST
namespace fmt
{
    template <typename _Tp>
    struct is_reference_of_signed : public std::false_type {};
    template <typename _Tp>
    struct is_reference_of_signed<_Tp&> : public std::is_signed<_Tp> {};
    template <typename _Tp>
    struct is_reference_of_signed<_Tp&&> : public std::is_signed<_Tp> {};

    template <typename _Tp>
    struct is_reference_of_unsigned : public std::false_type {};
    template <typename _Tp>
    struct is_reference_of_unsigned<_Tp&> : public std::is_unsigned<_Tp> {};
    template <typename _Tp>
    struct is_reference_of_unsigned<_Tp&&> : public std::is_unsigned<_Tp> {};

    template <typename _Tp>
    struct is_reference_of_integral : public std::false_type {};
    template <typename _Tp>
    struct is_reference_of_integral<_Tp&> : public std::is_integral<_Tp> {};
    template <typename _Tp>
    struct is_reference_of_integral<_Tp&&> : public std::is_integral<_Tp> {};

    template <typename _Tp>
    struct is_reference_of_floating_point : public std::false_type {};
    template <typename _Tp>
    struct is_reference_of_floating_point<_Tp&> : public std::is_floating_point<_Tp> {};
    template <typename _Tp>
    struct is_reference_of_floating_point<_Tp&&> : public std::is_floating_point<_Tp> {};

    template <typename _Tp>
    struct is_reference_of_arithmetic : public std::false_type {};
    template <typename _Tp>
    struct is_reference_of_arithmetic<_Tp&> : public std::is_arithmetic<_Tp> {};
    template <typename _Tp>
    struct is_reference_of_arithmetic<_Tp&&> : public std::is_arithmetic<_Tp> {};

    template <typename _Tp>
    struct is_reference_of_pointer : public std::false_type {};
    template <typename _Tp>
    struct is_reference_of_pointer<_Tp&> : public std::is_pointer<_Tp> {};
    template <typename _Tp>
    struct is_reference_of_pointer<_Tp&&> : public std::is_pointer<_Tp> {};

    template <typename _Tp>
    struct is_reference_of_array : public std::false_type {};
    template <typename _Tp>
    struct is_reference_of_array<_Tp&> : public std::is_array<_Tp> {};
    template <typename _Tp>
    struct is_reference_of_array<_Tp&&> : public std::is_array<_Tp> {};

    template <typename _Tp>
    struct is_character : public std::integral_constant<bool, (std::is_integral<_Tp>::value && sizeof(_Tp) == 1 && !std::is_same<_Tp, bool>::value && !std::is_same<_Tp, const bool>::value)> {};
    template <>
    struct is_character<void> : public std::false_type {};

    template <typename _Tp>
    struct is_bool : public std::integral_constant<bool, (std::is_same<_Tp, bool>::value || std::is_same<_Tp, const bool>::value)> {};

    template <typename _Tp>
    struct is_reference_of_character : public std::false_type {};
    template <typename _Tp>
    struct is_reference_of_character<_Tp&> : public is_character<_Tp> {};
    template <typename _Tp>
    struct is_reference_of_character<_Tp&&> : public is_character<_Tp> {};

    template <typename _Tp>
    struct is_reference_of_bool : public std::false_type {};
    template <typename _Tp>
    struct is_reference_of_bool<_Tp&> : public is_bool<_Tp> {};
    template <typename _Tp>
    struct is_reference_of_bool<_Tp&&> : public is_bool<_Tp> {};

    template <typename _Tp>
    struct is_cstring : public std::false_type {};
    template <typename _Tp>
    struct is_cstring<_Tp*> : public is_character<_Tp> {};
    template <typename _Tp>
    struct is_cstring<_Tp[]> : public is_character<_Tp> {};
    template <typename _Tp, size_t _Np>
    struct is_cstring<_Tp[_Np]> : public is_character<_Tp> {};
    template <typename _Tp>
    struct is_cstring<_Tp*&> : public is_character<_Tp> {};
    template <typename _Tp>
    struct is_cstring<_Tp*&&> : public is_character<_Tp> {};
    template <typename _Tp>
    struct is_cstring<_Tp(&)[]> : public is_character<_Tp> {};
    template <typename _Tp>
    struct is_cstring<_Tp(&&)[]> : public is_character<_Tp> {};
    template <typename _Tp, size_t _Np>
    struct is_cstring<_Tp(&)[_Np]> : public is_character<_Tp> {};
    template <typename _Tp, size_t _Np>
    struct is_cstring<_Tp(&&)[_Np]> : public is_character<_Tp> {};

    template <typename _Tp>
    struct type_check
    {
        static constexpr bool is_character_v =
            is_character<_Tp>::value || is_reference_of_character<_Tp>::value;

        static constexpr bool is_bool_v =
            is_bool<_Tp>::value || is_reference_of_bool<_Tp>::value;

        static constexpr bool is_signed_int_v =
            (std::is_signed<_Tp>::value || is_reference_of_signed<_Tp>::value) &&
            (std::is_integral<_Tp>::value || is_reference_of_integral<_Tp>::value);

        static constexpr bool is_unsigned_int_v =
            (std::is_unsigned<_Tp>::value || is_reference_of_unsigned<_Tp>::value) &&
            (std::is_integral<_Tp>::value || is_reference_of_integral<_Tp>::value);

        static constexpr bool is_floating_point_v =
            std::is_floating_point<_Tp>::value || is_reference_of_floating_point<_Tp>::value;

        static constexpr bool is_cstring_v =
            is_cstring<_Tp>::value;

        static constexpr bool is_pointer_v =
            (std::is_pointer<_Tp>::value || is_reference_of_pointer<_Tp>::value || 
            std::is_array<_Tp>::value || is_reference_of_array<_Tp>::value);

        static constexpr bool is_class_v =
            !(is_character_v || is_bool_v || is_signed_int_v || is_unsigned_int_v || is_floating_point_v || is_cstring_v || is_pointer_v);
    };

    template <typename>
    using void_t = void;
    template <typename T, typename Arg, typename V = void>
    struct has_out_class_function : public std::false_type {};
    template <typename T, typename Arg>
    struct has_out_class_function<T, Arg, void_t<decltype(std::declval<T>()(std::declval<Context>(), std::declval<Arg>()))>> : public std::true_type {};
} // namespace fmt

#endif
#endif // !__FMT_TYPE_TRAITS_HPP__



#ifndef __FMT_ITOA_HPP__
#define __FMT_ITOA_HPP__

#include "type_traits.hpp"
#if !FMT_ENABEL_EXIST
namespace fmt
{
    enum class IotaCase : char
    {
        Upper = 'A',
        Lower = 'a',
    };

    template <typename integral>
    size_t itoa(integral value, char *string, size_t radix = 10, IotaCase type = IotaCase::Lower);
} // namespace fmt

template <typename integral>
size_t fmt::itoa(integral value, char *string, size_t radix, IotaCase type)
{
    char tmp[33];
    char *tp = tmp;
    integral i;
    integral v;
    char sign;
    char *sp;

    static_assert(std::is_integral<integral>::value, "value is not signed integral");

    if (string == nullptr)
    {
        return 0;
    }

    if (radix > 36 || radix <= 1)
    {
        return 0;
    }

    sign = (value >= 0) ? '+' : '-';
    v = (value >= 0) ? value : -value;

    do
    {
        i = v % radix;
        v = v / radix;
        *tp++ = (i < 10) ? (i + '0') : (i + (char)type - 10);
    } while (v != 0 && (size_t)(tp - tmp) < sizeof(tmp));

    sp = string;

    if (sign == '-')
    {
        *sp++ = '-';
    }
    while (tp > tmp)
    {
        *sp++ = *--tp;
    }
    *sp = 0;

    return (size_t)(sp - string);
}
#endif
#endif // !__FMT_ITOA_HPP__

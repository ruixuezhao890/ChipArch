#if !FMT_ENABEL_EXIST
#ifndef __FMT_FORMAT_HPP__
#define __FMT_FORMAT_HPP__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <typeinfo>
#include "utils.hpp"
#include "type_traits.hpp"
#include "itoa.hpp"

namespace fmt
{
    template <class out_fct_wrap_t, typename... Args>
    size_t format_to(out_fct_wrap_t &&out_fct_wrap, const char *format, Args &&...args);

    template <size_t Index, class out_fct_wrap_t, typename Arg, typename... Args>
    bool formatter_to(size_t index, out_fct_wrap_t &&out_fct_wrap, const Context &context, Arg &&arg, Args &&...args);
    template <size_t Index, class out_fct_wrap_t>
    bool formatter_to(size_t index, out_fct_wrap_t out_fct_wrap, const Context &context) { return false; }

    template <class out_fct_wrap_t, typename Arg>
    bool out_integral_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, Arg &&arg);
    template <class out_fct_wrap_t, typename Arg>
    bool out_floating_point_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, Arg &&arg);
    template <class out_fct_wrap_t, typename Arg>
    bool ftoa_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, Arg &&arg);
    template <class out_fct_wrap_t, typename Arg>
    bool etoa_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, Arg &&arg);
    template <class out_fct_wrap_t>
    bool out_pointer_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, const void *arg);
    template <class out_fct_wrap_t>
    bool out_cstring_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, const char *arg);
    template <class out_fct_wrap_t, typename Arg>
    bool out_class_to(out_fct_wrap_t out_fct_wrap, const Context &context, Arg arg);

    template <class out_fct_wrap_t>
    bool out_rev_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, const char *buffer, size_t length);

    /**
     * @brief 格式化到控制台
     * 
     * @tparam Args 可变长模板参数包
     * @param format 格式化字符串
     * @param args 待填入format的参数
     * @return size_t 成功填入的args的数量
     */
    template <typename... Args>
    size_t print(const char *format, Args &&...args)
    {
        return format_to(putchar, format, args...);
    }

    /**
     * @brief 格式化到控制台并换行
     * 
     * @tparam Args 可变长模板参数包
     * @param format 格式化字符串
     * @param args 待填入format的参数
     * @return size_t 成功填入的args的数量
     */
    template <typename... Args>
    size_t println(const char *format, Args &&...args)
    {
        size_t retval = format_to(putchar, format, args...);
        putchar('\n');
        return retval;
    }

    /**
     * @brief 格式化到数组
     * 
     * @tparam Args 可变长模板参数包
     * @param buffer 缓冲区
     * @param size 缓冲区长度
     * @param format 格式化字符串
     * @param args 待填入format的参数
     * @return size_t 成功填入的args的数量
     */
    template <typename... Args>
    size_t format_to_buffer(void *buffer, size_t size, const char *format, Args &&...args)
    {
        char *begin = (char *)buffer;
        char *iter = (char *)buffer;
        auto out_to_buffer_wrap = [begin, &iter, size](char ch) {
            if ((size_t)(iter - begin) < size - 1)
            {
                *iter++ = ch;
                *iter = '\0';
            }
        };

        return format_to(out_to_buffer_wrap, format, args...);
    }
} // namespace fmt

/**
 * @brief 将字符串格式化, 并将格式化后的每个字符一一交给out_fct_wrap处理
 * 
 * @tparam out_fct_wrap_t 用于处理单个字符, 可以是一个函数引用类型, 也可以是一个定义了括号重载函数的类, 但其必须只接收一个类型为char的参数
 * @tparam Args 可变长模板参数包
 * @param out_fct_wrap out_fct_wrap_t的实例
 * @param format 格式化字符串
 * @param args 待填入format的参数
 * @return size_t 成功填入format的args的数量
 * 
 * @note 有关于自定义类的输出: 该功能由out_fct_wrap_t完成. 在此, out_fct_wrap_t必须是一个类, 首先要有对单个字符的处理函数(即`operator()(char)`), 其次需要有对自定义类对象的处理函数, 类型为`bool operator()(const fmt::Context &context, const MyClass &obj)`, 其中context包含format中对应花括号的信息(详见其定义), 并且有一个成员函数unpack_to可解包此段格式化字符串的信息, obj为自定义类, 需要返回布尔值
 */
template <class out_fct_wrap_t, typename... Args>
size_t fmt::format_to(out_fct_wrap_t &&out_fct_wrap, const char *format, Args &&...args)
{
    size_t count = 0, index = 0;

    if (format == nullptr)
        return count;

    while (*format != '\0')
    {
        switch (*format)
        {
        case '{':
        {
            const char *temp = format + 1;
            Context context = {.begin = format, .colon = nullptr};

            do
            {
                switch (*(++format))
                {
                case ':':
                    context.colon = (context.colon == nullptr) ? format : context.colon;
                    break;

                case '}':
                    context.end = format;
                    break;

                default:
                    break;
                }
            } while (*format != '{' && *format != '}' && *format != '\0');

            if (*format == '{')
            {
                out_fct_wrap(*format++);
            }
            else if (*format == '}')
            {
                count += formatter_to<0>(
                    (*temp >= '0' && *temp <= '9') ? atoi(temp) : index++,
                    out_fct_wrap,
                    context,
                    args...);
                format++;
            }

            break;
        }

        case '}':
        {
            do
            {
                format++;
            } while (*format != '}' && *format != '\0');
            if (*format == '}')
                out_fct_wrap(*format++);
            break;
        }

        default:
            out_fct_wrap(*format++);
            break;
        }
    }

    return count;
}

/**
 * @brief 在遇到花括号后处理单个参数的函数
 * 
 * @tparam Index 辅助参数, 用于递归定位args的参数
 * @tparam out_fct_wrap_t 用于处理单个字符, 可以是一个函数引用类型, 也可以是一个定义了括号重载函数的类, 但其必须只接收一个类型为char的参数
 * @tparam Arg 参数类型
 * @tparam Args 可变长模板参数包
 * @param index 辅助参数, 用于递归定位args的参数
 * @param out_fct_wrap out_fct_wrap_t的实例
 * @param context 上下文信息(即'{', ':', '}'的位置)
 * @param arg 待格式化参数
 * @param args 待格式化参数
 * @return true 格式化成功
 * @return false 格式化失败
 */
template <size_t Index, class out_fct_wrap_t, typename Arg, typename... Args>
bool fmt::formatter_to(size_t index, out_fct_wrap_t &&out_fct_wrap, const Context &context, Arg &&arg, Args &&...args)
{
    FormatterOption option;

    if (Index != index)
        return formatter_to<Index + 1>(index, out_fct_wrap, context, args...);

    if constexpr (type_check<Arg>::is_class_v) // 对象
    {
        if constexpr (has_out_class_function<out_fct_wrap_t, Arg>::value)
            return out_fct_wrap(context, arg);
        else
            return out_class_to(out_fct_wrap, context, arg);
    }

    context.unpack_to(option);

    if (option.type == Type::Pointer || option.type == Type::pointer) // 指针
    {
        if constexpr (type_check<Arg>::is_pointer_v || type_check<Arg>::is_cstring_v)
            return out_pointer_to(out_fct_wrap, option, (const void *)arg);
        else
            return out_pointer_to(out_fct_wrap, option, (const void *)&arg);
    }
    if constexpr (type_check<Arg>::is_character_v) // 字符型(或其引用)
    {
        option.type = (option.type == Type::None) ? Type::Chr : option.type;
        return out_integral_to(out_fct_wrap, option, arg);
    }
    else if constexpr (type_check<Arg>::is_bool_v) // 布尔型(或其引用)
    {
        option.type = (option.type == Type::None) ? Type::Bol : option.type;
        return out_integral_to(out_fct_wrap, option, arg);
    }
    else if constexpr (type_check<Arg>::is_signed_int_v) // 有符号整型(或其引用)
    {
        option.type = (option.type == Type::None) ? Type::Dec : option.type;
        return out_integral_to(out_fct_wrap, option, arg);
    }
    else if constexpr (type_check<Arg>::is_unsigned_int_v) // 无符号整型(或其引用)
    {
        option.type = (option.type == Type::None) ? Type::Dec : option.type;
        return out_integral_to(out_fct_wrap, option, arg);
    }
    else if constexpr (type_check<Arg>::is_floating_point_v) // 浮点型(或其引用)[1e-3, 1e5)
    {
        option.type = (option.type == Type::None) ? (((arg < max_float && arg >= min_float) || (-arg < max_float && -arg >= min_float)) ? Type::Float : Type::Exp) : option.type;
        return out_floating_point_to(out_fct_wrap, option, arg);
    }
    else if constexpr (type_check<Arg>::is_cstring_v) // C风格字符串
    {
        return out_cstring_to(out_fct_wrap, option, arg);
    }
    else if constexpr (type_check<Arg>::is_pointer_v) // 指针
    {
        return out_pointer_to(out_fct_wrap, option, (const void *)arg);
    }
}

/**
 * @brief 处理整型(包括字符型, 布尔型)的函数
 * 
 * @tparam out_fct_wrap_t 用于处理单个字符, 可以是一个函数引用类型, 也可以是一个定义了括号重载函数的类, 但其必须只接收一个类型为char的参数
 * @tparam Arg 参数类型
 * @param out_fct_wrap out_fct_wrap_t的实例
 * @param option 格式化信息
 * @param arg 待格式化参数
 * @return true 格式化成功
 * @return false 格式化失败
 */
template <class out_fct_wrap_t, typename Arg>
bool fmt::out_integral_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, Arg &&arg)
{
    char temp[33];
    size_t length;
    size_t radix;
    IotaCase itoa_case;

    switch (option.type)
    {
    case Type::Chr:
        return out_rev_to(out_fct_wrap, option, (const char *)&arg, 1);

    case Type::Bol:
        return out_rev_to(out_fct_wrap, option, arg ? "true" : "false", arg ? 4 : 5);

    case Type::Bin:
        radix = 2;
        itoa_case = IotaCase::Lower;
        break;

    case Type::Oct:
        radix = 8;
        itoa_case = IotaCase::Lower;
        break;

    case Type::Dec:
        radix = 10;
        itoa_case = IotaCase::Lower;
        break;

    case Type::hex:
        radix = 16;
        itoa_case = IotaCase::Lower;
        break;

    case Type::Hex:
        radix = 16;
        itoa_case = IotaCase::Upper;
        break;

    default:
        return false;
    }

    if (arg < 0 || option.sign == Sign::Minus)
    {
        length = itoa(arg, temp, radix, itoa_case);
    }
    else
    {
        temp[0] = (char)option.sign;
        length = itoa(arg, temp + 1, radix, itoa_case) + 1;
    }

    return out_rev_to(out_fct_wrap, option, temp, length);
}

/**
 * @brief 处理浮点型的函数
 * 
 * @tparam out_fct_wrap_t 用于处理单个字符, 可以是一个函数引用类型, 也可以是一个定义了括号重载函数的类, 但其必须只接收一个类型为char的参数
 * @tparam Arg 参数类型
 * @param out_fct_wrap out_fct_wrap_t的实例
 * @param option 格式化信息
 * @param arg 待格式化参数
 * @return true 格式化成功
 * @return false 格式化失败
 */
template <class out_fct_wrap_t, typename Arg>
bool fmt::out_floating_point_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, Arg &&arg)
{
    static_assert(type_check<Arg>::is_floating_point_v);

    if (arg != arg)
        return out_rev_to(out_fct_wrap, option, "nan", 3);

    if (arg < -DBL_MAX)
        return out_rev_to(out_fct_wrap, option, "-inf", 4);

    if (arg > DBL_MAX)
    {
        switch (option.sign)
        {
        case Sign::Minus:
            return out_rev_to(out_fct_wrap, option, "inf", 3);
        case Sign::Plus:
            return out_rev_to(out_fct_wrap, option, "+inf", 4);
        case Sign::Space:
            return out_rev_to(out_fct_wrap, option, " inf", 4);
        default:
            return false;
        }
    }

    switch (option.type)
    {
    case Type::Float:
        return ftoa_to(out_fct_wrap, option, arg);
    case Type::exp:
    case Type::Exp:
        return etoa_to(out_fct_wrap, option, arg);
    default:
        return false;
    }
}

/**
 * @brief 格式化为普通浮点数
 * 
 * @tparam out_fct_wrap_t 用于处理单个字符, 可以是一个函数引用类型, 也可以是一个定义了括号重载函数的类, 但其必须只接收一个类型为char的参数
 * @tparam Arg 参数类型
 * @param out_fct_wrap out_fct_wrap_t的实例
 * @param option 格式化信息
 * @param arg 待格式化参数
 * @return true 格式化成功
 * @return false 格式化失败
 */
template <class out_fct_wrap_t, typename Arg>
bool fmt::ftoa_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, Arg &&arg)
{
    char temp[66];
    char *iter = temp;
    auto value = arg;

    if (value < 0)
    {
        *iter++ = '-';
        value = -value;
    }
    else if (option.sign != Sign::Minus)
    {
        *iter++ = (char)option.sign;
    }

    if ((int)value != 0)
        iter += itoa((int)value, iter);
    else
        *iter++ = '0';
    *iter++ = '.';
    value -= (int)value;

    if (option.auto_precision)
    {
        for (size_t i = 0; value != 0 && i < 2 * sizeof(Arg) && (size_t)(iter - temp) < sizeof(temp); i++)
        {
            value *= 10;
            *iter++ = (char)value + '0';
            value -= (int)value;
        }
    }
    else
    {
        for (size_t i = 0; i < option.precision && (size_t)(iter - temp) < sizeof(temp); i++)
        {
            value *= 10;
            *iter++ = (char)value + '0';
            value -= (int)value;
        }
    }

    return out_rev_to(out_fct_wrap, option, temp, (size_t)(iter - temp));
}

/**
 * @brief 格式化为科学计数法
 * 
 * @tparam out_fct_wrap_t 用于处理单个字符, 可以是一个函数引用类型, 也可以是一个定义了括号重载函数的类, 但其必须只接收一个类型为char的参数
 * @tparam Arg 参数类型
 * @param out_fct_wrap out_fct_wrap_t的实例
 * @param option 格式化信息
 * @param arg 待格式化参数
 * @return true 格式化成功
 * @return false 格式化失败
 */
template <class out_fct_wrap_t, typename Arg>
bool fmt::etoa_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, Arg &&arg)
{
    char temp[66];
    char *iter = temp;
    auto value = arg;
    int expval;
    bool success;
    union
    {
        uint64_t intgral;
        double floating_point;
    } conv;

    value = (value < 0) ? -value : value;
    conv.floating_point = value;
    int exp2 = (int)((conv.intgral >> 52U) & 0x07FFU) - 1023;                // effectively log2
    conv.intgral = (conv.intgral & ((1ULL << 52U) - 1U)) | (1023ULL << 52U); // drop the exponent so conv.floating_point is now in [1,2)
    // now approximate log10 from the log2 integer part and an expansion of ln around 1.5
    expval = (int)(0.1760912590558 + exp2 * 0.301029995663981 + (conv.floating_point - 1.5) * 0.289529654602168);
    // now we want to compute 10^expval but we want to be sure it won't overflow
    exp2 = (int)(expval * 3.321928094887362 + 0.5);
    const double z = expval * 2.302585092994046 - exp2 * 0.6931471805599453;
    const double z2 = z * z;
    conv.intgral = (uint64_t)(exp2 + 1023) << 52U;
    // compute exp(z) using continued fractions, see https://en.wikipedia.org/wiki/Exponential_function#Continued_fractions_for_ex
    conv.floating_point *= 1 + 2 * z / (2 - z + (z2 / (6 + (z2 / (10 + z2 / 14)))));
    // correct for rounding errors
    if (value < conv.floating_point)
    {
        expval--;
        conv.floating_point /= 10;
    }

    auto base = arg;
    base /= conv.floating_point;
    success = ftoa_to(out_fct_wrap,
                      {
                          .sign = option.sign,
                          .width = 0,
                          .auto_precision = option.auto_precision,
                          .precision = option.precision,
                          .type = Type::Float,
                      },
                      base);

    if (!success)
        return false;

    out_fct_wrap((char)option.type);
    return out_integral_to(out_fct_wrap, {.type = Type::Dec}, expval);
}

/**
 * @brief 处理指针输出地址的函数
 * 
 * @tparam out_fct_wrap_t 用于处理单个字符, 可以是一个函数引用类型, 也可以是一个定义了括号重载函数的类, 但其必须只接收一个类型为char的参数
 * @param out_fct_wrap out_fct_wrap_t的实例
 * @param option 格式化信息
 * @param arg 待格式化参数
 * @return true 格式化成功
 * @return false 格式化失败
 */
template <class out_fct_wrap_t>
bool fmt::out_pointer_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, const void *arg)
{
    char temp[33];
    uintptr_t ptr = (uintptr_t)arg;
    size_t length = itoa(ptr, temp, 16, (option.type == Type::Pointer) ? IotaCase::Upper : IotaCase::Lower);

    if (length >= option.width)
    {
        for (size_t i = 0; i < length; i++)
            out_fct_wrap(temp[i]);
        return true;
    }

    return out_rev_to(out_fct_wrap, option, temp, length);
}

/**
 * @brief 处理C风格字符串的函数
 * 
 * @tparam out_fct_wrap_t 用于处理单个字符, 可以是一个函数引用类型, 也可以是一个定义了括号重载函数的类, 但其必须只接收一个类型为char的参数
 * @param out_fct_wrap out_fct_wrap_t的实例
 * @param option 格式化信息
 * @param arg 待格式化参数
 * @return true 格式化成功
 * @return false 格式化失败
 */
template <class out_fct_wrap_t>
bool fmt::out_cstring_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, const char *arg)
{
    size_t length = strlen(arg);

    if (length >= option.width)
    {
        for (size_t i = 0; i < length; i++)
            out_fct_wrap(arg[i]);
        return true;
    }

    return out_rev_to(out_fct_wrap, option, arg, length);
}

/**
 * @brief 处理无用户输出函数的类对象
 * 
 * @tparam out_fct_wrap_t 用于处理单个字符, 可以是一个函数引用类型, 也可以是一个定义了括号重载函数的类, 但其必须只接收一个类型为char的参数
 * @tparam Arg 参数类型
 * @param out_fct_wrap out_fct_wrap_t的实例
 * @param context 上下文信息
 * @param arg 待格式化参数
 * @return true 格式化成功
 * @return false 格式化失败
 */
template <class out_fct_wrap_t, typename Arg>
bool fmt::out_class_to(out_fct_wrap_t out_fct_wrap, const Context &context, Arg arg)
{
    FormatterOption option;
    const char *temp = typeid(Arg).name();
    context.unpack_to(option);
    return out_rev_to(out_fct_wrap, option, temp, strlen(temp));
}

/**
 * @brief 处理对齐方式的函数
 * 
 * @tparam out_fct_wrap_t 用于处理单个字符, 可以是一个函数引用类型, 也可以是一个定义了括号重载函数的类, 但其必须只接收一个类型为char的参数
 * @param out_fct_wrap out_fct_wrap_t的实例
 * @param option 格式化信息
 * @param buffer 未处理对齐方式前的缓冲区
 * @param length buffer的长度
 * @return true 格式化成功
 * @return false 格式化失败
 */
template <class out_fct_wrap_t>
bool fmt::out_rev_to(out_fct_wrap_t out_fct_wrap, const FormatterOption &option, const char *buffer, size_t length)
{
    if (option.width <= length)
    {
        for (size_t i = 0; i < length; i++)
            out_fct_wrap(buffer[i]);
        return true;
    }

    switch (option.align)
    {
    case Align::Left:
        for (size_t i = 0; i < length; i++)
            out_fct_wrap(buffer[i]);
        for (size_t i = 0; i < option.width - length; i++)
            out_fct_wrap(option.fill);
        return true;

    case Align::Center:
        for (size_t i = 0; i < (option.width - length) / 2; i++)
            out_fct_wrap(option.fill);
        for (size_t i = 0; i < length; i++)
            out_fct_wrap(buffer[i]);
        for (size_t i = 0; i < (option.width - length + 1) / 2; i++)
            out_fct_wrap(option.fill);
        return true;

    case Align::Right:
        for (size_t i = 0; i < option.width - length; i++)
            out_fct_wrap(option.fill);
        for (size_t i = 0; i < length; i++)
            out_fct_wrap(buffer[i]);
        return true;

    default:
        return false;
    }
}
#endif
#endif // !__FMT_FORMAT_HPP__

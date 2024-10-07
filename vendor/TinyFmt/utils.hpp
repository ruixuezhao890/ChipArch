
#ifndef __FMT_UTILS_HPP__
#define __FMT_UTILS_HPP__
#include "./ChipArchConfig.h"
#include <cstdint>
#include <cstddef>
#if !FMT_ENABEL_EXIST
namespace fmt
{
    static constexpr double max_float = 1e5;  // 未特别指明类型, 绝对值大于此值的浮点数会输出为科学计数法
    static constexpr double min_float = 1e-3; // 未特别指明类型, 绝对值小于此值的浮点数会输出为科学计数法

    enum class Align : char
    {
        Left = '<',   // 左对齐(默认)
        Center = '^', // 居中对齐
        Right = '>',  // 右对齐
    };

    enum class Sign : char
    {
        Plus = '+',  // 强制在结果之前显示符号, 正数前面显示"+", 负数前面显示"-"
        Minus = '-', // 不强制在结果之前显示符号, 即只有负数前面会显示"-"(默认)
        Space = ' ', // 正数前面插入空格, 负数无变化
    };

    enum class Type : char
    {
        Bin = 'b',     // 二进制
        Oct = 'o',     // 八进制
        Dec = 'd',     // 十进制(输入为多字节整型时为默认)
        hex = 'x',     // 小写字母的十六进制
        Hex = 'X',     // 大写字母的十六进制
        Bol = 's',     // 布尔值, 即"true"和"false"(输入为布尔型时为默认)
        Chr = 'c',     // 字符(输入为单字节整型时为默认)
        Float = 'f',   // 普通浮点数(输入为在范围内的浮点数时为默认)
        exp = 'e',     // 科学计数法, 小写(输入为在Float范围外的浮点数时为默认)
        Exp = 'E',     // 科学计数法, 大写
        pointer = 'p', // 指针地址, 小写, 输出格式为十六进制(输入为非单字节整型指针(数组)以外的指针(数组)时为默认)
        Pointer = 'P', // 指针地址, 大写, 输出格式为十六进制
        None = 'n',    // 格式化字符串中缺省时为此值, 会转变为对应的默认值
    };

    static inline constexpr bool is_digit(char ch) { return ch <= '9' && ch >= '0'; }
    static inline constexpr bool is_upper(char ch) { return ch <= 'Z' && ch >= 'A'; }
    static inline constexpr bool is_lower(char ch) { return ch <= 'z' && ch >= 'a'; }
    static inline constexpr char upper(char ch) { return is_lower(ch) ? (ch - 'a' + 'A') : ch; }
    static inline constexpr char lower(char ch) { return is_upper(ch) ? (ch - 'A' + 'a') : ch; }

    static inline constexpr bool is_align(char ch) { return ch == '<' || ch == '^' || ch == '>'; }
    static inline constexpr bool is_sign(char ch) { return ch == '+' || ch == '-' || ch == ' '; }
    static inline constexpr bool is_type(char ch) { return ch == 'b' || ch == 'o' || ch == 'd' || ch == 'x' || ch == 'X' || ch == 's' || ch == 'c' || ch == 'f' || ch == 'e' || ch == 'E' || ch == 'p' || ch == 'P'; }

    /**
     * @brief 格式化字符串中的格式化输出信息
     *
     * @note 格式为 {[index][:[fill][align][sign][width][.precision][type]]}
     */
    struct FormatterOption
    {
        char fill = ' ';           // 填充字符(仅在width大于原输出宽度时有效)
        Align align = Align::Left; // 对齐方式(仅在width大于原输出宽度时有效)
        Sign sign = Sign::Space;   // 符号位
        uint8_t width;             // 输出宽度(仅在width大于原输出宽度时有效)
        bool auto_precision;       // 自动精度(仅浮点型数据有效, 当且仅当不指定精度时为真)
        uint8_t precision;         // 精度(仅浮点型数据且指定精度时有效)
        Type type = Type::None;    // 输出类型
    };

    /**
     * @brief 包含格式化字符串中{...}的信息
     *
     */
    struct Context
    {
        const char *begin = nullptr; // 指向'{'
        const char *colon = nullptr; // 指向':'
        const char *end = nullptr;   // 指向'}'
        void unpack_to(FormatterOption &option) const;
    };
} // namespace fmt

/**
 * @brief 解包格式化字符串的信息到option中
 *
 * @param option[out] 格式化字符串信息解包到的地方
 *
 * @note {[index][:[fill][align][sign][width][.precistion][type]]}
 */
inline void fmt::Context::unpack_to(FormatterOption &option) const
{
    auto iter = this->colon + 1;

    option = {
        .fill = ' ',
        .align = Align::Left,
        .sign = Sign::Minus,
        .width = 0,
        .auto_precision = true,
        .precision = 6,
        .type = Type::None,
    };

    if (iter >= this->end || this->begin == nullptr || this->colon == nullptr || this->end == nullptr)
        return;

    if (iter + 1 < this->end && is_align(*(iter + 1)))
    {
        option.fill = *iter;
        option.align = static_cast<Align>(*(iter + 1));
        iter += 2;
    }
    else if (is_align(*iter))
    {
        option.align = static_cast<Align>(*iter);
        iter++;
    }

    if (iter >= this->end)
        return;

    if (is_sign(*iter))
    {
        option.sign = static_cast<Sign>(*iter);
        iter++;
    }

    if (iter >= this->end)
        return;

    if (is_digit(*iter))
    {
        do
        {
            option.width = option.width * 10 + *iter++ - '0';
        } while (is_digit(*iter) && iter < this->end);
    }

    if (iter >= this->end)
        return;

    if (*iter == '.')
    {
        iter++;
        option.auto_precision = false;
        option.precision = 0;
        while (is_digit(*iter) && iter < this->end)
            option.precision = option.precision * 10 + *iter++ - '0';
    }

    if (iter >= this->end)
        return;

    if (*iter == 'X' || *iter == 'P' || *iter == 'E')
        option.type = static_cast<Type>(*iter);
    else if (is_type(lower(*iter)))
        option.type = static_cast<Type>(lower(*iter));
}

#endif
#endif // !__FMT_UTILS_HPP__

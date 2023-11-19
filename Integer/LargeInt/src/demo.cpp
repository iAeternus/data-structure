/********************************************
* [大数加减乘除].CPP.A.0
*********************************************/

#include <iostream>
#include <vector>
#include <algorithm>

class LargeInt {
private:
    bool positive;              // 正负号
    std::vector<int> digits;    // 存储数字的动态数组

public:
    // 构造函数
    LargeInt() {
        positive = true;
        digits.push_back(0);
    }

    explicit LargeInt(const std::string& numberString) {
        positive = true;

        // 判断正负号
        if (numberString[0] == '-') {
            positive = false;
        }

        // 逐个字符解析数字并存储到digits数组中
        for (int i = numberString.length() - 1; i >= (positive ? 0 : 1); --i) {
            int digit = numberString[i] - '0';
            digits.push_back(digit);
        }
    }

    // 输入输出操作
    friend std::ostream& operator<<(std::ostream& os, const LargeInt& num) {
        if (!num.positive) {
            os << "-";
        }

        for (int i = num.digits.size() - 1; i >= 0; --i) {
            os << num.digits[i];
        }

        return os;
    }

    friend std::istream& operator>>(std::istream& is, LargeInt& num) {
        std::string input;
        is >> input;

        num.digits.clear();
        num.positive = true;

        if (input[0] == '-') {
            num.positive = false;
        }

        for (int i = input.length() - 1; i >= (num.positive ? 0 : 1); --i) {
            int digit = input[i] - '0';
            num.digits.push_back(digit);
        }

        return is;
    }

    // 运算符重载
    LargeInt operator+(const LargeInt& other) const {
        LargeInt result;
        result.digits.clear();

        if (positive == other.positive) {
            result.positive = positive;

            int carry = 0;
            int maxSize = std::max(digits.size(), other.digits.size());

            for (int i = 0; i < maxSize || carry; ++i) {
                int sum = carry;

                if (i < digits.size()) {
                    sum += digits[i];
                }

                if (i < other.digits.size()) {
                    sum += other.digits[i];
                }

                result.digits.push_back(sum % 10);
                carry = sum / 10;
            }
        } else {
            if (absoluteGreater(other)) {
                result.positive = positive;
            } else {
                result.positive = other.positive;
            }

            const LargeInt& bigger = absoluteGreater(other) ? *this : other;
            const LargeInt& smaller = absoluteGreater(other) ? other : *this;

            int borrow = 0;

            for (int i = 0; i < bigger.digits.size(); ++i) {
                int diff = borrow + bigger.digits[i];

                if (i < smaller.digits.size()) {
                    diff -= smaller.digits[i];
                }

                if (diff < 0) {
                    diff += 10;
                    borrow = -1;
                } else {
                    borrow = 0;
                }

                result.digits.push_back(diff);
            }

            // 移除结果高位的零
            while (result.digits.size() > 1 && result.digits.back() == 0) {
                result.digits.pop_back();
            }
        }

        return result;
    }

    LargeInt operator-(const LargeInt& other) const {
        LargeInt negativeOther = other;
        negativeOther.positive = !negativeOther.positive;
        return *this + negativeOther;
    }

    LargeInt operator*(const LargeInt& other) const {
        LargeInt result;
        result.digits.assign(digits.size() + other.digits.size(), 0);

        for (int i = 0; i < digits.size(); ++i) {
            int carry = 0;

            for (int j = 0; j < other.digits.size() || carry; ++j) {
                long long product = result.digits[i + j] + carry +
                    (long long)digits[i] * (j < other.digits.size() ? other.digits[j] : 0);
                result.digits[i + j] = product % 10;
                carry = product / 10;
            }
        }

        // 移除结果高位的零
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        result.positive = !(positive ^ other.positive);
        return result;
    }

    LargeInt operator/(const LargeInt& other) const {
        if (other.digits.size() == 1 && other.digits[0] == 0) {
            throw std::runtime_error("Divide by zero");
        }

        LargeInt quotient;
        quotient.digits.assign(digits.size(), 0);

        LargeInt remainder;

        for (int i = digits.size() - 1; i >= 0; --i) {
            remainder.digits.insert(remainder.digits.begin(), digits[i]);

            int digit = 0;

            while (remainder.absoluteGreater(other)) {
                remainder = remainder - other;
                ++digit;
            }

            quotient.digits[i] = digit;
        }

        // 移除商的高位的零
        while (quotient.digits.size() > 1 && quotient.digits.back() == 0) {
            quotient.digits.pop_back();
        }

        quotient.positive = !(positive ^ other.positive);
        return quotient;
    }

    LargeInt operator%(const LargeInt& other) const {
        if (other.digits.size() == 1 && other.digits[0] == 0) {
            throw std::runtime_error("Divide by zero");
        }

        LargeInt quotient;
        quotient.digits.assign(digits.size(), 0);

        LargeInt remainder;

        for (int i = digits.size() - 1; i >= 0; --i) {
            remainder.digits.insert(remainder.digits.begin(), digits[i]);

            int digit = 0;

            while (remainder.absoluteGreater(other)) {
                remainder = remainder - other;
                ++digit;
            }

            quotient.digits[i] = digit;
        }

        // 移除商的高位的零
        while (quotient.digits.size() > 1 && quotient.digits.back() == 0) {
            quotient.digits.pop_back();
        }

        remainder.positive = positive;
        return remainder;
    }

private:
    bool absoluteGreater(const LargeInt& other) const {
        if (digits.size() != other.digits.size()) {
            return digits.size() > other.digits.size();
        }

        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i]) {
                return digits[i] > other.digits[i];
            }
        }

        return false;
    }
};

//主函数
int main() {
    LargeInt a, b;
    std::cout << "Input first number: ";
    std::cin >> a;
    std::cout << "Input second number: ";
    std::cin >> b;
    std::cout << "add: " << a + b << std::endl;
    std::cout << "sub: " << a - b << std::endl;
    std::cout << "mul: " << a * b << std::endl;

    try {
        std::cout << a / b << std::endl;
        std::cout << a % b << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
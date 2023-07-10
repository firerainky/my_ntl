// From: ChatGPT

#include <complex>
#include <iostream>
#include <valarray>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> ComplexArray;

// 快速傅里叶变换递归函数
void fft(ComplexArray& x)
{
    const size_t N = x.size();
    if (N <= 1) {
        return;
    }

    // 分离奇偶数索引
    ComplexArray even = x[std::slice(0, N/2, 2)];
    ComplexArray odd = x[std::slice(1, N/2, 2)];

    // 递归计算奇偶数部分的FFT
    fft(even);
    fft(odd);

    // 合并结果
    for (size_t k = 0; k < N/2; ++k) {
        Complex t = std::polar(1.0, -2 * M_PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N/2] = even[k] - t;
    }
}

// 打印复数数组
void printComplexArray(const ComplexArray& arr)
{
    for (const auto& val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main()
{
    // 输入要进行FFT的复数序列
    ComplexArray x = {std::complex<double>(1.0), std::complex<double>(2.0, -1.0), std::complex<double>(0, -1.0), std::complex<double>(-1.0, 2.0)};
    // ComplexArray x = {std::complex<double>(3.0), std::complex<double>(3.0), std::complex<double>(2.0), std::complex<double>(-2.0)};

    std::cout << "原始序列: ";
    printComplexArray(x);

    // 进行FFT变换
    fft(x);

    std::cout << "FFT结果: ";
    printComplexArray(x);

    return 0;
}

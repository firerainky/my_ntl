#include "my-ftt.h"

const double pi = acos(-1.0);

void MyFft(Complex* coeffs, size_t size) {
    if (size <= 1) return;

    size_t half = size / 2;
    Complex A1[half], A2[half];

    for (int i = 0; i < half; ++i) {
        A1[i] = coeffs[2 * i];
        A2[i] = coeffs[2 * i + 1];
    }

    MyFft(A1, half);
    MyFft(A2, half);

    Complex w0(1.0), wn(cos( 2 * pi / size ), sin( 2 * pi / size));
    for (int i = 0; i < half; ++i, w0 *= wn) {
        coeffs[i] = A1[i] + w0 * A2[i];
        coeffs[i + half] = A1[i] - w0 * A2[i];
    }
}

// TODO: The inverse FFT result need to divide size and we have the precision problem.
void MyFftVec(ComplexVec &coeffs, bool inv) {
    if (coeffs.size() <= 1) return;
    double inversion = inv ? -1.0 : 1.0;

    size_t half = coeffs.size() / 2;
    ComplexVec A1, A2;

    for (int i = 0; i < half; ++i) {
        A1.push_back(coeffs[2 * i]);
        A2.push_back(coeffs[2 * i + 1]);
    }

    MyFftVec(A1);
    MyFftVec(A2);

    Complex w0(1.0), wn(cos( 2 * pi / coeffs.size() ), inversion * sin( 2 * pi / coeffs.size() ));
    for (int i = 0; i < half; ++i, w0 *= wn) {
        coeffs[i] = A1[i] + w0 * A2[i];
        coeffs[i + half] = A1[i] - w0 * A2[i];
    }
}

void change(ComplexVec &coeffs) {
    size_t i, j, k;
    size_t len = coeffs.size();
    for (int i = 1, j = len / 2; i < len - 1;) {
        if (i < j) {    // Swap i, j
            Complex temp = coeffs[i];
            coeffs[i] = coeffs[j];
            coeffs[j] = temp;
        }
        // i++, j 变成新的 i 对应的值, 保证 i 与 j 始终是反转的
        ++i;
        k = len / 2;
        while (j >= k) {
            j = j - k;
            k >>= 1;
        }
        if (j < k) j += k;
    }
}

void MyFftVecOptimize(ComplexVec &coeffs, bool inv) {
    change(coeffs);
    size_t len = coeffs.size();
    double inversion = inv ? -1.0 : 1.0;

    for (size_t h = 2; h <= len; h <<= 1) {
        Complex wn(cos(2 * pi / h), inversion * sin(2 * pi / h));

        for (size_t j = 0; j < len; j+= h) {
            Complex w(1);
            for (size_t k = j; k < j + h/2; ++k) {
                Complex u = coeffs[k];
                Complex t = w * coeffs[k + h/2];
                coeffs[k] = u + t;
                coeffs[k + h/2] = u - t;
                w = w * wn;
            }
        }
    }

    if (inv) {
        for (size_t i = 0; i < len; ++i) {
            coeffs[i] /= len;
            // TODO: Precision problem.
            double eps = 1e-6;
            if (abs(coeffs[i].real()) < eps) {
                coeffs[i].real(0);
            }
        }
    }
}

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

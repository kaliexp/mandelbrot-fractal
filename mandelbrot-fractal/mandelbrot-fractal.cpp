#include <iostream>
#include <complex>
#include <string>

double map(double value, double start1, double stop1, double start2, double stop2) {
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

int main() {
    const int width = 80;
    const int height = 40;
    const int maxIterations = 1000;
    const std::string gradient = " .:-=+*#%@";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double a = map(x, 0, width, -2.0, 1.0);
            double b = map(y, 0, height, -1.5, 1.5);
            std::complex<double> c(a, b);
            std::complex<double> z(0, 0);

            int iterations = 0;
            while (std::abs(z) < 2.0 && iterations < maxIterations) {
                z = z * z + c;
                iterations++;
            }

            int index = iterations * gradient.size() / maxIterations;
            if (index >= gradient.size()) index = gradient.size() - 1;
            std::cout << gradient[index];
        }
        std::cout << std::endl;
    }

    return 0;
}

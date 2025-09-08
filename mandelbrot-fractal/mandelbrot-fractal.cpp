#include <iostream>
#include <complex>
#include <fstream>
#include <string>

double map(double value, double start1, double stop1, double start2, double stop2) {
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

int main() {
    const int width = 80;
    const int height = 40;
    const int maxIterations = 1000;
    const std::string gradient = " .:-=+*#%@";

    std::cout << "select output:\n1 - console (ASCII)\n2 - file PPM\nselect: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
		// output to console
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
    }
    else if (choice == 2) {
		// output to PPM file
        std::ofstream file("fractal.ppm");
        if (!file) {
            std::cerr << "error: failed to create file" << std::endl;
            return 1;
        }

        const int ppmWidth = 800;
        const int ppmHeight = 600;
        file << "P3\n" << ppmWidth << " " << ppmHeight << "\n255\n";

        for (int y = 0; y < ppmHeight; y++) {
            for (int x = 0; x < ppmWidth; x++) {
                double a = map(x, 0, ppmWidth, -2.0, 1.0);
                double b = map(y, 0, ppmHeight, -1.5, 1.5);
                std::complex<double> c(a, b);
                std::complex<double> z(0, 0);

                int iterations = 0;
                while (std::abs(z) < 2.0 && iterations < maxIterations) {
                    z = z * z + c;
                    iterations++;
                }

                int r = (iterations * 5) % 256;
                int g = (iterations * 2) % 256;
                int bColor = (iterations * 3) % 256;

                file << r << " " << g << " " << bColor << " ";
            }
            file << "\n";
        }

        file.close();
        std::cout << "fractal saved to fractal.ppm" << std::endl;
    }
    else {
        std::cout << "wrong choice!" << std::endl;
    }

    return 0;
}

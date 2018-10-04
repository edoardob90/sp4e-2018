#include <iostream>

double* get_vector(int n) {
    double v[n]; // this won't work
    for (int i=0; i<n; ++i) {
        v[i] = 10.;
    }
    return v;
}

int main (int argc, char** argv) {
    std::cout << "Give me the array size: ";
    int n;
    std::cin >> n;

    double* vec = get_vector(n);

    return EXIT_SUCCESS;
}

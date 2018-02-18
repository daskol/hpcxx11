//  main.cc

#include "hpc++11.h"
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<float> a(1024 * 1024);
    std::vector<float> b(1024 * 1024);
    std::vector<float> c(1024 * 1024);

    for (size_t i = 0; i != a.size(); ++i) {
        a[i] = i;
        b[i] = b.size() - i - 1;
    }

    sum_vectors(a, b, c);

    return 0;
}

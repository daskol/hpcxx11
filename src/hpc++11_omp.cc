#include "hpc++11.h"

#include <cassert>
#include <omp.h>

void sum_vectors(std::vector<float> const &a,
                 std::vector<float> const &b,
                 std::vector<float> &c) {

    assert(a.size() == b.size());
    assert(a.size() == c.size());

    const auto a_data = a.data();
    const auto b_data = b.data();
    auto c_data = c.data();
    size_t size = c.size();

    omp_set_num_threads(4);

#pragma omp parallel
    for (size_t i = 0; i != size; ++i) {
        c_data[i] = a_data[i] + b_data[i];
    }
}

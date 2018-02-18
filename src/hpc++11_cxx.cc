#include "hpc++11.h"

#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>

void sum_vectors_block(const float *a, const float *b, float *c, size_t size) {
//    std::stringstream ss;
//    ss << std::hex
//        << "[0x"
//        << std::setw(16) << std::setfill('0') << std::this_thread::get_id()
//        << "] "
//        << "block size = " << std::dec << size << " bytes" << std::endl;
//    std::cout << ss.str();

    for (size_t i = 0; i != size; ++i) {
        c[i] = a[i] + b[i];
    }
}

void sum_vectors(std::vector<float> const &a,
                 std::vector<float> const &b,
                 std::vector<float> &c) {

    assert(a.size() == b.size());
    assert(a.size() == c.size());

    unsigned nothreads = std::thread::hardware_concurrency();
    unsigned block_size = a.size() / nothreads;

    std::vector<std::thread> threads;

    for (unsigned i = 0; i != nothreads - 1; ++i) {
        const auto a_begin = a.data() + i * block_size;
        const auto b_begin = b.data() + i * block_size;
        auto c_begin = c.data() + i * block_size;

        threads.emplace_back(std::thread(sum_vectors_block,
                                         a_begin,
                                         b_begin,
                                         c_begin,
                                         block_size));
    }

    const auto a_begin = a.data() + (nothreads - 1) * block_size;
    const auto b_begin = b.data() + (nothreads - 1) * block_size;
    auto c_begin = c.data() + (nothreads - 1) * block_size;
    size_t rest_size = a.size() - (nothreads - 1) * block_size;

    sum_vectors_block(a_begin, b_begin, c_begin, rest_size);

    for (auto it = threads.begin(); it != threads.end(); ++it) {
        it->join();
    }
}

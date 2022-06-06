//#include "allocator.h"
//#include <iostream>
//#include <vector>
#include <list>
//#include <deque>
//#include <ctime>
//#include <unordered_map>

const int NUM_OF_TESTS = 1000000;

int main() {
//    int start_time;
//    std::cout << "vector" << "\n";
//    start_time = clock();
//    std::vector<double, bornik::allocator<double, 2, 1048576>> test1;
//    for (auto i = 0; i < NUM_OF_TESTS; ++i)
//        test1.push_back(i);
//    for (auto i = 0; i < NUM_OF_TESTS; ++i)
//        test1.pop_back();
//    std::cout << "BornikAllocator - " << clock() - start_time << "\n";
//
//    start_time = clock();
//    std::vector<double> test12;
//    for (auto i = 0; i < NUM_OF_TESTS; ++i)
//        test12.push_back(i);
//    for (auto i = 0; i < NUM_OF_TESTS; ++i)
//        test12.pop_back();
//    std::cout << "std::allocator - " << clock() - start_time << "\n" << "\n";

//    std::cout << "list" << "\n";
//    start_time = clock();
//    std::list<double, bornik::allocator<double, NUM_OF_TESTS, 1>> test2;
//    for (auto i = 0; i < NUM_OF_TESTS; ++i)
//        test2.push_back(i);
//    for (auto i = 0; i < NUM_OF_TESTS; ++i)
//        test2.pop_back();
//    std::cout << "BornikAllocator - " << clock() - start_time << "\n";

//    start_time = clock();
    std::list<double> test22;
    for (auto i = 0; i < NUM_OF_TESTS; ++i)
        test22.push_back(i);
    for (auto i = 0; i < NUM_OF_TESTS; ++i)
        test22.pop_back();
//    std::cout << "std::allocator - " << clock() - start_time << "\n" << "\n";
//
//    std::cout << "deque" << "\n";
//    start_time = clock();
//    std::deque<double, bornik::allocator<double, 16000, 41000>> test3;
//    for (auto i = 0; i < NUM_OF_TESTS; ++i)
//        test3.push_back(i);
//    for (auto i = 0; i < NUM_OF_TESTS; ++i)
//        test3.pop_back();
//    std::cout << "BornikAllocator - " << clock() - start_time << "\n";
//
//    start_time = clock();
//    std::deque<double> test32;
//    for (auto i = 0; i < NUM_OF_TESTS; ++i)
//        test32.push_back(i);
//    for (auto i = 0; i < NUM_OF_TESTS; ++i)
//        test32.pop_back();
//    std::cout << "std::allocator - " << clock() - start_time << "\n" << "\n";
//
//    std::cout << "unordered_map" << "\n";
//    start_time = clock();
//    std::unordered_map<int, int, hash<int>, equal_to<>, bornik::allocator<pair<const int, int>, 10001, 20546>> test4;
//    for (auto i = 0; i < 10000; ++i)
//        test4.insert({i, i});
//    std::cout << "BornikAllocator - " << clock() - start_time << "\n";
//
//    start_time = clock();
//    std::unordered_map<double, double> test42;
//    for (auto i = 0; i < 10000; ++i)
//        test42.insert({i, i});
//    std::cout << "std::allocator - " << clock() - start_time << "\n";
    return 0;
}
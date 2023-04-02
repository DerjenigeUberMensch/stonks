#include <random>

int rng(int min, int max) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(min,max);
    return dist(rd);
}
/*
#include <random>
int rng(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}
*/
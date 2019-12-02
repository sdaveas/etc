#include <iostream>
#include <vector>
#include <optional>
#include <cstring>

std::optional<int> linear_search(std::vector<int>& v, int target)
{
    for (auto i:v) {
        if (i == target) {
            return i;
        }
    }
    return std::nullopt;
}

std::optional<int> binary_search(std::vector<int> v, int target)
{
    if (v.size() == 1) {
        if (v[0] == target) {
            return v[0] == target ? target : std::nullopt;
        }
    }
    if (target < v[v.size()/2]) {
        return binary_search(std::vector<int>{v.begin(), v.begin()+v.size()/2}, target);
    }
    else {
        return binary_search(std::vector<int>{v.begin()+v.size()/2, v.end()}, target);
    }
}

int main(int argc, char* argv[])
{
    int type = 0;
    if (argc > 1) {
        if (strcmp(argv[1], "l") == 0) {
            type = 1;
        }
        else if (strcmp(argv[1], "b") == 0) {
            type = 2;
        }
        else {
            std::cout << "Please define a type (1: linear, 2: binary)" << std::endl;
            return -1;
        }
    }
    else {
        std::cout << "Please define a type (1: linear, 2: binary)" << std::endl;
        return -1;
    }

    std::vector<int> v;
    long long unsigned int size = 1<<30;
    int target = 1024;

    for (int i=0; i<size; i++) {
        v.push_back(i);
    }

    if (type == 1) {
        auto res = linear_search(v, target).value_or(-1);
        std::cout << "Linear search returned " << res << std::endl;
    }
    else if (type == 2) {
        auto res = linear_search(v, target).value_or(-1);
        std::cout << "Binary search returned " << res << std::endl;
    }

    return 0;
}

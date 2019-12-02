#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

template <typename T>
std::pair<T, bool> find_missing_1(std::vector<T> & first, std::vector<T> & second)
{
    auto xor_result = T();
    for (auto a : first) {
        xor_result = xor_result xor a;
    }

    for (auto a : second) {
        xor_result = xor_result xor a;
    }

    bool found = false;
    if ((xor_result | 0) == 0) {
        found = false;
    }
    else {
        found = true;
    }

    return {xor_result, found};
}

template<typename T>
std::pair<T, bool> find_missing_2(std::vector<T> & first, std::vector<T> & second)
{
    std::unordered_map<int, bool> my_map;

    for (auto f:first) {
        my_map.insert({f, 0});
    }

    for (auto s:second) {
        if (my_map.find(s) == my_map.end()) {
            return {s, true};
        }
    }

    return {T(), false};
}

template<typename T>
std::pair<T, bool> find_missing_3(std::vector<T> first, std::vector<T> second)
{
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    bool found = false;
    T missing = 0;
    size_t min_size = 0;
    min_size = first.size() < second.size() ? first.size() : second.size();

    for (int i=0; i<min_size; i++) {
        if (first[i] != second[i]) {
            missing = first.size() > second.size() ? first[i] : second[i];
            found = true;
            break;
        }
    }

    if (!found && first.size() == second.size()) {
        return {T(), false};
    }
    else if (!found) {
        missing = first.size() > second.size() ? first[first.size() - 1] : second[second.size() - 1];
    }

    return {missing, true};
}

template<typename T>
std::pair<T, bool> find_missing_4(std::vector<T> & first, std::vector<T> & second)
{
    std::set<T> my_set;
    for (auto a : first) {
        my_set.insert(a);
    }

    for (auto a : second) {
        if (my_set.find(a) == my_set.end()) {
            return {a, true};
        }
    }

    return {T(), false};
}

template<typename T>
std::pair<T, bool> find_missing_5(std::vector<T> & first, std::vector<T> & second)
{
    if (first.size() > second.size()) {
        for (auto f:first) {
            if (std::find(second.begin(), second.end(), f) == second.end()) {
                return {f ,true};
            }
        }
    }
    else {
        for (auto f:second) {
            if (std::find(first.begin(), first.end(), f) == first.end()) {
                return {f ,true};
            }
        }
    }


    return {T(), false};
}

void init_vector(std::vector<int> & v, int digits)
{
    for (int i=digits; i>=0; i--) v.push_back(i);
}

int main()
{
    int size = 200000;
    std::vector<int> first;
    std::vector<int> second;
    init_vector(first,  size);
    init_vector(second, size);

    // mess firest vector arround
    std::swap(first[first.size()/2], first[first.size()-1]);
    first.pop_back();

    auto result_1 = find_missing_1(first, second);
    std::cout << "Found: " << result_1.first << "(" << result_1.second << ")" << std::endl;
    auto result_2 = find_missing_2(first, second);
    std::cout << "Found: " << result_2.first << "(" << result_2.second << ")" << std::endl;
    auto result_3 = find_missing_3(first, second);
    std::cout << "Found: " << result_3.first << "(" << result_3.second << ")" << std::endl;
    auto result_4 = find_missing_4(first, second);
    std::cout << "Found: " << result_4.first << "(" << result_4.second << ")" << std::endl;
    auto result_5 = find_missing_4(first, second);
    std::cout << "Found: " << result_5.first << "(" << result_5.second << ")" << std::endl;


    return 0;
}

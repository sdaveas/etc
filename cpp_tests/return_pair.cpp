#include <iostream>
#include <unordered_map>

std::pair<int, int> get_record(std::unordered_map<int, int>& map, int key)
{
    return *map.find(key);
}

int main()
{
    std::unordered_map<int, int> my_map;

    for (int i=0; i<100; i++) {
        my_map.insert({i,i});
    }

    std::pair<int, int> res = get_record(my_map, 1);
    my_map.erase(1);
    my_map.insert({1, 2});

    std::cout << res.first << " " << res.second << std::endl;
}

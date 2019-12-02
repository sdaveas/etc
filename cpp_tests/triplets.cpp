#include <iostream>
#include <iterator>
#include <vector>

template<typename T = std::string>
void print_vector(const std::vector<char>& vec, T msg = "")
{
    std::cout << msg;
    for (auto c : vec) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

void process_vector(std::vector<char>& vec)
{
    // Print the current state of vector
    print_vector(vec, "-> ");

    bool triplet_exists = false;
    auto it = vec.begin();

    // v: abcdefghijklmnopqrstuvwxyz
    //    ^                         ^
    //    '----v.begin()            '----vec.end()
    while (it!=vec.end()) {
        // Make a new itterator point at the same pos
        auto it_2 = it;
        // Advance the itterator one position ahead for each same character
        do {
            std::advance(it_2, 1);
        } while (it_2 != vec.end() && *it == *it_2);
        // If the advances were over than 3, erase that part
        if (std::distance(it, it_2) >= 3) {
            vec.erase(it, it_2);
            triplet_exists = true;
        }
        // Advance main iterator if not surpassed the vector size
        if (it!=vec.end()) {
            std::advance(it, 1);
        }
    }
    // If triplets were found, call recursively
    if (triplet_exists) {
        return process_vector(vec);
    }
    // Else return
    else {
        return;
    }
}

int main()
{
    std::string input = "bbccaaacb";
    std::vector<char> vec(input.size());
    for (int i=0; i<input.size(); i++) {
        vec[i] = input[i];
    }
    print_vector(vec, "Initial input: ");

    process_vector(vec);

    print_vector(vec, "Final output: ");

    return 0;
}

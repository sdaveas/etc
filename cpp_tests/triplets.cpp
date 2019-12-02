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

// Ugly solution which I am not going to document
// void process_vector(std::vector<char> vec)
// {
//     bool triplet_exists = false;
//     do {
//         std::vector<char> new_vec;
//         triplet_exists = false;
//         for (int i=0; i<vec.size(); i++) {
//             char current = vec[i];
//             int j=1;
//             while (vec[i] == vec[i+j]) {
//                 j++;
//             }
//             if (j >= 3) {
//                 i = i + j - 1;
//                 triplet_exists = true;
//             }
//             else {
//                 new_vec.push_back(vec[i]);
//             }
//         }
//         for (int i=0; i<new_vec.size(); i++) {
//             std::cout << new_vec[i] << " ";
//         }
//         std::cout << std::endl;
//         vec = new_vec;
//      } while(triplet_exists);
// }

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

#include <iostream>
#include <iterator>
#include <vector>

void process_vector(std::vector<char>& vec)
{
    for (auto c:vec) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    bool triplet_exists = false;
    auto it = vec.begin();
    while (it!=vec.end()) {
        auto it_2 = it;
        std::advance(it_2, 1);
            std::advance(it_2, 1);
        }
        } while (it_2 != vec.end() && *it == *it_2);
        if (std::distance(it, it_2) >= 3) {
            vec.erase(it, it_2);
            triplet_exists = true;
        }
        if (it!=vec.end()) {
            std::advance(it, 1);
        }
    }

    if (triplet_exists) {
        return process_vector(vec);
    }
    else {
        return;
    }
}

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
    std::string input = "caabbbac";
    std::cout << "Initial input: " << input << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::vector<char> vec(input.size());
    for (int i=0; i<input.size(); i++) {
        vec[i] = input[i];
    }
    process_vector(vec);

    return 0;
}

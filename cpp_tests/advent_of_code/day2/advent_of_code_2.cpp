#include <iostream>
#include <fstream>
#include <vector>

auto process_input(std::vector<int> vec)
{
    size_t index = 0;
    while(vec[index]!=99) {
        if (vec[index] == 1) {
            vec[vec[index+3]] = vec[vec[index+1]] + vec[vec[index+2]];
        }
        else if(vec[index] == 2) {
            vec[vec[index+3]] = vec[vec[index+1]] * vec[vec[index+2]];
        }
        else {
            std::cerr << "Invalid opcode: " << vec[index] << std::endl;
            return std::vector<int>{};
        }
        index += 4;
    }

    return std::vector<int>{vec.begin(), vec.begin()+3};
}

int main()
{
    size_t size = 149;
    std::vector<int> vec(size);
    std::ifstream f_read{"advent_of_code_2.in"};
    // std::ifstream f_read{"test_1.in"};

    for(int i=0; i<size; i++) {
        f_read >> vec[i];
    }

    size_t noun = 0;
    size_t verb = 0;
    bool increase_noun = true;
    std::vector<int> res(3);

    while(1) {
        vec[1] = noun;
        vec[2] = verb;
        res = process_input(vec);
        if (res[0] == 19690720) {
            break;
        }
        increase_noun ? noun++ : verb++;
        increase_noun = !increase_noun;
    }

    std::cout << 100 * noun + verb << std::endl;

    return 0;
}

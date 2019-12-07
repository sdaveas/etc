#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <unordered_map>


enum op_code_t
{
    add = 1,
    mult = 2,
    input = 3,
    output = 4,
    jumpiftrue=5,
    jumpiffalse=6,
    lessthan=7,
    equals=8,
    halt = 99,
};

enum modes_t
{
    position = 0,
    immediate = 1,
};

std::unordered_map<op_code_t, int> codes_to_offsets
{
    {add, 4},
    {mult, 4},
    {input, 2},
    {output, 2},
    {jumpiftrue, 3},
    {jumpiffalse, 3},
    {lessthan, 4},
    {equals, 4},
    {halt, 0},
};

int parameters_of_opcode(int op)
{
    auto code_to_offset = codes_to_offsets.find(static_cast<op_code_t>(op));
    // std::cout << "Advancing pointer by: " << code_to_offset->second << std::endl;
    return code_to_offset->second;
}

int pow(int value, int base)
{
    if (base ==0) {
        return 1;
    }
    int x = value;
    while(base > 1) {
        x *= value;
        base--;
    }
    return x;
}

auto process_input(std::vector<int>& instrs, int& index, int phase, int signal)
{
    std::vector<int> input{signal};
    if (index == 0) {
        input.push_back(phase);
    }
    int in = 0;
    std::optional<int> out = std::nullopt;
    int count = 0;

    do {
        count++;
        int instr = instrs[index];
        int op_code = instr%pow(10, 2);

        if(op_code == op_code_t::halt) {
            // std::cout << "Received HALD op_code and signal " << signal << std::endl;
            out = std::nullopt;
            break;
        }

        auto params = parameters_of_opcode(op_code) - 1;
        std::vector<int> modes(params);
        std::vector<int> addrs(params);

        for (int i=0; i<addrs.size(); i++) {
            modes[i] = (instr%(pow(10, i+3)))/pow(10, i+2);
            addrs[i] = modes[i] == 0 ? instrs[index+1+i] : index+1+i;
        }

        if (op_code == op_code_t::add) {
            instrs[addrs[2]] = instrs[addrs[0]] + instrs[addrs[1]];
        }
        else if(op_code == op_code_t::mult) {
            instrs[addrs[2]] = instrs[addrs[0]] * instrs[addrs[1]];
        }
        else if(op_code == op_code_t::input) {
            // std::cout << "Input: " << std::endl;
            instrs[addrs[0]] = input.back();
            input.pop_back();
            // std::cin >> instrs[addrs[0]];
        }
        else if(op_code == op_code_t::output) {
            // std::cout << "Output: " << instrs[addrs[0]] << std::endl;
            out = instrs[addrs[0]];
            index+=parameters_of_opcode(op_code);
            // std::cout << "Saving instr pointer at: " << index << " after " << count << std::endl;
            break;
        }
        else if(op_code == op_code_t::jumpiftrue) {
            if (instrs[addrs[0]] != 0) {
                index = instrs[addrs[1]];
                continue;
            }
        }
        else if(op_code == op_code_t::jumpiffalse) {
            if (instrs[addrs[0]] == 0) {
                index = instrs[addrs[1]];
                continue;
            }
        }
        else if(op_code == op_code_t::lessthan) {
            if (instrs[addrs[0]] < instrs[addrs[1]]) {
                instrs[addrs[2]] = 1;
            }
            else {
                instrs[addrs[2]] = 0;
            }
        }
        else if(op_code == op_code_t::equals) {
            if (instrs[addrs[0]] == instrs[addrs[1]]) {
                instrs[addrs[2]] = 1;
            }
            else {
                instrs[addrs[2]] = 0;
            }
        }
        index+=parameters_of_opcode(op_code);

    } while(1);

    return out;
}

int main()
{
    std::vector<int> vec{};
    std::ifstream f_read{"advent_of_code_7.in"};
    // std::ifstream f_read{"test.in"};

    if (!f_read) {
        std::cout << "No such file" << std::endl;
        return -1;
    }

    while(!f_read.eof()) {
        int x;
        f_read >> x;
        vec.push_back(x);
    }

    int signal = 0;
    int max = 0;
    std::vector<int> phases{5, 6, 7, 8, 9};
    std::vector<int> index{0, 0, 0, 0, 0};
    std::vector<std::vector<int>> instrs= {vec, vec, vec, vec, vec};
    int i=0;

    // For all permutations
    do {
        // Until receiving an halt from any amplifier
        i=0;
        while (1) {
            i=i%phases.size();
            auto res = process_input(instrs[i], index[i], phases[i], signal);
            i++;
            if (res == std::nullopt) {
                break;
            }
            signal = res.value();
        }

        // Same max signal
        if (signal > max) {
            max = signal;
        }

        // Reset state
        signal = 0;
        index = {0, 0, 0, 0, 0};
        instrs= {vec, vec, vec, vec, vec};
    } while(std::next_permutation(phases.begin(), phases.end()));

    std::cout << max << std::endl;

    return 0;
}

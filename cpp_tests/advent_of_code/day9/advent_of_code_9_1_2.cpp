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
    update_relative=9,
    halt = 99,
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
    {update_relative, 2},
    {halt, 0},
};

enum modes_t
{
    position = 0,
    immediate = 1,
    relative = 2,
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

auto process_input(std::vector<long long int> instrs)
{
    int index = 0;
    int relative_base = 0;

    do {
        long long int instr = instrs[index];
        int op_code = instr%pow(10, 2);

        if(op_code == op_code_t::halt) {
            std::cout << "Received HALD" << std::endl;
            break;
        }
        auto params = parameters_of_opcode(op_code) - 1;
        std::vector<int> modes(params);
        std::vector<int> addrs(params);

        for (int i=0; i<addrs.size(); i++) {
            modes[i] = (instr%(pow(10, i+3)))/pow(10, i+2);
            if (modes[i] == modes_t::position) {
                addrs[i] = instrs[index+1+i];
            }
            else if (modes[i] == modes_t::immediate) {
                addrs[i] = index+1+i;
            }
            else if (modes[i] == modes_t::relative) {
                int offset = instrs[index+1+i];
                addrs[i] = relative_base+offset;
            }
            if (addrs[i] >= instrs.size()) {
                std::cout << addrs[i] << " is out of size" << std::endl;
            }
        }

        if (op_code == op_code_t::add) {
            instrs[addrs[2]] = instrs[addrs[0]] + instrs[addrs[1]];
        }
        else if(op_code == op_code_t::mult) {
            instrs[addrs[2]] = instrs[addrs[0]] * instrs[addrs[1]];
        }
        else if(op_code == op_code_t::input) {
            std::cout << "Input: " << std::endl;
            std::cin >> instrs[addrs[0]];
        }
        else if(op_code == op_code_t::output) {
            std::cout << "Output: " << instrs[addrs[0]] << std::endl;
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
        else if(op_code == op_code_t::update_relative) {
            relative_base += instrs[addrs[0]];
        }
        else {
            std::cout << "Wrong op_code:" << op_code << std::endl;
            return false;
        }
        index+=parameters_of_opcode(op_code);

    } while(1);

    return true;
}

int main()
{
    std::vector<long long int> vec{};
    std::ifstream f_read{"input.txt"};
    // std::ifstream f_read{"test.in"};

    if (!f_read) {
        std::cout << "No such file" << std::endl;
        return -1;
    }

    while(!f_read.eof()) {
        long long int x;
        f_read >> x;
        vec.push_back(x);
        if (!f_read.eof()) {
            char comma;
            f_read >> comma;
        }
    }
    for (int i=0; i<2029; i++) {
        vec.push_back(0);
    }

    auto res = process_input(vec);

    return 0;
}

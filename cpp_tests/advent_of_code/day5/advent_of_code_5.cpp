#include <iostream>
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
    std::cout << "Advancing pointer by: " << code_to_offset->second << std::endl;
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

void test_instr(int in)
{
    int instr = in;
    int op_code = instr%100;

    if(op_code == op_code_t::halt) {
        std::cerr << "Received HALD op_code: " << std::endl;
        return;
    }

    auto params = parameters_of_opcode(op_code) - 1;
    std::vector<int> modes(params);
    std::vector<int> addrs(params);

    for (int i=0; i<addrs.size(); i++) {
        modes[i] = (instr%(pow(10, i+3)))/pow(10, i+2);
        addrs[i] = modes[i] == 0 ? true : false;
    }

    for (int i=0; i<addrs.size(); i++) {
        std:: cout << modes[i] << std::endl;
        std:: cout << addrs[i] << std::endl;
    }

}

auto process_input(std::vector<int> instrs)
{
    size_t index = 0;
    do {
        int instr = instrs[index];
        int op_code = instr%pow(10, 2);

        if(op_code == op_code_t::halt) {
            std::cerr << "Received HALD op_code: " << std::endl;
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
        index+=parameters_of_opcode(op_code);

    } while(1);

    return true;
}

int main()
{
    size_t size = 678;
    std::vector<int> vec(size);
    std::ifstream f_read{"advent_of_code_5.in"};
    // std::ifstream f_read{"test.in"};

    for(int i=0; i<size; i++) {
        f_read >> vec[i];
    }

    auto res = process_input(vec);
    std::cout << "Done: " << res << std::endl;

    // test_instr(1001);

    return 0;
}

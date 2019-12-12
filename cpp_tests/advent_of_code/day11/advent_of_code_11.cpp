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

enum output_t
{
    fill = 0,
    rotation = 1,
};

enum rotation_t
{
    left = 0,
    right = 1,
};

enum fill_t
{
    empty = 0,
    full = 1,
};

auto process_input(
        std::vector<long long int>& instrs,
        const std::vector<fill_t> input,
        std::vector<int>& output)
{
    static int index = 0;
    static int relative_base = 0;

    do {
        long long int instr = instrs[index];
        int op_code = instr%pow(10, 2);

        if(op_code == op_code_t::halt) {
            std::cout << "Received HALD" << std::endl;
            return false;
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
            // std::cout << "Input: " << std::endl;
            // std::cin >> instrs[addrs[0]];
            instrs[addrs[0]] = input[0];
        }
        else if(op_code == op_code_t::output) {
            // std::cout << "Output: " << instrs[addrs[0]] << std::endl;
            output.push_back(instrs[addrs[0]]);
            if (output.size() == 2) {
                index+=parameters_of_opcode(op_code);
                return true;
            }
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

struct Point
{
    Point(int _x, int _y)
    {
        x=_x;
        y=_y;
    }
    int x;
    int y;

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }

    struct Hasher
    {
        std::size_t operator()(const Point& k) const
        {
            return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
        }
    };
};



void move_robot(Point& prev_pos, Point& curr_pos , rotation_t rotation)
{
    Point new_pos = curr_pos;

    if (prev_pos.x == curr_pos.x) {
        if (prev_pos.y < curr_pos.y) {
            if (rotation == rotation_t::left) {
                new_pos.x += 1;
            }
            else if (rotation == rotation_t::right) {
                new_pos.x -= 1;
            }
        }
        else {
            if (rotation == rotation_t::left) {
                new_pos.x -= 1;
            }
            else if (rotation == rotation_t::right) {
                new_pos.x += 1;
            }
        }
    }
    else {
        if (prev_pos.x < curr_pos.x) {
            if (rotation == rotation_t::left) {
                new_pos.y -= 1;
            }
            else if (rotation == rotation_t::right) {
                new_pos.y += 1;
            }
        }
        else {
            if (rotation == rotation_t::left) {
                new_pos.y += 1;
            }
            else if (rotation == rotation_t::right) {
                new_pos.y -= 1;
            }
        }
    }
    prev_pos = curr_pos;
    curr_pos = new_pos;
}

int main()
{

    std::vector<long long int> vec{};
    std::ifstream f_read{"input"};

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


    for (int i=0; i<1000000; i++) {
        vec.push_back(0);
    }

    Point prev_pos{0, 1};
    Point curr_pos{0, 0};
    std::unordered_map<Point, fill_t, Point::Hasher> panels;
    std::vector<fill_t> input{};

    input.push_back(fill_t::empty);

    int round = 0;
    int skipping = 0;
    while(1) {
        std::vector<int> output{};

        auto res = process_input(vec, input, output);

        if (res == false) {
            break;
        }

        fill_t fill = static_cast<fill_t>(output[output_t::fill]);
        panels.insert({curr_pos, fill});

        rotation_t rotation = static_cast<rotation_t>(output[output_t::rotation]);
        move_robot(prev_pos, curr_pos, rotation);

        fill_t curr_fill = panels.find(curr_pos)==panels.end() ? fill_t::empty : panels.at(curr_pos);
        input = {curr_fill};
        round++;
    }

    printf("rounds %d\n", round);

    printf("size: %d\n", panels.size());

    char p;
    for (int y=0; y<6; y++) {
        for (int x=-42; x<42; x++) {
            if (panels.find(Point(x,y))!=panels.end()) {
                p = panels[Point(x,y)] == fill_t::empty ? '.' : '0';
            }
            else {
                p = ' ';
            }
            printf("%c", p);
        }
        printf("\n");
    }
}

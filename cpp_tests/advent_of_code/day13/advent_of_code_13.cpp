#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>

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
    x = 0,
    y = 1,
    tide_id = 2,
};

enum tide_t
{
    empty = 0,
    wall = 1,
    block = 2,
    paddle = 3,
    ball = 4,
};

enum joystick_t
{
    left = -1,
    still = 0,
    right = 1,
};

auto process_input(
        std::vector<long long int>& instrs,
        int input,
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
            instrs[addrs[0]] = input;
        }
        else if(op_code == op_code_t::output) {
            // std::cout << "Output: " << instrs[addrs[0]] << std::endl;
            output.push_back(instrs[addrs[0]]);
            if (output.size() == 3) {
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
    int x;
    int y;

    Point(int _x, int _y)
        :x(_x), y(_y)
    {}

    bool operator==(const Point& p) const
    {
        return x==p.x && y==p.y;
    }

    struct Hasher
    {
        size_t operator()(const Point& p) const
        {
            return p.x*1000 + p.y;
        }
    };
};

using teren_map_t = std::unordered_map<Point, tide_t, Point::Hasher>;

void print_teren(teren_map_t& teren_map, int min_x, int max_x, int min_y, int max_y, int score)
{
    system ("clear");
    for (int y=min_y; y<=max_y; y++) {
        for (int x=min_x; x<=max_x; x++) {
            tide_t cell = teren_map[Point(x,y)];
            if (cell == empty) {
                printf(" ");
            }
            else if (cell == wall) {
                printf("#");
            }
            else if (cell == block) {
                printf("=");
            }
            else if (cell == paddle) {
                printf("-");
            }
            else if (cell == ball) {
                printf("O");
            }
            else {
                printf("X");
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
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

    teren_map_t teren_map;

    // known from pt1
    int min_x=0;
    int max_x=44;
    int min_y=0;
    int max_y=23;

    // Play for free
    vec[0] = 2;
    int score = 0;

    int ball_x = 44/2;
    int paddle_x = 44/2;

    joystick_t input;

    while (1) {

        std::vector<int> output{};
        auto res = process_input(vec, input, output);
        if (res == false) {
            break;
        }

        if (output[x] == -1 && output[y] == 0) {
            score = output[tide_id];
            print_teren(teren_map, min_x, max_x, min_y, max_y, score);
            std::this_thread::sleep_for(std::chrono::milliseconds{100});
        }
        else {
            if (output[tide_id] == ball) {
                ball_x = output[x];
            }
            else if (output[tide_id] == paddle) {
                paddle_x = output[x];
            }
            if (ball_x < paddle_x) {
                input = left;
            }
            else if (ball_x > paddle_x) {
                input = right;
            }
            else {
                input = still;
            }
        }

        teren_map[Point(output[x], output[y])] = static_cast<tide_t>(output[tide_id]);
    }
}

#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <iostream>
#include <functional>

void fill_matrix(std::vector<std::vector<char>>& matrix,
                 std::vector<std::vector<int>>& steps,
                 const std::vector<char> directions,
                 const std::vector<int> distances,
                 const std::pair<int, int> start_pos,
                 const char mark)
{
    struct {
        int x{0}; int y{0};
    } pos;


    pos.x = start_pos.first;
    pos.y = start_pos.second;

    matrix[pos.y][pos.x] = -1;

    size_t num_of_operations = directions.size() - 1;

    int step = 0;

    for (int i=0; i<num_of_operations; i++) {
        step++;
        // std::cout << "Operation:" << directions[i] << "," << distances[i] << std::endl;
        if (directions[i] == 'U') {
            pos.y--;
            for (int k=1; k<distances[i]; k++) {
                // if (matrix[pos.y][pos.x] == '.') {
                //     matrix[pos.y][pos.x] = '|';
                // }
                // else {
                //     matrix[pos.y][pos.x] = 'X';
                // }
                if (matrix[pos.y][pos.x] != mark) matrix[pos.y][pos.x] += mark;
                steps[pos.y][pos.x]=step++;
                pos.y--;
            }
        }
        if (directions[i] == 'D') {
            pos.y++;
            for (int k=1; k<distances[i]; k++) {
                // if (matrix[pos.y][pos.x] == '.') {
                //     matrix[pos.y][pos.x] = '|';
                // }
                // else {
                //     matrix[pos.y][pos.x] = 'X';
                // }
                if (matrix[pos.y][pos.x] != mark) matrix[pos.y][pos.x] += mark;
                steps[pos.y][pos.x]=step++;
                pos.y++;
            }
        }
        if (directions[i] == 'L') {
            pos.x--;
            for (int k=1; k<distances[i]; k++) {
                // if (matrix[pos.y][pos.x] == '.') {
                //     matrix[pos.y][pos.x] = '_';
                // }
                // else {
                //     matrix[pos.y][pos.x] = 'X';
                // }
                if (matrix[pos.y][pos.x] != mark) matrix[pos.y][pos.x] += mark;
                steps[pos.y][pos.x]=step++;
                pos.x--;
            }
        }
        if (directions[i] == 'R') {
            pos.x++;
            for (int k=1; k<distances[i]; k++) {
                // if (matrix[pos.y][pos.x] == '.') {
                //     matrix[pos.y][pos.x] = '_';
                // }
                // else {
                //     matrix[pos.y][pos.x] = 'X';
                // }
                if (matrix[pos.y][pos.x] != mark) matrix[pos.y][pos.x] += mark;
                steps[pos.y][pos.x]=step++;
                pos.x++;
            }
        }
        matrix[pos.y][pos.x] += mark;
        steps[pos.y][pos.x]=step;
        // std::cout << "Pos: " << pos.x << "," << pos.y << std::endl;
    }

    return;
}

std::tuple<int, int, int, int> find_dims(std::vector<char> directions, std::vector<int> distances)
{
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
    for (int i=0; i<distances.size(); i++) {
        if (directions[i] == 'U') {
            up += distances[i];
            continue;
        }
        if (directions[i] == 'D') {
            down += distances[i];
            continue;
        }
        if (directions[i] == 'L') {
            left += distances[i];
            continue;
        }
        if (directions[i] == 'R') {
            right+=distances[i];
            continue;
        }
    }

    return {up, down, left, right};
}

int main()
{
    enum dirs {
        up = 0,
        down = 1,
        left = 2,
        right = 3
    };

    // cable 1
    std::ifstream cable_1{"test_1"};
    std::vector<char> directions_1{};
    std::vector<int> distances_1{};
    while(!cable_1.eof()) {
        std::string operation;
        cable_1 >> operation;
        directions_1.push_back(operation[0]);
        distances_1.push_back(atoi(&operation[1]));
    }
    std::cout << std::endl;

    // cable 2
    std::ifstream cable_2{"test_2"};
    std::vector<char> directions_2{};
    std::vector<int> distances_2{};
    while(!cable_2.eof()) {
        std::string operation;
        cable_2 >> operation;
        directions_2.push_back(operation[0]);
        distances_2.push_back(atoi(&operation[1]));
    }
    std::cout << std::endl;

    auto dims_1 = find_dims(directions_1, distances_1);
    auto dims_2 = find_dims(directions_2, distances_2);

    auto max_up = std::get<dirs::up>(dims_1) > std::get<dirs::up>(dims_2) ?
                std::get<dirs::up>(dims_1):
                std::get<dirs::up>(dims_2);
    auto max_down = std::get<dirs::down>(dims_1) > std::get<dirs::down>(dims_2) ?
                std::get<dirs::down>(dims_1):
                std::get<dirs::down>(dims_2);
    auto max_left = std::get<dirs::left>(dims_1) > std::get<dirs::left>(dims_2) ?
                std::get<dirs::left>(dims_1):
                std::get<dirs::left>(dims_2);
    auto max_right = std::get<dirs::right>(dims_1) > std::get<dirs::right>(dims_2) ?
                std::get<dirs::right>(dims_1):
                std::get<dirs::right>(dims_2);

    //TODO: why is this +3 needed??
    int x_length = max_up+max_down;
    int y_length = max_left+max_right+1;

    std::cout <<
        "max up: " << max_up << "\n"
        "max down: " << max_down << "\n"
        "max left: " << max_left << "\n"
        "max right: " << max_right << "\n"
        "x_length:" << x_length << "\n"
        "y_length:" << y_length << std::endl;


    std::vector<std::vector<char>> matrix;
    for (int i=0; i<x_length; i++) {
        matrix.push_back(std::vector<char>(y_length));
        for (int j=0; j<y_length; j++) {
            matrix[i][j] = 0;
        }
    }

    std::vector<std::vector<int>> steps_1;
    std::vector<std::vector<int>> steps_2;
    for (int i=0; i<x_length; i++) {
        steps_1.push_back(std::vector<int>(y_length));
        steps_2.push_back(std::vector<int>(y_length));
        for (int j=0; j<y_length; j++) {
            steps_1[i][j] = 0;
            steps_2[i][j] = 0;
        }
    }

    std::pair<int, int> origin = {max_left, max_up};
    // std::pair<int, int> origin = {x_length/2, y_length/2};

    fill_matrix(matrix, steps_1, directions_1, distances_1, origin, 1);
    fill_matrix(matrix, steps_2, directions_2, distances_2, origin, 2);

    std::vector<int> manhattan_distances{};
    std::vector<int> steps{};

    printf("  ");
    for (int i=0; i<y_length; i++) {
        printf(" %2d", i);
    }
    std::cout << std::endl;
    for (int i=0; i<y_length; i++) {
        printf("%2d", i);
        for (int j=0; j<x_length; j++) {
            if (matrix[j][i] == 0) printf("   ");
            else if (matrix[j][i] == -1) printf("  O");
            else if (matrix[j][i] == 1) printf("  *");
            else if (matrix[j][i] == 2) printf("  o");
            else {
                printf("  x");
            }
            // if (matrix[i][j] == 3) {
            //     printf("  %2d, %2d", steps_1[i][j], steps_2[i][j]);
            // }
        }
        std::cout << std::endl;
    }

    for (int i=0; i<x_length; i++) {
        for (int j=0; j<y_length; j++) {
            if (matrix[i][j] == 3) {
                manhattan_distances.push_back(abs(max_left - j) + abs(max_up - i));
                steps.push_back(steps_1[i][j] + steps_2[i][j]);
            }
        }
    }

    int min_distance = x_length*y_length;
    for (auto i:manhattan_distances) {
        if (i < min_distance) {
            min_distance = i;
        }
    }
    std::cout << "Minimum distance: " << min_distance << std::endl;

    int min_steps = 2*x_length*y_length;
    for (auto i:steps) {
        if (i < min_steps) {
            min_steps = i;
        }
    }
    std::cout << "Minimum steps: " << min_steps << std::endl;

    return 0;
}

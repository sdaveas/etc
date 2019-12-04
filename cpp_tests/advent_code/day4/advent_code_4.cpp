#include <iostream>
#include <vector>
#include <unordered_map>

int start = 356261;
int end = 846303;
int counter = 0;

std::unordered_map<int, int> appearances{};

bool in_limits(int candidate)
{
    return (start<= candidate && candidate <= end);
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

void find_adjacent_numbers(int d1, int d2,int d3,int d4,int d5)
{
    std::vector<int> digits{d1,d2,d3,d4,d5};
    int candidate = 0;

    // TODO: lose the code dublication
    // for (int i=0; i<digits.size(); i++) {
    //     candidate += digits[i] * pow(10, i);
    // }

    if (d1 != d2) {
        candidate = d1*100000 + d1*10000 + d2*1000 + d3*100 + d4*10 + d5;
        if (in_limits(candidate)) {
            appearances.insert({candidate, 1});
        }
    }

    if (d1!= d2 && d2 != d3) {
        candidate = d1*100000 + d2*10000 + d2*1000 + d3*100 + d4*10 + d5;
        if (in_limits(candidate)) {
            appearances.insert({candidate, 1});
        }
    }

    if (d2!=d3 && d3 != d4) {
        candidate = d1*100000 + d2*10000 + d3*1000 + d3*100 + d4*10 + d5;
        if (in_limits(candidate)) {
            appearances.insert({candidate, 1});
        }
    }

    if (d3 != d4 && d4 != d5) {
        candidate = d1*100000 + d2*10000 + d3*1000 + d4*100 + d4*10 + d5;
        if (in_limits(candidate)) {
            appearances.insert({candidate, 1});
        }
    }

    if (d4 != d5) {
        candidate = d1*100000 + d2*10000 + d3*1000 + d4*100 + d5*10 + d5;
        if (in_limits(candidate)) {
            appearances.insert({candidate, 1});
        }
    }

}
int main()
{
    int start_digit= 3;
    int end_digit = 9 + 1;

    for(int d1=start_digit; d1<end_digit; d1++) {
        for(int d2=d1; d2<end_digit; d2++) {
            for(int d3=d2; d3<end_digit; d3++) {
                for(int d4=d3; d4<end_digit; d4++) {
                    for(int d5=d4; d5<end_digit; d5++) {
                        find_adjacent_numbers(d1, d2, d3, d4, d5);
                    }
                }
            }
        }
    }

    for (auto a: appearances) {
        std::cout << a.first << std::endl;
    }
    std::cout << appearances.size() << std::endl;
}

#include <iostream>
#include <string>

void test1();  // see file test1.cpp
void test2();  // see file test2.cpp
void test3();  // see file test3.cpp

void exercise3();  // see file frequency_table.cpp

int main() {
    std::cout << "Start batch of tests 1 ...\n";
    std::cout << std::string(30, '=') << "\n";
    test1();  // get_parent

    std::cout << "\nStart batch of tests 2 ...\n";
    std::cout << std::string(30, '=') << "\n";
    test2();  // find_pred_succ

    std::cout << "\nStart batch of tests 3 ...\n";
    std::cout << std::string(30, '=') << "\n";
    test3();  // Iterator class

    std::cout << "\nExercise 3 ...\n";
    std::cout << std::string(30, '=') << "\n";
    exercise3();
}

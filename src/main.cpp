#include <iostream>
#include <string>
#include <cstdlib>
#include "solve_tree.h"


int main() {
    SolveTree solving_tree;
    std::string filename, object_name1, object_name2;
    char mode = 0;
    while (true) {
        std::cout << CHOOSE_MSG;
        std::cin >> mode;
        std::cin.ignore();
        switch (mode) {
            case 'G':
                solving_tree.guess();
                break;
            case 'Q':
                return 0;
            case 'S':
                std::cout << FILE_OUTPUT_MSG;
                getline(std::cin, filename);
                solving_tree.save(filename.c_str());
                break;
            case 'E':
                std::cout << FILE_INPUT_MSG;
                getline(std::cin, filename);
                solving_tree.load(filename.c_str());
                break;
            case 'P':
                std::cout << FILE_OUTPUT_MSG;
                getline(std::cin, filename);
                solving_tree.print(filename.c_str());
                std::cout << IMG_FILE_MSG;
                getline(std::cin, object_name1);
                object_name1 = "dot -Tsvg -o " + object_name1 + " " + filename;
                system(object_name1.c_str());
                break;
            case 'D':
                getline(std::cin, object_name1);
                solving_tree.get_definition(object_name1.c_str());
                break;
            case 'C':
                INPUT_Kth("first");
                getline(std::cin, object_name1);
                INPUT_Kth("second");
                getline(std::cin, object_name2);
                solving_tree.get_common(object_name1.c_str(), object_name2.c_str());
                break;
            case '-':
                INPUT_Kth("first");
                getline(std::cin, object_name1);
                INPUT_Kth("second");
                getline(std::cin, object_name2);
                solving_tree.get_difference(object_name1.c_str(), object_name2.c_str());
                break;
            default:
                std::cout << NO_COMMAND;
                break;
        }
    }
    return 0;
}

#pragma once
#ifndef CONSTANTS
#define CONSTANTS

#define CHOOSE_MSG         "Choose working mode: [G]uess, [P]rint, [S]ave, [E]xport, [D]efinition, [C]ommon, [-]Difference, [Q]uit.\n"
#define FILE_INPUT_MSG     "Input file name: "
#define FILE_OUTPUT_MSG    "Output file name: "
#define IMG_FILE_MSG       "Image file name: "
#define NULL_NODE          "undefined"
#define CONFIRM_MSG        "\n[Y]es/[N]o\n"
#define UNSURE_CONFIRM_MSG "\n[Y]es/[N]o/[P]robably [Y]es/[P]robably [N]o\n"
#define NO_NODE_MSG        "I don't know what it is.\n"
#define CORRECT_ANS_MSG    "It was easy.\n"
#define LEARN_MSG          "I will remember this.\n"
#define GET_OBJ_MSG        "What did you think about?\n"
#define NO_COMMAND         "I don't know this command. Use the list above.\n"

#define GET_FEATURE_MSG(obj)  std::cout << "What is unique about " << obj << "?\n" << "It is ... "
#define PROBABLE_ANS_MSG(obj) std::cout << "I think it is " << obj << "." << CONFIRM_MSG;
#define GET_DIFF_MSG(obj1, obj2) std::cout << "How is " << obj1 << " different from " << obj2 << "?\n" << "It is ... "
#define INPUT_Kth(Kth) std::cout << "Input " Kth " object name:\n"

#endif
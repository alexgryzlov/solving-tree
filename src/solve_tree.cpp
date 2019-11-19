#include "solve_tree.h"

void SolveTree::get_common(const char *obj1, const char *obj2) {
    update_tree();
    std::stack<std::string> chars;
    DFS_definition(root, LCA(DFS_num(root, obj1), DFS_num(root, obj2)), chars);
    if (!chars.empty() && chars.top() == "FOUND") {
        chars.pop();
        if (chars.empty()) {
            std::cout << "NOT FOUND" << std::endl;
            return;
        }
        std::cout << "They both ";
        while (!chars.empty()) {
            std::cout << chars.top() << ' ';
            chars.pop();
        }
        std::cout << std::endl;
    }
}


SolveTree::SolveTree() : root(nullptr),
                         _size(1),
                         max_log(0),
                         preproc_data(nullptr),
                         in(nullptr),
                         out(nullptr),
unsure_answers(get_var_name(unsure_answers)) {
    root = new Node(NULL_NODE);
}

SolveTree::~SolveTree() {
    delete_node(root);
    clear();
}

void SolveTree::guess() {
    Node *current_node = root;
    std::string current_answer;

    while (current_node->children[0] && current_node->children[1] || !unsure_answers.empty()) {
        get_ans(current_node);
        if (!current_node->children[0] && !current_node->children[1]) {
            if (current_node->data == NULL_NODE) {
                check_unsure(current_node);
            }
            else {
                PROBABLE_ANS_MSG(current_node->data);
                std::getline(std::cin, current_answer);
                if (current_answer == "Y") {
                    std::cout << CORRECT_ANS_MSG;
                    return;
                } else {
                    if (unsure_answers.empty()) {
                        clear();
                        input_new_node(current_node);
                        update_tree();
                        std::cout << LEARN_MSG;
                        return;
                    }
                    check_unsure(current_node);
                }
            }
        }
    }
    if (current_node->data == NULL_NODE) {
        std::cout << NO_NODE_MSG;
    }
    else {
        PROBABLE_ANS_MSG(current_node->data);
        std::getline(std::cin, current_answer);
        if (current_answer == "Y") {
            std::cout << CORRECT_ANS_MSG;
            return;
        }
    }

    clear();
    input_new_node(current_node);
    update_tree();
    std::cout << LEARN_MSG;
}

void SolveTree::check_unsure(Node*& current_node) {
    if (!unsure_answers.empty()) {
        current_node = unsure_answers.top().node->children[(unsure_answers.top().child + 1) % 2];
        unsure_answers.pop();
    }
}

void SolveTree::get_ans(Node*& current_node) {
    std::string current_answer;
    while (current_node->children[0] && current_node->children[1]) {
        std::cout << current_node->data << "?" << UNSURE_CONFIRM_MSG;
        std::getline(std::cin, current_answer);
        if (current_answer == "Y"){
            current_node = current_node->children[0];
        }
        else if (current_answer == "N") {
            current_node = current_node->children[1];
        }
        else if (current_answer == "PY") {
            unsure_answers.push({current_node, 0});
            current_node = current_node->children[0];
        }
        else if (current_answer == "PN") {
            unsure_answers.push({current_node, 1});
            current_node = current_node->children[1];
        }
    }
}

void SolveTree::save(const char* output_file) {
    FILE* output = fopen(output_file, "w");
    write_node(root, output, 1);
    fclose(output);
}

void SolveTree::load(const char* input_file) {
    char* text = nullptr;
    db_file = input_file;
    string_view* separated_text = nullptr;
    int current_side = 0;
    Node* current_node = root;
    Stack<NodeInfo> node_stack(get_var_name(node_stack));
    int SIZE = read_input(input_file, text);
    int line_count = separate_by_quotes(text, SIZE, separated_text);
    _size = 1;
    node_stack.push({current_node, 0});
    current_node->data = std::string(separated_text[1].ptr, separated_text[1].len);
    for (int i = 2; i < line_count - 1; ++i) {
        if (*separated_text[i].ptr == '{') {
            current_node = new Node;
            _size++;
            ++i;
            current_node->data = std::string(separated_text[i].ptr, separated_text[i].len);
            node_stack.top().node->children[node_stack.top().child] = current_node;
            node_stack.top().child++;
            node_stack.push({current_node, 0});
        }
        if (*separated_text[i].ptr == '}') {
            node_stack.pop();
        }
    }
}

void SolveTree::print(const char* file_name) {
    update_tree();
    FILE* dot_output = fopen(file_name, "w");
    fprintf(dot_output, "digraph G {\n");
    DFS_print(root, dot_output);
    DFS_create_edges(root, dot_output);
    fprintf(dot_output, "}\n");
    fclose(dot_output);
}

void SolveTree::get_definition(const char *object) {
    std::stack<std::string> chars;
    auto obj_str = std::string(object);
    DFS_definition(root, obj_str, chars);
    if (!chars.empty() && chars.top() == "FOUND") {
        chars.pop();
        while (!chars.empty()) {
            std::cout << chars.top() << std::endl;
            chars.pop();
        }
    } else {
        std::cout << "NOT FOUND" << std::endl;
    }
}

void SolveTree::get_definition(int node_num) {
    std::stack<std::string> chars;
    DFS_definition(root, node_num, chars);
    if (!chars.empty() && chars.top() == "FOUND") {
        chars.pop();
        while (!chars.empty()) {
            std::cout << chars.top() << std::endl;
            chars.pop();
        }
    } else {
        std::cout << "NOT FOUND" << std::endl;
    }
}

void SolveTree::get_difference(const char *obj1, const char *obj2) {
    update_tree();
    std::stack<std::string> chars;
    int common = LCA(DFS_num(root, obj1), DFS_num(root, obj2));
    Node* common_node = DFS_node(root, common);
    auto obj_str = std::string(obj1);
    DFS_definition(common_node, obj_str, chars);
    if (!chars.empty() && chars.top() == "FOUND") {
        chars.pop();
        if (chars.empty()) {
            std::cout << "NOT FOUND" << std::endl;
            return;
        }
        std::cout << "First object is ";
        while (!chars.empty()) {
            std::cout << chars.top() << ' ';
            chars.pop();
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    obj_str = std::string(obj2);
    DFS_definition(common_node, obj_str, chars);
    if (!chars.empty() && chars.top() == "FOUND") {
        chars.pop();
        if (chars.empty()) {
            std::cout << "NOT FOUND" << std::endl;
            return;
        }
        std::cout << "Second object is ";
        while (!chars.empty()) {
            std::cout << chars.top() << ' ';
            chars.pop();
        }
        std::cout << std::endl;
    }
}



// Private methods
int SolveTree::LCA(int node1, int node2) {
    if (upper(node1, node2)) {
        return node1;
    }
    if (upper(node1, node2)){
        return node2;
    }
    for (int i=max_log; i>=0; --i)
        if (!upper (preproc_data[node1][i], node2)) {
            node1 = preproc_data[node1][i];
        }
    return preproc_data[node1][0];
}

void SolveTree::input_new_node(SolveTree::Node*& to) {
    std::string new_object, new_question, tmp;
    std::cout << GET_OBJ_MSG;
    std::getline(std::cin, new_object);
    if (to->data == NULL_NODE) {
        GET_FEATURE_MSG(new_object);
    }
    else {
        GET_DIFF_MSG(new_object,to->data);
    }
    std::getline(std::cin, new_question);
    int new_beginning = 0;
    while (strncasecmp(new_question.c_str() + new_beginning, "not", 3) == 0) {
        new_beginning += 4;
    }
    new_question = new_question.substr(new_beginning);

    tmp = to->data;
    to->data = new_question;
    Node *new_obj_node = new Node(new_object);
    Node *old_obj_node = new Node(tmp);
    _size += 2;
    if ((new_beginning / 4) % 2 == 0) {
        to->children[0] = new_obj_node;
        to->children[1] = old_obj_node;
    } else {
        to->children[1] = new_obj_node;
        to->children[0] = old_obj_node;
    }
}

void SolveTree::update_tree() {
    if (!db_file.empty()) {
        save(db_file.c_str());
    }
    cnt = 0;
    timer = 0;
    max_log = static_cast<long long>(ceil(log2(_size)));
    preprocess_alloc();
    DFS_preproc(root, 0);
}

void SolveTree::preprocess_alloc() {
    preproc_data = (int**)calloc(_size, sizeof(int*));
    for (int i = 0; i < _size; ++i) {
        preproc_data[i] = (int*)calloc(max_log + 1, sizeof(int));
    }
    in = (int*)calloc(_size, sizeof(int));
    out = (int*)calloc(_size, sizeof(int));
}

bool SolveTree::upper(Node* node1, Node* node2) {
    return in[node1->num] <= in[node2->num] && out[node1->num] >= out[node2->num];
}

bool SolveTree::upper(int node1, int node2) {
    return in[node1] <= in[node2] && out[node1] >= out[node2];
}

void SolveTree::clear() {
    if (preproc_data) {
        for (int i = 0; i < _size; ++i) {
            if (preproc_data[i]) {
                free(preproc_data[i]);
            }
        }
        free(preproc_data);
    }
    if (in) {
        free(in);
    }
    if (out) {
        free(out);
    }
}


// Different DFS's for various purposes
int SolveTree::DFS_num(Node* node, const char* data) {
    if (!node) {
        return -1;
    }
    if (node->data == data) {
        return node->num;
    }
    for (int i = 0; i < 2; ++i) {
        int result = DFS_num(node->children[i],data);
        if (result != -1) {
            return result;
        }
    }
    return -1;
}

SolveTree::Node* SolveTree::DFS_node(Node* node, int node_num) {
    if (!node) {
        return nullptr;
    }
    if (node->num == node_num) {
        return node;
    }
    for (int i = 0; i < 2; ++i) {
        Node* result = DFS_node(node->children[i], node_num);
        if (result != nullptr) {
            return result;
        }
    }
    return nullptr;
}

void SolveTree::DFS_definition(Node* node, std::string& object, std::stack<std::string>& chars) {
    if (!node) {
        return;
    }
    if (!chars.empty() && chars.top() == "FOUND") {
        return;
    }
    if (node->data == object) {
        chars.push("FOUND");
        return;
    }
    for (int i = 0; i < 2; ++i) {
        if (i == 0) {
            chars.push(node->data);
        }
        if (i == 1) {
            chars.push("Not " + node->data);
        }
        DFS_definition(node->children[i], object, chars);
        if (!chars.empty() && chars.top() == "FOUND") {
            return;
        }
        chars.pop();
    }
}

void SolveTree::DFS_definition(Node* node, int node_num, std::stack<std::string>& chars) {
    if (!node) {
        return;
    }
    if (!chars.empty() && chars.top() == "FOUND") {
        return;
    }
    if (node->num == node_num) {
        chars.push("FOUND");
        return;
    }
    for (int i = 0; i < 2; ++i) {
        if (i == 0) {
            chars.push(node->data);
        }
        if (i == 1) {
            chars.push("not " + node->data);
        }
        DFS_definition(node->children[i], node_num, chars);
        if (!chars.empty() && chars.top() == "FOUND") {
            return;
        }
        chars.pop();
    }
}

void SolveTree::DFS_print(Node* node, FILE* file) {
    if (!node) {
        return;
    }
    fprintf(file, "\tNode%d [label=\"%s, %d\"]\n", node->num, node->data.c_str(), node->num);
    for (int i = 0; i < 2; ++i) {
        DFS_print(node->children[i], file);
    }
}

void SolveTree::DFS_create_edges(Node* node, FILE* file) {
    if (!node->children[0] && !node->children[1]) {
        return;
    }
    fprintf(file, "\tNode%d -> Node%d [label=\"No\"]\n", node->num, node->children[1]->num);
    fprintf(file, "\tNode%d -> Node%d [label=\"Yes\"]\n", node->num, node->children[0]->num);
    DFS_create_edges(node->children[0], file);
    DFS_create_edges(node->children[1], file);
}

void SolveTree::DFS_preproc(SolveTree::Node *node, int p){
    if (!node) {
        return;
    }
    node->num = cnt++;
    in[node->num] = timer++;
    preproc_data[node->num][0] = p;
    for (int i=1; i <= max_log; ++i)
        preproc_data[node->num][i] = preproc_data[preproc_data[node->num][i-1]][i-1];
    for (int i = 0; i < 2; ++i) {
        DFS_preproc(node->children[i], node->num);
    }
    out[node->num] = timer++;
}

void SolveTree::write_node(Node* node, FILE*& output, int offset) {
    if (!node) {
        return;
    }
    std::string printf_format_string = std::string(offset - 1, '\t') + "{\n" + std::string(offset, '\t') + "\"%s\"\n";
    std::string printf_format_string1 = std::string(offset - 1, '\t') + "}\n";
    fprintf(output, printf_format_string.c_str(), node->data.c_str());
    write_node(node->children[0], output, offset + 1);
    write_node(node->children[1], output, offset + 1);
    fprintf(output, "%s", printf_format_string1.c_str());
}

void SolveTree::delete_node(Node* node) {
    if (!node) {
        return;
    }
    delete_node(node->children[0]);
    delete_node(node->children[1]);
    delete node;
}

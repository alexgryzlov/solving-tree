#pragma once

#include <cmath>
#include <stack>


#include "text_proc.h"
#include "SafeStackOnePlace.hpp"

#include "constants.h"


class SolveTree {
public:
    SolveTree();
    ~SolveTree();

    void guess();                               // If tree changes after unsuccessful guess, we need to rewrite db

    void save(const char* output_file);         // Save tree structure in text file in such format that:
    //
    // root_node----> right_node         root_node->data
    // |                                 {
    // |                            = >     right_node->data
    // |                                 }
    // -------------> left_node          {
    //                                      left_node->data
    //                                   }


    void load(const char* input_file);          //! \brief Load tree from given file written in the format mentioned before

    void print(const char* file_name);          //! \brief Create config file for graphviz

    void get_definition(const char* object);    //! \brief Get all features of the given object

    void get_definition(int node_num);          //! \brief Same but node number instead of the string

    void get_common(const char* obj1,
                    const char* obj2);          //! \brief Get all common features of the two given objects

    void get_difference(const char* obj1,       //! \brief Get difference of two given objects
                        const char* obj2);

    size_t size() { return _size; }

private:
    struct Node {
        Node* children[2]; // LEFT - YES, RIGHT - NO
        std::string data;
        int num;

        Node() : data(), num(-1) { children[0] = nullptr; children[1] = nullptr; }
        Node(const std::string& data) : data(data), num(-1) { children[0] = nullptr; children[1] = nullptr; }
    };

    //! \brief Structure used in the load function to determine which child is currently being processed
    struct NodeInfo {
        Node* node;
        int   child;
    };

    void get_ans(Node*& current_node);
    //! \brief Get new node data from stdin and insert it into the tree
    void input_new_node(Node*& to);

    //! \brief Check another child if answer was unsure
    void check_unsure(Node*& current_node);

    //! \brief Clear used memory
    void delete_node(Node* node);
    void clear();

    //! \brief Recursive function to save node data in the output file
    void write_node(Node* node, FILE*& output, int offset);

    //! \brief Function to update initial database and LCA preprocessed data
    void update_tree();

    //! \brief Function to count in and out values for each node and also compute preprocess data for LCA
    void DFS_preproc(Node* node, int p);

    //! \brief Function to create node definitions in graphviz config file
    void DFS_print(Node* node, FILE* file);

    //! \brief Function to create edges in graphviz config file
    void DFS_create_edges(Node* node, FILE* file);

    //! \brief Functions to get node definition from its data or number
    void DFS_definition(Node* node, std::string& object, std::stack<std::string>& chars);
    void DFS_definition(Node* node, int node_num, std::stack<std::string>& chars);

    //! \brief Function to get node number from its data
    int  DFS_num(Node* node, const char* data);

    //! \brief Function to get node ptr from its number
    Node* DFS_node(Node* node, int node_num);

    //! \brief Function to allocate needed memory before starting preprocessing
    void preprocess_alloc();

    //! \brief Function return true if node1 is ancestor of node2
    bool upper(Node* node1, Node* node2);
    bool upper(int node1, int node2);

    //! \brief Get number of LCA node of two given node numbers
    int LCA(int node1, int node2);


    Node*       root;
    int         cnt;                //! > Counter to enumerate all vertices
    int         timer;              //! > Timer to get in and out values for every node
    size_t      _size;
    long long   max_log;            //! >  Save logarithm so we don't recompute it many times
    int**       preproc_data;       //! >  Data for LCA. preproc_data is a matrix (_size) x ([log2(_size)] + 1)
                                    //! >  preproc[i][j] stores 2 ^ j ancestor number of node with number i
    int*        in;
    int*        out;

    Stack<NodeInfo> unsure_answers;
    std::string db_file;
};

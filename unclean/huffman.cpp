#include "data.h"
#include "huffman.h"
#include <deque>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

HuffmanTable::HuffmanTable(char letter, string str) {
    this->letter = letter;
    code = str;
}

ofstream& operator<<(ofstream& fout, HuffmanTable tab) {
    fout << tab.letter << " " << tab.code << endl;
    return fout;
}

HuffmanTree::HuffmanTree() {
    root = NULL;
}

HuffmanTree::HuffmanTree(Node *node) {
    root = node;
}

Queue HuffmanTree::buildQueue(char *arg) {
    ifstream fin;
    fin.open(arg);
    Queue queue;
    char next;
    while (fin.get(next)) {
        queue.addNode(next);
    }
    fin.close();
    queue.sort();
    return queue;
}

void HuffmanTree::build(char *arg) {
    Queue queue = buildQueue(arg);
    
    deque<Node *> node_queue;
    for (int i = 0; i < queue.getSize(); i++) {
        node_queue.push_back(queue[i]);
    }

    Node *node;
    while(!node_queue.empty()){
        Node *left = node_queue.front();
        node_queue.pop_front();
        Node *right = node_queue.front();
        node_queue.pop_front();
        node = new Node(new DataClass('#', left->data->freq+right->data->freq), left, right);
        if(!node_queue.empty()){
            node_queue.push_back(node);
            int cnt = node_queue.size() - 1;
            while ((node_queue[cnt]->data->freq <= node_queue[cnt-1]->data->freq) && (cnt > 0)){
                swap(node_queue[cnt], node_queue[cnt-1]);
                cnt--;
            }
        }
    }
    root = node;
    buildTable();
}

HuffmanTree::~HuffmanTree() {
    delete[] root;
}

void HuffmanTree::write(char* in, char* out) {
    ofstream fout;
    ifstream fin;
    fin.open(in);
    fout.open(out);
    string line;
    for (int i = 0; i < table.size(); i++) {
        fout << table[i];
    }
    fout << "/\n";
    while (fin >> line) {
        string encline;
        for (int i = 0; i < line.length();i++) {
            for (int j = 0; j < table.size();j++) {
                if (line[i] == table[j].letter) {
                    encline += table[j].code;
                }
            }
        }
        fout << encline << endl;
    }
}

void HuffmanTree::read(char *in, char *out) {
    ifstream fin;
    fin.open(in);
    root = new Node(new DataClass());
    Node *cur;
    char next;
    string code;
    char letter;
    while (fin >> letter) {
        if (letter == '/') {break;}
        fin >> code;
        Node *node;
        node = new Node(new DataClass(letter));
        cur = root;
        for (int i = 0;i < code.length();i++) {
            next = code[i];
            Node *empty = new Node(new DataClass());
            if (i == code.length()-1) {empty = node;}
            if (next == '1') {
                if (cur->left == NULL) {cur->left = empty;}
                cur = cur->left;
            }else if (next == '0'){
                if (cur->right == NULL) {cur->right = empty;}
                cur = cur->right;
            }
        }
    }

    ofstream fout;
    fout.open(out);
    int it = 0;
    string line;
    while (fin >> line) {
        string encline;
        cur = root;
        Node *node;
        for (int i = 0;i < line.length();i++) {
            if (line[i] == '1') {cur = cur->left;}
            else if (line[i] == '0') {cur = cur->right;}
            if (cur->data->letter != '#') {
                encline += cur->data->letter;
                cur = root;
            }
        }
        if (it != 0) {fout << endl;}
        fout << encline;
        it++;
    }
    fin.close();
    fout.close();
}

void HuffmanTree::buildTable() {
    string str;
    buildTableRecur(root, str);
}

void HuffmanTree::buildTableRecur(Node *node, string str)
{
    if (!node) {return;}
    if (node->data->letter != '#'){
        table.push_back(HuffmanTable(node->data->letter, str));
    }
    buildTableRecur(node->left, str + "1");
    buildTableRecur(node->right, str + "0");
}

// void HuffmanTree::buildFromTable() {
//     ifstream fin;
//     fin.open("table.txt");
//     string code;
//     char letter;
//     while (true) {
//         fin >> letter >> code;
//         if (letter == '/') {break;}
//         table.push_back(HuffmanTable(letter, code));
//     }
//     fin.close();

//     fin.open("table.txt");
//     root = new Node(new DataClass());
//     Node *cur;
//     char next;
//     string line;
//     while (fin >> line) {
//         cur = root;
//         Node *node;
//         for (int i = 0;i < line.length();i++) {
//             next = line[i];
//             if (isalpha(next) || next == '_') {
//                 node = new Node(new DataClass(next));
//             }     
//             else if (isnumber(next)) {
//                 Node *empty = new Node(new DataClass());
//                 if (i == line.length()-1) {empty = node;}
//                 if (next == '1') {
//                     if (cur->left == NULL) {cur->left = empty;}
//                     cur = cur->left;
//                 }else if (next == '0'){
//                     if (cur->right == NULL) {cur->right = empty;}
//                     cur = cur->right;
//                 }
//             } 
//         }
//     }
//     fin.close();
// }

// void HuffmanTree::print() {
//     printInorder(root);
// }

// void HuffmanTree::printInorder(Node *node) {
//     if (node == NULL){return;}
//     if (node->data->letter != '#') {cout << node;}
//     printInorder(node->left);
//     printInorder(node->right);
// }
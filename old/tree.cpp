#include <iostream>
#include "huffman.h"
#include <stdio.h>
#include <ctype.h>
#include <deque>
using namespace std;

DataClass::DataClass(char letter){
    this->freq = 1;
    this->letter = letter;
}
DataClass::DataClass(char letter, int freq){
    this->freq = freq;
    this->letter = letter;
}


ostream& operator<<(ostream &fout, DataClass *data){
    cout << data->letter << ": " << data->freq << endl;
    return fout;
}


Node::Node(DataClass *data, Node *left, Node *right){
    this->data = data;
    this->left = left;
    this->right = right;
}

ostream& operator<<(ostream &fout, Node node) {
    cout << node.data;
    return fout;
}

Queue::Queue(){
    capacity = 2;
    size = 0;
    nodes = new Node[capacity];
}

Queue::~Queue(){}

void Queue::addNode(char letter) {
    if ((isalpha(letter) || isdigit(letter) || letter == '_') && !iscntrl(letter)) {
        if (size == capacity) {resize();}
        bool flag = true;
        for (int i = 0; i < size; i++) {
            if (nodes[i].data->letter == letter) {
                nodes[i].data->freq++;
                flag = false;
                break;
            }
        }
        if (flag) {
            nodes[size] = Node(new DataClass(letter));
            size++;
        }
    }
}

Node Queue::operator[](int idx) {
    return nodes[idx];
}

void Queue::resize() {
    Node *tmp_arr = new Node[capacity * 2];
    for(int i = 0; i < size; i++){
        tmp_arr[i] = nodes[i];
    }
    delete[] nodes;
    nodes = tmp_arr;
    capacity *= 2;
}

ostream& operator<<(ostream &fout, Queue &que){
    for (int i = 0; i < que.size; i++) {
        cout << que[i];
    }
    return fout;
}

void Queue::sort()
{
    int i, j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size - i - 1; j++) {
            if (nodes[j].data->freq > nodes[j+1].data->freq) {
                Node temp = nodes[j];
                nodes[j] = nodes[j+1];
                nodes[j+1] = temp;
            }
        }
    }
}

int Queue::getSize() {
    return size;
}

HuffmanTree::HuffmanTree() {
    root = NULL;
}

HuffmanTree::HuffmanTree(Node *node) {
    root = node;
}

void HuffmanTree::build(Queue que) {
    deque<Node *> node_queue;
    for (int i = 0; i < que.getSize(); i++) {
        node_queue.push_back(new Node(que[i]));
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
}

void HuffmanTree::print() {
    printInorder(root);
}

void HuffmanTree::printInorder(Node *node) {
    if (!node){return;}
    cout << *node;
    printInorder(node->left);
    printInorder(node->right);
}

void HuffmanTree::printCodes() {
    string str;
    printCodesRecur(root, str);
}

void HuffmanTree::printCodesRecur(Node *node, string str)
{
 
    if (!node) {return;}

    if (node->data->letter != '#'){
        cout << node->data->letter << " " << str << "\n";
    }
 
    printCodesRecur(node->left, str + "1");
    printCodesRecur(node->right, str + "0");
}

HuffmanTree::~HuffmanTree() {
    //delete[] root;
}
#include <iostream>
#include <fstream>
#include <deque>
#include "huffman.h"

using namespace std;

int main() {
    ifstream fin;
    fin.open("bla.txt");
    Queue queue;
    char next;

    while (fin.get(next)) {
        queue.addNode(next);
    }
    
    queue.sort();

    // deque<Node *> node_queue;
    // for (int i = 0; i < queue.getSize(); i++) {
    //     node_queue.push_back(new Node(queue[i]));
    // }

    // Node *node;
    // while(!node_queue.empty()){
    //     Node *left = node_queue.front();
    //     node_queue.pop_front();
    //     Node *right = node_queue.front();
    //     node_queue.pop_front();
    //     node = new Node(new DataClass('#', left->data->freq+right->data->freq), left, right);
    //     if(!node_queue.empty()){
    //         node_queue.push_back(node);
    //         int cnt = node_queue.size() - 1;
    //         while ((node_queue[cnt]->data->freq <= node_queue[cnt-1]->data->freq) && (cnt > 0)){
    //             swap(node_queue[cnt], node_queue[cnt-1]);
    //             cnt--;
    //         }
    //     }
    // }
    // HuffmanTree tree = HuffmanTree(node);
    
    HuffmanTree tree;
    tree.build(queue);
    tree.print();
    tree.printCodes();
    fin.close();
    return 0;
}
#include <iostream>
#include <fstream>
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

    HuffmanTree tree;
    tree.build(queue);
    tree.print();
    cout << endl;
    tree.printCodes();
    fin.close();
    return 0;
}
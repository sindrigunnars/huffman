#include <iostream>
#include <fstream>
#include "huffman.h"

using namespace std;

int main() {
    ifstream fin;
    fin.open("alice29.txt");
    Queue queue;
    char next;
    while (fin.get(next)) {
        queue.addNode(next);
    }
    queue.sort();
    cout << queue;
    fin.close();
    return 0;
}
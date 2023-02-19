#include "data.h"
#include "huffman.h"
using namespace std;

int main(int argc, char** argv) {
    HuffmanTree tree;
    if (argc == 4) {
        if (strcmp(argv[1], "-e") == 0) {
            tree.build(argv[2]);
            tree.write(argv[2], argv[3]);
        } else if (strcmp(argv[1], "-d") == 0) {
            tree.read(argv[2], argv[3]);
        }
    }
    return 0;
}
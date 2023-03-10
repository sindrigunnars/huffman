#include "data.h"
#include <deque>
using namespace std;

struct HuffmanTable {
    char letter;
    string code;
    HuffmanTable(char letter, string str);
    friend ofstream& operator<<(ofstream& fout, HuffmanTable tab);
};

class HuffmanTree{
    public:
        void build(char *arg);
        void write(char* in, char* out);
        void read(char *in, char *out);
        HuffmanTree(Node *node);
        HuffmanTree();
        virtual ~HuffmanTree();
    private:
        Queue buildQueue(char *arg);
        void buildTable();
        void buildTableRecur(Node *node, string str);
        Node *root;
        deque<HuffmanTable> table;
        // void print();
        // void printInorder(Node *node);
        // void buildFromTable();

};
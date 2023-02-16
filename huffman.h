#include <iostream>
using namespace std;

struct DataClass{
    DataClass(char letter);
    int freq;
    char letter;
    friend ostream& operator<<(ostream &fout, DataClass *data);
};

class Node{
    public:
        Node(DataClass *data = NULL, Node *left = NULL, Node *right = NULL);
        virtual ~Node();
        DataClass *data;
        friend ostream& operator<<(ostream &fout, Node node);

    private:
        Node *left;
        Node *right;
};

class HuffmanTree{
    public:

    private:
        Node *root;
};

class Queue{
    public:
        Queue();
        void addNode(char letter);
        Node operator[](int idx);
        friend ostream& operator<<(ostream &fout, Queue &que);
        void sort();
    private:
        int capacity, size;
        Node *nodes;
        void resize();
};
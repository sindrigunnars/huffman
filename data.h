#pragma once
#ifndef DATA_H
#define DATA_H
#include <iostream>
using namespace std;

struct DataClass{
    DataClass(char letter);
    DataClass(char letter, int freq);
    DataClass();
    int freq;
    char letter;
    friend ostream& operator<<(ostream &fout, DataClass *data);
};

class Node{
    public:
        Node(DataClass *data = NULL, Node *left = NULL, Node *right = NULL);
        DataClass *data;
        friend ostream& operator<<(ostream &fout, Node *node);
        Node *left;
        Node *right;
};

class Queue{
    public:
        Queue();
        void addNode(char letter);
        Node* operator[](int idx);
        friend ostream& operator<<(ostream &fout, Queue &que);
        void sort();
        int getSize();
        virtual ~Queue();
    private:
        int capacity, size;
        Node **nodes;
        void resize();
};

#endif
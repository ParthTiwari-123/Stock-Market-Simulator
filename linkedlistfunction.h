// linkedlist.h
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>

using namespace std;

const int MAX_STOCKS=10;

struct Node {
    string symbol;
    double price;
    int qtyAvailable;
    Node* next;
};

// Function declarations
Node* createStockList();
void show(Node* head, const string& symbol);
void displayStockData(Node* head);
void deleteList(Node*& head);

#endif // LINKEDLIST_H

#include <iostream>
#include <string>

using namespace std;

// Constants
const int MAX_STOCKS = 10;  // Maximum number of stocks we can store

struct Node {
    string symbol;    // Stock symbol
    double price;     // Stock price
    int qtyAvailable; // Quantity available
    Node* next;       // Pointer to the next node
};

// Function to create and initialize linked list with stock data
Node* createStockList() {
    string symbols[MAX_STOCKS] = {"AAPL", "GOOGL", "MSFT", "AMZN", "META","TSLA", "NFLX", "NVDA", "DIS", "JPM"};
    double prices[MAX_STOCKS] = {223.81, 180.12, 417.47, 206.36, 582.28, 357.79, 804.9, 144.81, 100.875, 239.37};
    int qtyAvailable[MAX_STOCKS] = {6626, 577, 1537, 1540, 1652, 22154, 151, 58250, 1141, 140};

    Node* head = nullptr; // Initialize head of the linked list
    Node* current = nullptr;

    for (int i = 0; i < MAX_STOCKS; ++i) {
        Node* newNode = new Node{symbols[i], prices[i], qtyAvailable[i], nullptr};

        if (head == nullptr) {
            head = newNode; // First node becomes the head
        } else {
            current->next = newNode; // Append new node to the list
        }
        current = newNode; // Move current pointer to the new node
    }

    return head; // Return the head of the linked list
}

void show(Node* head, const string& symbol) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->symbol == symbol) {
            cout << "\nStock Details:\n";
            cout << "Symbol: " << temp->symbol << "\nPrice: $" << temp->price 
                 << "\nQuantity Available: " << temp->qtyAvailable << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Stock symbol not found.\n";
}

// Function to display all stock data in the linked list
void displayStockData(Node* head) {
    if (head == nullptr) {
        cout << "No stocks to display.\n";
        return;
    }

    cout << "\nStock Data:\n";
    Node* temp = head;
    int stockNum = 1;
    while (temp != nullptr) {
        cout << "Stock " << stockNum << ": Symbol = " << temp->symbol
             << ", Price = $" << temp->price
             << ", Quantity Available = " << temp->qtyAvailable << endl;

        temp = temp->next; // Move to the next node
        stockNum++;
    }
}

// Function to delete the linked list to free memory
void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
#ifndef MAIN_FUNCTION_LINKEDLIST
int main() {
    Node* head = createStockList(); // Create the linked list
    int choice;
    
    do {
        cout << "\nMenu:\n";
        cout << "1. Display all stock data\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                displayStockData(head);
                break;
            case 2:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 2);

    // Clean up the linked list memory
    deleteList(head);

    return 0;
}
#endif
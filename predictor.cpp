#include <iostream>
#include <vector>
#include <random>

using namespace std;

struct TreeNode {
    double price;
    TreeNode *left, *right;
    TreeNode(double p) : price(p), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* node, double price) {
    if (node == nullptr) {
        return new TreeNode(price);
    }
    if (price < node->price) {
        node->left = insert(node->left, price);
    } else if (price > node->price) {
        node->right = insert(node->right, price);
    }
    return node;
}

double findMin(TreeNode* node) {
    if (!node) return -1;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node->price;
}

double findMax(TreeNode* node) {
    if (!node) return -1;
    while (node->right != nullptr) {
        node = node->right;
    }
    return node->price;
}

vector<double> generatePrices(double openingPrice, int count, double minRange, double maxRange) {
    vector<double> prices;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(minRange, maxRange);
    for (int i = 0; i < count; ++i) {
        prices.push_back(dist(gen));
    }
    return prices;
}

int main() {
    double openingPrice;
    int sampleCount=10;
    double minRange, maxRange;

    string selectedSymbol;
    cout<<"Enter the stock symbol for which you want to find the Predicted Values: ";
    cin>>selectedSymbol;
    string symbols[10] = {"AAPL", "GOOGL", "MSFT", "AMZN", "META","TSLA", "NFLX", "NVDA", "DIS", "JPM"};
    double price[10] =  {223.81, 180.12, 417.47, 206.36, 582.28, 357.79, 804.9, 144.81, 100.875, 239.37};
    for(int i=0;i<10;i++)
    {
        if(selectedSymbol==symbols[i])
        {
            openingPrice=price[i];
            minRange=openingPrice-10;
            maxRange=openingPrice+10;
        }

    }
    vector<double> prices = generatePrices(openingPrice, sampleCount, minRange, maxRange);

    // Building the BST with generated prices
    TreeNode* root = nullptr;
    for (double price : prices) {
        root = insert(root, price);
    }

    double minPrice = findMin(root);
    double maxPrice = findMax(root);
    double predictedPrice = root ? root->price : -1;

    cout << "Predicted Price Range lies between: " << minPrice << " and " << maxPrice << endl;
    cout << "Predicted Price: " << predictedPrice << endl;  //root of bst

    return 0;
}

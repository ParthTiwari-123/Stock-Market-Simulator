#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <vector>

struct TreeNode {
    double price;
    TreeNode *left, *right;
    TreeNode(double p);
};

TreeNode* insert(TreeNode* node, double price);
double findMin(TreeNode* node);
double findMax(TreeNode* node);
std::vector<double> generatePrices(double openingPrice, int count, double minRange, double maxRange);

#endif

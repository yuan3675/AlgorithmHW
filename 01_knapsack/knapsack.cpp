#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stdio.h>

using namespace std;

vector<vector<float>> items;
stack<float> currentPrice;
stack<bool> tree;
int itemNum, capacity, restCap;
float lowerBound, upperBound;

void countUpperBound() {
    if (currentPrice.size() > 0) upperBound = currentPrice.top();
    else upperBound = 0.0;
    // TODO: fill the rest capacity with highest P/W item.
    int tmpCap = restCap;
    for(int i = tree.size(); i < itemNum; i++) {
        if (tmpCap > 0) {
            if (tmpCap >= items.at(i).at(1)) {
                upperBound += items.at(i).at(0);
                tmpCap -= items.at(i).at(1);
            }
            else {
                upperBound += items.at(i).at(0) * (tmpCap / items.at(i).at(1));
                tmpCap = 0;
            }
        }
        else break;
    }
}

void findOptimalPrice() {
    // Find the first lower bound.
    for (int i = 0; i < itemNum; i++) {
        if (restCap > 0) {
            if (restCap >= items.at(i).at(1)) {
                if (currentPrice.size() == 0) currentPrice.push(items.at(i).at(0));
                else currentPrice.push(currentPrice.top() + items.at(i).at(0));
                restCap -= items.at(i).at(1);
                tree.push(1);
            }
            else {
                if (currentPrice.size() == 0) currentPrice.push(0);
                else currentPrice.push(currentPrice.top());
                tree.push(0);
            }
        }
        else break;
    }
    lowerBound = currentPrice.top();

    // Traverse the tree.
    bool direction = 0; // up = 0, down = 1
    while (!tree.empty()) {
        if (tree.size() == itemNum || restCap <= 0) {
            if (lowerBound < currentPrice.top()) {
                lowerBound = currentPrice.top();
            }
            if (tree.top() == 1) restCap += items.at(tree.size()-1).at(1);
            tree.pop();
            currentPrice.pop();
            direction = 0;
        }
        else {
            countUpperBound();
            if (lowerBound >= upperBound) {
                if (tree.top() == 1) restCap += items.at(tree.size()-1).at(1);
                tree.pop();
                currentPrice.pop();
                direction = 0;
            }
            else {
                bool node = tree.top();
                if (node && !direction) {
                    tree.top() = 0;
                    currentPrice.pop();
                    if (currentPrice.size() == 0) currentPrice.push(0);
                    else currentPrice.push(currentPrice.top());
                    restCap += items.at(tree.size()-1).at(1);
                    direction = 1; 
                }
                else if (!node && !direction) {
                    tree.pop();
                    currentPrice.pop();
                    direction = 0;
                }
                else {
                    if (restCap >= items.at(tree.size()).at(1)) {
                        if (currentPrice.size() == 0) currentPrice.push(items.at(tree.size()).at(0));
                        else currentPrice.push(currentPrice.top() + items.at(tree.size()).at(0));
                        restCap -= items.at(tree.size()).at(1);
                        tree.push(1);
                    }
                    else {
                        if (currentPrice.size() == 0) currentPrice.push(0);
                        else currentPrice.push(currentPrice.top());
                        tree.push(0);
                    }
                    direction = 1;
                }
            }
        }
    }
    printf("%d\n", (int)lowerBound);
}

int main() {
    scanf("%d", &capacity);
    scanf("%d", &itemNum);
    vector<float> item;
    item.assign(3, 0.0);
    items.assign(itemNum, item);
    restCap = capacity;

    for (int i = 0; i < itemNum; i++) {
        float price, weight;
        scanf("%f", &price);
        scanf("%f", &weight);
	    items.at(i).at(0) = price;
	    items.at(i).at(1) = weight;
        items.at(i).at(2) = price / weight;
    }
    sort(items.begin(), items.end(), [](const vector<float>& a, const vector<float>& b) {
		    return a[2] > b[2];
    });

    findOptimalPrice();
    return 0;
}

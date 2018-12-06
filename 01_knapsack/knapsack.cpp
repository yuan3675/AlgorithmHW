#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stdio.h>

using namespace std;

vector<int> itemPrice;
vector<int> itemWeight;
stack<int> upperBound;
stack<bool> tree;
int itemNum, capacity, lowerBound;

int countUpperBound() {
    int restCap = capacity;
    int upperBound = 0;
    for (int i = 0; i < tree.size(); i++) {
        upperBound += itemPrice.at((tree.size()-i-1)) * tree.top();
        restCap -= itemWeight.at((tree.size()-i-1)) * tree.top();
    }

    // TODO: fill the rest capacity with highest P/W item.
}

void findOptimalPrice() {
}

int main() {
    scanf("%d", capacity);
    scanf("%d", itemNum);
    itemPrice.assign(itemNum, 0);
    itemWeight.assign(itemNum, 0);
    upperBound.assign(itemNum, 0);

    for (int i = 0; i < itemNum; i++) {
        int price, weight;
        scanf("%d", price);
        scanf("%d", weight);
	itemPrice.at(i) = price;
	itemWeight.at(i) = weight;
    }

    findOptimalPrice();
    return 0;
}

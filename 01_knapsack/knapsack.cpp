#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stdio.h>

using namespace std;

vector<vector<float>> items;
stack<int> currentPrice;
stack<bool> tree;
int itemNum, capacity, lowerBound;
float upperBound;

bool mySort(vector v1, vector v2) {
    return v1.at(2) < v2.at(2);
}

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
    vector<float> item(3, 0);
    items.assign(item, itemNum);

    for (int i = 0; i < itemNum; i++) {
        int price, weight;
        scanf("%d", price);
        scanf("%d", weight);
	    items.at(i).at(0) = price;
	    items.at(i).at(1) = weight;
        items.at(i).at(2) = price / weight;
    }
    sort(items.begin(), items.end(), mySort());

    for(int i = 0; i < itemNum; i++) {
        printf("%f ", items.at(i).at(0));
        printf("%f ", items.at(i).at(1));
        printf("%f\n", items.at(i).at(2));
    }
    //findOptimalPrice();
    return 0;
}

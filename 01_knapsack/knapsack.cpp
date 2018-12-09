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

int countUpperBound() {
    // TODO: fill the rest capacity with highest P/W item.
}

void findOptimalPrice() {

}

int main() {
    scanf("%d", &capacity);
    scanf("%d", &itemNum);
    vector<float> item;
    item.assign(3, 0.0);
    items.assign(itemNum, item);

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

    for(int i = 0; i < itemNum; i++) {
        printf("%f ", items.at(i).at(0));
        printf("%f ", items.at(i).at(1));
        printf("%f\n", items.at(i).at(2));
    }
    //findOptimalPrice();
    return 0;
}

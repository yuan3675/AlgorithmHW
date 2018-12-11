#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <climits>
#include <cmath>

using namespace std;

long minDis = LONG_MAX;

long getDistance(vector<int> a, vector<int> b) {
    return (long int)(pow((a.at(0) - b.at(0)), 2) + pow((a.at(1) - b.at(1)), 2));
}

int findMiddleX(vector<int> tmp) {
    sort(tmp.begin(), tmp.end());
    return tmp.at(tmp.size()/2);
}

void findClosetPairs(int num, vector<vector<int>> points) {
    // not safe, may have error
    if (num <= 2) { 
        if (num == 2) {
            long dis = getDistance(points.at(0), points.at(1));
            if (dis < minDis) minDis = dis;
        }
    }
    else {
        vector<int> tmp(num, 0);
        for (int i = 0; i < num; i++) {
            tmp.at(i) = points.at(i).at(0);
        }
        int middle = findMiddleX(tmp);
        vector<vector<int>> L, R;
        for (int i = 0; i < num; i++) {
            if (points.at(i).at(0) <= middle) L.push_back(points.at(i));
            else R.push_back(points.at(i));
        }
        findClosetPairs(L.size(), L);
        findClosetPairs(R.size(), R);
        // TODO: merge
    } 
}

int main() {
    int pointNum;
    scanf("%d", &pointNum);
    vector<int> tmp(2, 0);
    vector<vector<int>> points;
    points.assign(pointNum, tmp);
    
    for (int i = 0; i < pointNum; i++) {
        int x, y;
        scanf("%d", &x);
        scanf("%d", &y);
        points.at(i).at(0) = x;
        points.at(i).at(1) = y;
    }
    sort(points.begin(), points.end(), [](const vector<int> &a, const vector<int> &b) {
        return a[1] < b[1];
});
    //findClosetPairs(pointNum, points);
}

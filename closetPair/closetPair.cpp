#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include <cmath>

using namespace std;

long minDis = LONG_MAX;
vector<vector<int>> lookUp;
vector<vector<vector<int>>> closestPairs;

bool compareX(const vector<int> &a, const vector<int> &b) {
    return a[0] < b[0];
}

bool compareY(const vector<int> &a, const vector<int> &b) {
    return a[1] < b[1];
}

long getDistance(vector<int> a, vector<int> b) {
    return (long int)(pow((a.at(0) - b.at(0)), 2) + pow((a.at(1) - b.at(1)), 2));
}

void bruteForce(vector<vector<int>> points) {
    for (int i = 0; i < points.size(); i++) {
        for (int j = i+1; j < points.size(); j++) {
            dis = getDistance(points.at(i), points.at(j));
            if (dis < minDis) {
                minDis = dis;
                closestPairs.clear();
                vector<vector<int>> closestPair = {points.at(i), points.at(j)};
                closestPairs.push_back(closestPair);
            }
            else if (dis == minDis) {
                vector<vector<int>> closestPair = {points.at(i), points.at(j)};
                closestPairs.push_back(closestPair);
            }
        }
    }
}

void mergeStrip(vector<vector<int>> points) {
    sort(points.begin(), points.end(), compareY);
    for (int i = 0; i <     
}                

void findClosestPairs(vector<vector<int>> points) {
    // not safe, may have error
    if (points.size() <= 3) {
        bruteForce(points); 
    }
    else {
        sort(points.begin(), points.end(), compareX);
        int middle = points.at(points.size()/2).at(0);
        vector<vector<int>> L, R;
        for (int i = 0; i < points.size(); i++) {
            if (points.at(i).at(0) <= middle) L.push_back(points.at(i));
            else R.push_back(points.at(i));
        }
        findClosetPairs(L);
        findClosetPairs(R);
        // TODO: merge
        vector<vector<int>> strip;
        for (int i = 0; i < points.size(); i++) {
            if ((long int)(abs(points.at(i).at(0))) - middle <= sqrt(minDis)) strip.push_back(points.at(i));
        }
	mergeStrip(strip);
    } 
}

int main() {
    int pointNum;
    scanf("%d", &pointNum);
    vector<int> tmp(2, 0);
    vector<vector<int>> points;
    points.assign(pointNum, tmp);
    lookUp.assign(pointNum, tmp);
    
    for (int i = 0; i < pointNum; i++) {
        int x, y;
        scanf("%d", &x);
        scanf("%d", &y);
        points.at(i).at(0) = x;
        points.at(i).at(1) = y;
        lookUp.at(i).at(0) = x;
        lookUp.at(i).at(1) = y;
    }
    findClosestPairs(points);
}

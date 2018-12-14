#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include <cmath>

using namespace std;

long minDis = LONG_MAX;
vector<vector<int>> closestPairs;

bool compareX(const vector<int> &a, const vector<int> &b) {
    return a[0] < b[0];
}

bool compareY(const vector<int> &a, const vector<int> &b) {
    return a[1] < b[1];
}

bool compareXY(const vector<int> &a, const vector<int> &b) {
    if (a[0] != b[0]) return a[0] < b[0];
    else return a[1] < b[1];
}

long getDistance(vector<int> &a, vector<int> &b) {
    return (long int)(pow((a.at(0) - b.at(0)), 2) + pow((a.at(1) - b.at(1)), 2));
}

bool sameX(vector<vector<int>> &points) {
    for (int i = 0; i < points.size()-1; i++) {
        if (points.at(i).at(0) != points.at(i+1).at(0)) return false;
    }
    return true;
}

void bruteForce(vector<vector<int>> &points) {
    // If many points have same x axis, may be slow.
    for (int i = 0; i < points.size(); i++) {
        for (int j = i+1; j < points.size(); j++) {
            long dis = getDistance(points.at(i), points.at(j));
            if (dis < minDis) {
                minDis = dis;
                closestPairs.clear();
		int a = points.at(i).at(2);
		int b = points.at(j).at(2);
                vector<int> closestPair;
		if (a < b) closestPair = {a, b};
		else closestPair = {b, a};
                closestPairs.push_back(closestPair);
            }
            else if (dis == minDis) {
		int a = points.at(i).at(2);
		int b = points.at(j).at(2);
                vector<int> closestPair;
		if (a < b) closestPair = {a, b};
		else closestPair = {b, a};
                closestPairs.push_back(closestPair);
            }
        }
    }
}

void mergeStrip(vector<vector<int>> &L, vector<vector<int>> &R) {
    sort(L.begin(), L.end(), compareY);
    sort(R.begin(), R.end(), compareY);
    for (int i = 0; i < L.size(); i++) {
	for (int j = 0; j < R.size(); j++) {
            // May be slow
            if (abs(L.at(i).at(1) - R.at(j).at(1)) > sqrt(minDis)) continue;
	    long dis = getDistance(L.at(i), R.at(j));
            if (dis < minDis) {
                minDis = dis;
                closestPairs.clear();
		int a = L.at(i).at(2);
		int b = R.at(j).at(2);
                vector<int> closestPair;
		if (a < b) closestPair = {a, b};
		else closestPair = {b, a};
                closestPairs.push_back(closestPair);
            }
            else if (dis == minDis) {
		int a = L.at(i).at(2);
		int b = R.at(j).at(2);
                vector<int> closestPair;
		if (a < b) closestPair = {a, b};
		else closestPair = {b, a};
                closestPairs.push_back(closestPair);
            }
	}
    }           		
}                

void findClosestPairs(vector<vector<int>> &points) {
    if (points.size() <= 3 || sameX(points)) {
        bruteForce(points); 
    }
    else {
        sort(points.begin(), points.end(), compareX);
        int middle = points.at(points.size()/2).at(0);
        vector<vector<int>> L, R;
        for (int i = 0; i < points.size(); i++) {
            if (points.at(i).at(0) < middle) L.push_back(points.at(i));
            else R.push_back(points.at(i));
        }
        findClosestPairs(L);
        findClosestPairs(R);
        // TODO: merge
        vector<vector<int>> stripL, stripR;
        for (int i = 0; i < L.size(); i++) {
            if (middle - (long int)L.at(i).at(0) <= sqrt(minDis)) stripL.push_back(L.at(i));
        }
        for (int i = 0; i < R.size(); i++) {
            if ((long int)R.at(i).at(0) - middle <= sqrt(minDis)) stripR.push_back(R.at(i));
        }
	mergeStrip(stripL, stripR);
    } 
}

int main() {
    int pointNum;
    scanf("%d", &pointNum);
    vector<int> tmp(3, 0);
    vector<vector<int>> points;
    points.assign(pointNum, tmp);
    
    for (int i = 0; i < pointNum; i++) {
        int x, y;
        scanf("%d", &x);
        scanf("%d", &y);
        points.at(i).at(0) = x;
        points.at(i).at(1) = y;
	points.at(i).at(2) = i+1;
    }
    findClosestPairs(points);
    sort(closestPairs.begin(), closestPairs.end(), compareXY);

    printf("%ld %d\n", minDis, closestPairs.size());
    for (int i = 0; i < closestPairs.size(); i++) {
        printf("%d %d\n", closestPairs.at(i).at(0), closestPairs.at(i).at(1));
    }
}

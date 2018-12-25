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

bool sameX(vector<vector<int>> &points, int begin, int len) {
    for (int i = begin; i < begin + len - 1; ++i) {
	// Compare the x coordinate with their neighbor, if not the same, return false.
        if (points.at(i).at(0) != points.at(i+1).at(0)) return false;
    }
    return true;
}

void same(vector<vector<int>> &points, int begin, int len) {
    sort(points.begin() + begin, points.begin() + begin + len, compareY);
    for (int i = begin; i < begin + len - 1; i++) {
        long dis = getDistance(points.at(i), points.at(i+1));
        if (dis < minDis) {
            minDis = dis;
            closestPairs.clear();
            int a = points.at(i).at(2);
            int b = points.at(i+1).at(2);
            vector<int> closestPair;
            if (a < b) closestPair = {a, b};
            else closestPair = {b, a};
            closestPairs.push_back(closestPair);
        }
        else if (dis == minDis) {
            int a = points.at(i).at(2);
            int b = points.at(i+1).at(2);
            vector<int> closestPair;
            if (a < b) closestPair = {a, b};
            else closestPair = {b, a};
            closestPairs.push_back(closestPair);
        }
    }
}

void bruteForce(vector<vector<int>> &points, int begin, int len) {
    // Compute distance in the order of (0,1), (0,2), (1,2)
    for (int i = begin; i < begin + len; i++) {
        for (int j = i+1; j < begin + len; j++) {
            long dis = getDistance(points.at(i), points.at(j));
	    // If the distance is smaller than the min distance, update min distance, flush the closestPair vector and put new pair into closestPair vector. 
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
	    // The distance is the same as min distance, put new pair into closestPair vector
            else if (dis == minDis) {
		int a = points.at(i).at(2);
		int b = points.at(j).at(2);
                vector<int> closestPair;
		if (a < b) closestPair = {a, b};
		else closestPair = {b, a};
                closestPairs.push_back(closestPair);
            }
	    // The distance is greater than min distance, do nothing.
        }
    }
}

void mergeStrip(vector<vector<int>> &L, vector<vector<int>> &R) {
    sort(L.begin(), L.end(), compareY);
    sort(R.begin(), R.end(), compareY);
    for (int i = 0; i < L.size(); i++) {
	for (int j = 0; j < R.size() && R.at(j).at(1) <= L.at(i).at(1) + sqrt(minDis); j++) {
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

void findClosestPairs(vector<vector<int>> &points, int begin, int len) {
    // If the rest of points are all having the same x coordinate, find the answer directly.
    if (sameX(points, begin, len)) {
        same(points, begin, len); 
    }
    
    // If the number of points are less than 3, brute force.
    else if (len <= 3) bruteForce(points, begin, len);
    else {
        findClosestPairs(points, begin, len/2);
	// If the len is odd, right part will have more points.
        findClosestPairs(points, begin + (len/2), len - len/2);
        // TODO: merge
	int middle = points.at(begin + (len/2)).at(0);
	vector<vector<int>> stripL, stripR;
        for (int i = begin; i < begin + (len/2); i++) {
            if (middle - (long int)points.at(i).at(0) <= sqrt(minDis)) stripL.push_back(points.at(i));
        }
        for (int i = begin + (len/2); i < begin + len; i++) {
            if ((long int)points.at(i).at(0) - middle <= sqrt(minDis)) stripR.push_back(points.at(i));
        }
	mergeStrip(stripL, stripR);
    } 
}

int main() {
    // record the number of points
    int pointNum;
    scanf("%d", &pointNum);
    // Initialize a vector which size is (the number of points) * 3
    vector<int> tmp(3, 0);
    vector<vector<int>> points;
    points.assign(pointNum, tmp);
    
    for (int i = 0; i < pointNum; i++) {
        int x, y;
        scanf("%d", &x);
        scanf("%d", &y);
	// record the coordinate and the input order of each point
        points.at(i).at(0) = x;
        points.at(i).at(1) = y;
	points.at(i).at(2) = i+1;
    }
    // sort the points in x coordinate
    sort(points.begin(), points.end(), compareX);
    findClosestPairs(points, 0, pointNum);
    sort(closestPairs.begin(), closestPairs.end(), compareXY);

    printf("%ld %d\n", minDis, closestPairs.size());
    for (int i = 0; i < closestPairs.size(); i++) {
        printf("%d %d\n", closestPairs.at(i).at(0), closestPairs.at(i).at(1));
    }
}

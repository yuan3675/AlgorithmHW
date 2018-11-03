#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int constraintNum;

void pruneAndSearch(vector<vector<int>> constraints) {
    int xL = INT_MIN, xR = INT_MAX;

    while(constraints.size() < 3) {
        vector<vector<int>> iPos, iNeg, iZero;
        vector<double> rx, rxPos, rxNeg;
        double xm;
	// classify I0, I+, I-
	for (int i = 0; i < constraints.size(); i++) {
	    if (constraints.at(i).at(1) > 0) iPos.push_back(constraints.at(i));
	    else if (constraints.at(i).at(1) < 0) iNeg.push_back(constraints.at(i));
	    else iZero.push_back(constraints.at(i));
	}
        if (iZero.size() != 0) {
	    for (int i = 0; i < iZero.size(); i++) {
		double tmp = iZero.at(i).at(2) / (double) iZero.at(i).at(0);
	        if (iZero.at(i).at(0) < 0) {
                    if (tmp > xL) xL = tmp;
		}
                else if (iZero.at(i).at(0) > 0) {
                    if (tmp < xR) xR = tmp;
		}
	    }
	}	    
	// determine the x-coordinates of their intersections
	if (iNeg.size() >= 2) {
            for (int i = 0; i < iNeg.size(); i=i+2) {
	        int index;
	        double a1 = iNeg.at(i).at(0), b1 = iNeg.at(i).at(1), c1 = iNeg.at(i).at(2), a2, b2, c2;
	        if ( i == iNeg.size() - 1) {
	            a2 = iNeg.at(0).at(0);
	            b2 = iNeg.at(0).at(1);
	            c2 = iNeg.at(0).at(2);
		    index = 0;
	        }
	        else {
	            a2 = iNeg.at(i+1).at(0);
	            b2 = iNeg.at(i+1).at(1);
	            c2 = iNeg.at(i+1).at(2);
		    index = i+1;
	        }
                double tmp1 = (b1 * a2) - (b2 * a1);
	        if (tmp1 == 0.0) {
		    double y1 = c1 / (double)b1;
		    double y2 = c2 / (double)b2;
		    if (y1 > y2) constraints.erase(constraints.begin()+index);
		    else constraints.erase(constraints.begin()+i);
	        }
                double tmp2 = (c1 * a2) - (c2 * a1);
                double y = tmp2 / tmp1;
                double x = (c1 - (b1 * y)) / (double)a1;
	        if (x <= xR && x >= xL) {
		    rx.push_back(x);
		    rxNef.push_back(x);
		}
	    }
	}

	if (iPos.size() >= 2) {
            for (int i = 0; i < iPos.size(); i=i+2) {
	        int index;
	        double a1 = iPos.at(i).at(0), b1 = iPos.at(i).at(1), c1 = iPos.at(i).at(2), a2, b2, c2;
	        if ( i == iPos.size() - 1) {
	            a2 = iPos.at(0).at(0);
	            b2 = iPos.at(0).at(1);
	            c2 = iPos.at(0).at(2);
		    index = 0;
	        }
	        else {
	            a2 = iPos.at(i+1).at(0);
	            b2 = iPos.at(i+1).at(1);
	            c2 = iPos.at(i+1).at(2);
		    index = i+1;
	        }
                double tmp1 = (b1 * a2) - (b2 * a1);
	        if (tmp1 == 0.0) {
		    double y1 = c1 / (double)b1;
		    double y2 = c2 / (double)b2;
		    if (y1 < y2) constraints.erase(constraints.begin()+index);
		    else constraints.erase(constraints.begin()+i);
	        }
                double tmp2 = (c1 * a2) - (c2 * a1);
                double y = tmp2 / tmp1;
                double x = (c1 - (b1 * y)) / (double)a1;
	        if (x <= xR && x >= xL) {
		    rx.push_back(x);
		    rxPos.push_back(x);
		}
	    }
	}
        
	if (rx.size() == 0) {
	    break;
	}

        // find the mediam in rx
	sort(rx.begin(), rx.end());
	xm = rx.at(rx.size()/2);
	// find smin, smax, tmin, tmax, ax, ay, bx, by
	double smin = 500, smax = -500, tmin = 500, tmax = -500, ax = xm, ay = INT_MIN, bx = xm, by = INT_MAX;
	for (int i = 0; i < iNeg.size(); i++) { // I- part
	    double tmp = (-1 * iNeg.at(i).at(0) * xm - iNeg.at(i).at(2)) / iNeg.at(i).at(1);
	    if (tmp > ay) ay = tmp;
	}
	for (int i = 0; i < iPos.size(); i++) { // I+ part
            double tmp = (-1 * iPos.at(i).at(0) * xm - iPos.at(i).at(2)) / iPos.at(i).at(1);
	    if (tmp < by) by = tmp;
	}
	for (int i = 0; i < iNeg.size(); i++) {
	    if (iNeg.at(i).at(0) * ax + iNeg.at(i).at(1) * ay == iNeg.at(i).at(2)) {
	        double tmp = -1 * (iNeg.at(i).at(0) / iNeg.at(i).at(1));
	        if (tmp > smax) smax = tmp;
	        if (tmp < smin) smin = tmp;
	    }
	}
	for (int i = 0; i < iPos.size(); i++) {
	    if (iPos.at(i).at(0) * bx + iPos.at(i).at(1) * by == iPos.at(i).at(2)) {
	        double tmp = -1 * (iPos.at(i).at(0) / iPos.at(i).at(1));
	        if (tmp > tmax) tmax = tmp;
	        if (tmp < tmin) tmin = tmp;
	    }
	}

	if (ay <= by) {
	    // case1 xm < x*
	    if (smax < 0) {
	        xL = xm;
		// prune redundant constraints

	    }
	    // case2
	    else if (smin > 0) {
	        xR = xm;
		// prune redundant constraints
	    }
	    // case3
	    else {
	        // xm is the answer
		if (ay < 0) {
		    ay = ay - 0.5;
		    cout << (int)ay << endl;
		else {
		    ay = ay + 0.5
		    cout << (int)ay << endl;
		}
		return;
	    }
	}
	else {
	    // case4
	    if (smax < tmin) {
	        xL = xm;
		// prune redundant constraints
	    }
	    // case5
	    else if (smin > tmax) {
		xR = xm;
		// prune redundant constraints
	    }
	    // case6
	    else { 
	        cout << "NA" << endl;
		return;
	    }
	}
    }
	
    
}

int main() {
    cin >> constraintNum;
    vector<int> row(3, 0);
    vector<vector<int>> constraints(constraintNum, row);

    for (int i = 0; i < constraintNum; i++) {
	for (int j = 0; j < 3; j++) {
	    int tmp;
	    cin >> tmp;
	    constraints.at(i).at(j) = tmp;
	}
    }
    pruneAndSearch(constraints);
}

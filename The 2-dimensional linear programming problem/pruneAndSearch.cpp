#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Line {
    public:
	int a, b, c;
	double slope;
	Line(){};
	Line(int A, int B, int C) {
	    a = A;
	    b = B;
	    c = C;
	    if (B != 0) {
	        slope = -1 * A / (double) B;
	    }
	}
};

bool mySort(vector<double> i, vector<double> j) {
    return (i.at(2) < j.at(2));
}

void pruneAndSearch(vector<Line> &constraints) {
    double xL = INT_MIN, xR = INT_MAX;
    vector<Line> iPos, iNeg, iZero;
    // classify I0, I+, I-
    for (int i = 0; i < constraints.size(); i++) {
	if (constraints.at(i).b > 0) iPos.push_back(constraints.at(i));
	else if (constraints.at(i).b < 0) iNeg.push_back(constraints.at(i));
	else iZero.push_back(constraints.at(i));
    }
    
    // find the constraint of x-axis
    if (iZero.size() != 0) {
	for (int i = 0; i < iZero.size(); i++) {
            double tmp = iZero.at(i).c / (double) iZero.at(i).a;
	    if (iZero.at(i).a < 0) {  // x >= k
                if (tmp > xL) xL = tmp;
	    }
            else if (iZero.at(i).a > 0) { // x <= k
                if (tmp < xR) xR = tmp;
	    }
	}
	iZero.clear();
        if (xL > xR) {  // no available region
            cout << "NA" <<endl;
            return;
        }
    }
    if (iNeg.size() == 0) {
	cout << "-INF" << endl;
        return;
    }	    

    while(iPos.size() + iNeg.size() > 2) {
	vector<vector<double>> rx;
	vector<vector<int>> rxPos, rxNeg;
        double xm;
        

	// determine the x-coordinates of their intersections
	if (iNeg.size() >= 2) {
	    int counter = 0;  // record which slot in rxNeg store this intersection
            for (int i = 0; i < iNeg.size();) {
	        int index;
	        double a1 = iNeg.at(i).a, b1 = iNeg.at(i).b, c1 = iNeg.at(i).c, slope1 = iNeg.at(i).slope, a2, b2, c2, slope2;
	        if ( i == iNeg.size() - 1) {
	            a2 = iNeg.at(0).a;
	            b2 = iNeg.at(0).b;
	            c2 = iNeg.at(0).c;
		    slope2 = iNeg.at(0).slope;
		    index = 0;
	        }
	        else {
	            a2 = iNeg.at(i+1).a;
	            b2 = iNeg.at(i+1).b;
	            c2 = iNeg.at(i+1).c;
		    slope2 = iNeg.at(i+1).slope;
		    index = i+1;
	        }
                double tmp1 = (b1 * a2) - (b2 * a1);
	        if (tmp1 == 0.0) {
		    double y1 = c1 / (double)b1;
		    double y2 = c2 / (double)b2;
		    if (y1 > y2) iNeg.erase(iNeg.begin()+index);
		    else iNeg.erase(iNeg.begin()+i);
		    i = i+1;
		    continue;
	        }
                double tmp2 = (c1 * a2) - (c2 * a1);
                double y = tmp2 / tmp1;
                double x = (c1 - (b1 * y)) / (double)a1;
	        if (x < xR && x > xL) {
		    // {I-, the index of rxNeg, x position}
		    vector<double> tmp{-1, (double) counter, x};
		    rx.push_back(tmp);
		    // {record the index of two intersect lines}
		    vector<int> indexTmp{i, index};
		    rxNeg.push_back(indexTmp);
		    counter ++;
		}
		else if (x >= xR){
		    if (slope1 > slope2) iNeg.erase(iNeg.begin()+i);
		    else iNeg.erase(iNeg.begin()+index);
		    i = i+1;
		    continue;
		}
		else {
		    if (slope1 < slope2) iNeg.erase(iNeg.begin()+i);
		    else iNeg.erase(iNeg.begin()+index);
		    i = i+1;
		    continue;
		}
		i = i+2;
	    }
	}

	if (iPos.size() >= 2) {
	    int counter = 0;
            for (int i = 0; i < iPos.size();) {
	        int index;
	        double a1 = iPos.at(i).a, b1 = iPos.at(i).b, c1 = iPos.at(i).c, slope1 = iPos.at(i).slope, a2, b2, c2, slope2;
	        if ( i == iPos.size() - 1) {
	            a2 = iPos.at(0).a;
	            b2 = iPos.at(0).b;
	            c2 = iPos.at(0).c;
		    slope2 = iPos.at(0).slope;
		    index = 0;
	        }
	        else {
	            a2 = iPos.at(i+1).a;
	            b2 = iPos.at(i+1).b;
	            c2 = iPos.at(i+1).c;
		    slope2 = iPos.at(i+1).slope;
		    index = i+1;
	        }
                double tmp1 = (b1 * a2) - (b2 * a1);
	        if (tmp1 == 0.0) {
		    double y1 = c1 / (double)b1;
		    double y2 = c2 / (double)b2;
		    if (y1 < y2) iPos.erase(iPos.begin()+index);
		    else iPos.erase(iPos.begin()+i);
		    i = i+1;
		    continue;
	        }
                double tmp2 = (c1 * a2) - (c2 * a1);
                double y = tmp2 / tmp1;
                double x = (c1 - (b1 * y)) / (double)a1;
	        if (x < xR && x > xL) {
		    vector<double> tmp{1, (double) counter, x};
		    rx.push_back(tmp);
		    vector<int> indexTmp{i, index};
		    rxPos.push_back(indexTmp);
		    counter++;
		}
		else if (x >= xR){
		    if (slope1 < slope2) iPos.erase(iPos.begin()+i);
		    else iPos.erase(iPos.begin()+index);
		    i = i+1;
		    continue;
		}
		else {
		    if (slope1 > slope2) iPos.erase(iPos.begin()+i);
		    else iPos.erase(iPos.begin()+index);
		    i = i+1;
		    continue;
		}
		i = i+2;
	    }
	}
	// no intersect point or all intersect points are not between xL and xR
	if (rx.size() == 0) continue;

	// find the mediam in rx
        sort(rx.begin(), rx.end(), mySort);
	/*if (rx.size() <= 2) {
	    //xm = (rx.at(0).at(2) + rx.at(rx.size()-1).at(2)) / 2;
	    xm = (xL + xR) / 2;
	}*/
        //else {
	    //sort(rx.begin(), rx.end(), mySort);
	    int m = rx.size() / 2;
	    xm = rx.at(m).at(2);
	//}
	
	// find smin, smax, tmin, tmax, ax, ay, bx, by
	double smin, smax, tmin, tmax, ax = xm, ay = -1 * std::numeric_limits<double>::infinity(), bx = xm, by = std::numeric_limits<double>::infinity();
	for (int i = 0; i < iNeg.size(); i++) { // I- part
	    double tmp = (-1 * iNeg.at(i).a * xm + iNeg.at(i).c) / (double) iNeg.at(i).b;
	    if (tmp > ay + 0.00001) {
	    	ay = tmp;
	    	smin = iNeg.at(i).slope;
	    	smax = iNeg.at(i).slope;
	    }
	    else if (abs(tmp - ay) < 0.00001) {
	        if (smin > iNeg.at(i).slope) smin = iNeg.at(i).slope;
	        if (smax < iNeg.at(i).slope) smax = iNeg.at(i).slope;
	    }
	}
	for (int i = 0; i < iPos.size(); i++) { // I+ part
            double tmp = (-1 * iPos.at(i).a * xm + iPos.at(i).c) / (double) iPos.at(i).b;
	    if (tmp < by - 0.00001 ) {
	    	by = tmp;
	    	tmin = iPos.at(i).slope;
	    	tmax = iPos.at(i).slope;
	    }
	    else if (abs(tmp - by) < 0.00001) {
	        if (tmin > iPos.at(i).slope) tmin = iPos.at(i).slope;
	        if (tmax < iPos.at(i).slope) tmax = iPos.at(i).slope;
	    }
	}
	/*
	// ----------------------- debug ----------------------------
	cout << "ay: " << ay << ", by: " << by << endl;
	cout << "smin: " << smin << ", smax: " << smax << endl;
	cout << "tmin: " << tmin << ", tmax: " << tmax << endl;
	// ----------------------- debug ----------------------------
*/
	// case1 & case4
	if ((ay <= by && smax < 0) || (ay > by && smax < tmin)) {
	    xL = xm;
	    /*
            // prune redundant constraints
	    vector<int> delP, delN;
	    for (int i = 0; i < rx.size(); i++) {
		if (rx.at(i).at(2) <= xm) {
	            if (rx.at(i).at(0) < 0) {  // iNeg
			vector<int> tmp = rxNeg.at(rx.at(i).at(1)); 
			if (iNeg.at(tmp.at(0)).slope < iNeg.at(tmp.at(1)).slope) {  //  prune the one with smaller slope
			    delN.push_back(tmp.at(0));
			}
		        else {  
			    delN.push_back(tmp.at(1));
			}
		    }
		    else {  // iPos
			vector<int> tmp = rxPos.at(rx.at(i).at(1));
			if (iPos.at(tmp.at(0)).slope > iPos.at(tmp.at(1)).slope) {  // prune the one with bigger slope
			    delP.push_back(tmp.at(0));
			}
			else {  
			    delP.push_back(tmp.at(0));
			}
		    }
		}
	    }
            sort(delN.begin(), delN.end());
            reverse(delN.begin(), delN.end());
            sort(delP.begin(), delP.end());
            reverse(delP.begin(), delP.end());
	    for (int i = 0; i < delN.size(); i++) {
		iNeg.at(delN.at(i)) = iNeg.back();
		iNeg.pop_back();
	    }
	    
	    for (int i = 0; i < delP.size(); i++) {
		iPos.at(delP.at(i)) = iPos.back();
		iPos.pop_back();
	    }*/
	}
	// case2 & case5
	else if ((ay <= by && smin > 0) || (ay > by && smin > tmax)) {
	    xR = xm;
	    /*
	    // prune redundant constraints
	    vector<int> delP, delN;
	    for (int i = 0; i < rx.size(); i++) {
		if (rx.at(i).at(2) >= xm) {
		    if (rx.at(i).at(0) < 0) {  // iNeg
			vector<int> tmp = rxNeg.at(rx.at(i).at(1));
			if (iNeg.at(tmp.at(0)).slope > iNeg.at(tmp.at(1)).slope) {  // prune the one with larger slope
			    delN.push_back(tmp.at(0));
			}
		        else {
			    delN.push_back(tmp.at(1));
			}
	            }
		    else {  // iPos
			vector<int> tmp = rxPos.at(rx.at(i).at(1));
			if (iPos.at(tmp.at(0)).slope < iPos.at(tmp.at(1)).slope) {  // prune the one with smaller slope
			    delP.push_back(tmp.at(0));
			}
			else {  
			    delP.push_back(tmp.at(1));
			}
		    }
		}
	    }
            sort(delN.begin(), delN.end());
            reverse(delN.begin(), delN.end());
            sort(delP.begin(), delP.end());
            reverse(delP.begin(), delP.end());
	    for (int i = 0; i < delN.size(); i++) {
		iNeg.at(delN.at(i)) = iNeg.back();
		iNeg.pop_back();
	    }
	    for (int i = 0; i < delP.size(); i++) {
		iPos.at(delP.at(i)) = iPos.back();
		iPos.pop_back();
	    }*/
	}
	// case3
	else if (ay <= by && smin <= 0 && smax >= 0) {
	    // xm is the answer
	    if (ay < 0) {
		ay = ay - 0.5;
		cout << (int)ay << endl;
	    }
	    else {
		ay = ay + 0.5;
		cout << (int)ay << endl;
	    }
	    return;
	}
	// case6
	else if (ay > by && smin <= tmax && smax >= tmin){
	    cout << "NA" << endl;
	    return;
	}
	else {
	    cout << "WTF" << endl;
	}
    }

    // constraints < 2, find the answer directly
    /* 
    // ------------------------ debug --------------------------
    for (int i = 0; i < iNeg.size(); i++) { 
        cout << iNeg.at(i).a << " " << iNeg.at(i).b << " " << iNeg.at(i).c << endl;
    }
    for (int i = 0; i < iPos.size(); i++) { 
        cout << iPos.at(i).a << " " << iPos.at(i).b << " " << iPos.at(i).c << endl;
    }
    // ------------------------ debug --------------------------
    */
    if (iNeg.size() == 0) cout << "-INF" << endl;
    else if (iPos.size() == 0) {
	if (iNeg.size() == 1) {  // only one I-
	    if (iNeg.at(0).slope == 0) {
	        double ans = iNeg.at(0).c / (double) iNeg.at(0).b;
		if (ans > 0) cout << (int) (ans + 0.5) << endl;
		else cout << (int) ans - 0.5 << endl;
	    }
	    else if (iNeg.at(0).slope > 0){
                if (xL == INT_MIN) cout << "-INF" << endl;
		else {
		    double ans = (-1 * iNeg.at(0).a * xL + iNeg.at(0).c) / (double) iNeg.at(0).b;
		    if (ans > 0) cout << (int) (ans + 0.5) << endl;
		    else cout << (int) ans - 0.5 << endl;
		}
	    }
	    else {
                if (xR == INT_MAX) cout << "-INF" << endl;
		else {
		    double ans = (-1 * iNeg.at(0).a * xR + iNeg.at(0).c) / (double) iNeg.at(0).b;
		    if (ans > 0) cout << (int) (ans + 0.5) << endl;
		    else cout << (int) ans - 0.5 << endl;
		}
	    }
	}
	else {  // two I-
	    // not parallel
	    if ((iNeg.at(0).slope != iNeg.at(1).slope)) { 
		double interY = (iNeg.at(0).c * iNeg.at(1).a - iNeg.at(1).c * iNeg.at(0).a) / (double) (iNeg.at(0).b * iNeg.at(1).a - iNeg.at(1).b * iNeg.at(0).a);
		double interX = (iNeg.at(0).c - iNeg.at(0).b * interY) / (double) iNeg.at(0).a;
		// xL < intersection < xR
		if (interX <= xR && interX >= xL) {
		    if (iNeg.at(0).slope <= 0 && iNeg.at(1).slope <= 0) {
			if (xR == INT_MAX) cout << "-INF" << endl;
			else if(iNeg.at(0).slope > iNeg.at(1).slope) {
		            double ans = (-1 * iNeg.at(0).a * xR + iNeg.at(0).c) / (double) iNeg.at(0).b;
		            if (ans > 0) cout << (int) (ans + 0.5) << endl;
		            else cout << (int) (ans - 0.5) << endl;
		        }
		        else {
		            double ans = (-1 * iNeg.at(1).a * xR + iNeg.at(1).c) / (double) iNeg.at(1).b;
		            if (ans > 0) cout << (int) (ans + 0.5) << endl;
		            else cout << (int) (ans - 0.5) << endl;
		        }
		    }
		    else if (iNeg.at(0).slope >= 0 && iNeg.at(1).slope >= 0) {
			cout << "xL: " << xL << endl;
			if (xL == INT_MIN) cout << "-INF" <<endl;
			else if(iNeg.at(0).slope < iNeg.at(1).slope) {
		            double ans = (-1 * iNeg.at(0).a * xL + iNeg.at(0).c) / (double) iNeg.at(0).b;
		            if (ans > 0) cout << (int) (ans + 0.5) << endl;
		            else cout << (int) (ans - 0.5) << endl;
		        }
		        else {
		            double ans = (-1 * iNeg.at(1).a * xL + iNeg.at(1).c) / (double) iNeg.at(1).b;
		            if (ans > 0) cout << (int) (ans + 0.5) << endl;
		            else cout << (int) (ans - 0.5) << endl;
		        }
		    }
		    else {
		        if (interY > 0) cout << (int) (interY + 0.5) << endl;
		        else cout << (int) (interY - 0.5) << endl;
		    }
		}
		// intersection > xR, assume xR < INT_MAX
		else if (interX > xR) {
		    if(iNeg.at(0).slope < iNeg.at(1).slope) {
		        double ans = (-1 * iNeg.at(0).a * xR + iNeg.at(0).c) / (double) iNeg.at(0).b;
		        if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
		    }
		    else {
		        double ans = (-1 * iNeg.at(1).a * xR + iNeg.at(1).c) / (double) iNeg.at(1).b;
		        if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
		    }
		}
		// intersection < xL, assume xL > INT_MIN
                else {
		    if(iNeg.at(0).slope > iNeg.at(1).slope) {
		        double ans = (-1 * iNeg.at(0).a * xL + iNeg.at(0).c) / (double) iNeg.at(0).b;
		        if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
		    }
		    else {
		        double ans = (-1 * iNeg.at(1).a * xL + iNeg.at(1).c) / (double) iNeg.at(1).b;
		        if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
		    }
		}
	    }
	    // parallel
	    else {
		if (iNeg.at(0).slope > 0) {
		    if (xL == INT_MIN) cout << "-INF" << endl;
                    else {
		        double ans1 = (-1 * iNeg.at(0).a * xL + iNeg.at(0).c) / (double) iNeg.at(0).b;
		        double ans2 = (-1 * iNeg.at(1).a * xL + iNeg.at(1).c) / (double) iNeg.at(1).b;
		        double ans;
		        if (ans1 > ans2) ans = ans2;
		        else ans = ans1;
		        if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
                    }
		}
		else if (iNeg.at(0).slope == 0) {
		    double ans = max(iNeg.at(0).c / iNeg.at(0).b, iNeg.at(1).c / iNeg.at(1).b);
		    if (ans > 0) cout << (int) (ans + 0.5) << endl;
		    else cout << (int) ans - 0.5 << endl;
		}
		else {
		    if (xR == INT_MAX) cout << "-INF" << endl;
                    else {
		        double ans1 = (-1 * iNeg.at(0).a * xR + iNeg.at(0).c) / (double) iNeg.at(0).b;
		        double ans2 = (-1 * iNeg.at(1).a * xR + iNeg.at(1).c) / (double) iNeg.at(1).b;
		        double ans;
		        if (ans1 > ans2) ans = ans2;
		        else ans = ans1;
		        if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
                    }
		}
	    }
	}
    }
    else { // one I- and one I+
	// parallel
	if (iNeg.at(0).slope == iPos.at(0).slope) {
	    if (iNeg.at(0).slope > 0) {
		double ans1 = (-1 * iNeg.at(0).a * xL + iNeg.at(0).c) / (double) iNeg.at(0).b;
		double ans2 = (-1 * iPos.at(0).a * xL + iPos.at(0).c) / (double) iPos.at(0).b;
		if (ans1 > ans2) cout << "NA" << endl;
		else {
		    if (xL == INT_MIN) cout << "-INF" << endl;
		    else if (ans1 > 0) cout << (int) (ans1 + 0.5) << endl;
		    else cout << (int) (ans1 - 0.5) << endl;
		}
	    } 
	    else if (iNeg.at(0).slope == 0) {
                double ans1 = iNeg.at(0).c / iNeg.at(0).b;
	        double ans2 = iPos.at(0).c / iPos.at(0).b;
	        if (ans1 > ans2) cout << "NA" << endl;
	        else {
		    if (ans1 > 0) cout << (int) (ans1 + 0.5) << endl;
		    else cout << (int) (ans1 - 0.5) << endl;
                }
	    }	
	    else {
		double ans1 = (-1 * iNeg.at(0).a * xR + iNeg.at(0).c) / (double) iNeg.at(0).b;
		double ans2 = (-1 * iPos.at(0).a * xR + iPos.at(0).c) / (double) iPos.at(0).b;
		if (ans1 > ans2) cout << "NA" << endl;
		else {
		    if (xR == INT_MAX) cout << "-INF" << endl;
		    else if (ans1 > 0) cout << (int) (ans1 + 0.5) << endl;
		    else cout << (int) (ans1 - 0.5) << endl;
		}
	    } 
	}
	// not parallel
	else {
	    double interY = (iNeg.at(0).c * iPos.at(0).a - iPos.at(0).c * iNeg.at(0).a) / (double) (iNeg.at(0).b * iPos.at(0).a - iPos.at(0).b * iNeg.at(0).a);
	    double interX = (iNeg.at(0).c - iNeg.at(0).b * interY) / (double) iNeg.at(0).a;
	    // xL <= interX <= xR
	    if (xL <= interX && interX <= xR) {
		// I- slope > I+ slope
		if (iNeg.at(0).slope > iPos.at(0).slope) {
		    if ((iNeg.at(0).slope < 0 && iPos.at(0).slope < 0) || iNeg.at(0).slope == 0) {
		        if (interY > 0) cout << (int) (interY + 0.5) << endl;
		        else cout << (int) (interY - 0.5) << endl;
		    }
		    else {
		        double ans = (-1 * iNeg.at(0).a * xL - iNeg.at(0).c) / (double) iNeg.at(0).b;
			if (xL == INT_MIN) cout << "-INF" << endl;
			else if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
		    }
		}
		// I- slope < I+ slope
		else {
		    if ((iNeg.at(0).slope > 0 && iPos.at(0).slope > 0) || iNeg.at(0).slope == 0) {
		        if (interY > 0) cout << (int) (interY + 0.5) << endl;
		        else cout << (int) (interY - 0.5) << endl;
		    }
		    else {
		        double ans = (-1 * iNeg.at(0).a * xR - iNeg.at(0).c) / (double) iNeg.at(0).b;
			if (xR == INT_MAX) cout << "-INF" <<endl;
			else if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
		    }
		}
	    }
	    // interX < xL
	    else if (interX < xL) {
		// I- slope > I+ slope
		if (iNeg.at(0).slope > iPos.at(0).slope) cout << "NA" << endl;
		// I- slope < I+ slope
		else {
		    // I- slope < 0
		    if (iNeg.at(0).slope < 0) {
		        double ans = (-1 * iNeg.at(0).a * xR - iNeg.at(0).c) / (double) iNeg.at(0).b;
			if (xR == INT_MAX) cout << "-INF" << endl;
			else if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
		    }
                    // I- slope = 0
                    else if (iNeg.at(0).slope == 0) {
                        double ans = iNeg.at(0).c / (double) iNeg.at(0).b;
			if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
                    }
		    // I- slope > 0
		    else {
		        double ans = (-1 * iNeg.at(0).a * xL - iNeg.at(0).c) / (double) iNeg.at(0).b;
			if (xL == INT_MIN) cout << "-INF" << endl;
			else if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
		    }
		}
	    }
	    // xR < interX
	    else {
		// I- slope < I+ slope
		if (iNeg.at(0).slope < iPos.at(0).slope) cout << "NA" << endl;
		// I- slope > I+ slope
		else {
		    // I- slope < 0
		    if (iNeg.at(0).slope < 0) {
		        double ans = (-1 * iNeg.at(0).a * xR - iNeg.at(0).c) / (double) iNeg.at(0).b;
			if (xR == INT_MAX) cout << "-INF" << endl;
			else if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
		    }
                    // I- slope = 0
                    else if (iNeg.at(0).slope == 0) {
                        double ans = iNeg.at(0).c / (double) iNeg.at(0).b;
			if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
                    }
		    // I- slope > 0
		    else {
		        double ans = (-1 * iNeg.at(0).a * xL - iNeg.at(0).c) / (double) iNeg.at(0).b;
			if (xL == INT_MIN) cout << "-INF" << endl;
			else if (ans > 0) cout << (int) (ans + 0.5) << endl;
		        else cout << (int) (ans - 0.5) << endl;
		    }
		}
	    }
	}
    }
}

int main() {
    int constraintNum;
    cin >> constraintNum;
    vector<int> tmpLine(3, 0);
    vector<Line> constraints(constraintNum);

    for (int i = 0; i < constraintNum; i++) {
	for (int j = 0; j < 3; j++) {
	    int tmp;
	    cin >> tmp;
	    tmpLine.at(j) = tmp;
	}
	Line line(tmpLine.at(0), tmpLine.at(1), tmpLine.at(2));
        constraints.at(i) = line;
    }
    pruneAndSearch(constraints);
}

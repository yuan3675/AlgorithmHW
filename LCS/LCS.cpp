#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stdio.h>

using namespace std;

char input1[100];
char input2[100];
vector<string> result;
int LCS_length;

// find out all LCS
void listAllLCS(int m, int n, int curLen, vector<char> &tmp, vector<char> &vec1, vector<char> &vec2, vector<vector<int>> &table) {
    if (curLen == LCS_length) {
	   string s(tmp.begin(), tmp.end());
	   result.push_back(s);
	   return;
    }
    
    if (m == vec2.size() || n == vec1.size()) return;

    for (int i = m; i < vec2.size(); i++) {
	    for (int j = n; j < vec1.size(); j++) {
		    if (vec1.at(j) == vec2.at(i) && table.at(i+1).at(j+1) == curLen + 1) {
			    tmp.at(curLen) = vec1.at(j);
			    listAllLCS(i+1, j+1, curLen + 1, tmp, vec1, vec2, table);
		    }
	    }
    }
}

// Construct table, find LCS length
void LCS(vector<char> &vec1, vector<char> &vec2, vector<vector<int>> &table) {
    vector<int> row;
    row.assign(vec1.size() + 1, 0);
    table.assign(vec2.size() + 1, row);

    for (int i = 0; i < vec1.size() + 1; i++) table.at(0).at(i) = 0;
    for (int i = 0; i < vec2.size() + 1; i++) table.at(i).at(0) = 0;

    for (int i = 0; i < vec2.size(); i++) {
	    for (int j = 0; j < vec1.size(); j++) {
		    if (vec1.at(j) == vec2.at(i)) {
			    table.at(i+1).at(j+1) = table.at(i).at(j) + 1;
		    }
		    else {
			    table.at(i+1).at(j+1) = max(table.at(i).at(j+1), table.at(i+1).at(j));
		    }
	    }
    }
    LCS_length = table.at(vec2.size()).at(vec1.size());
    printf("%d ", LCS_length);
    vector<char> tmp(LCS_length, 'a');
    listAllLCS(0, 0, 0, tmp, vec1, vec2, table);
}
    


int main() {
    scanf("%s", input1);
    scanf("%s", input2);
   
    vector<char> vec1;
    vector<char> vec2;
    vector<vector<int>> table;
    vec1.assign(input1, input1 + strlen(input1)); 
    vec2.assign(input2, input2 + strlen(input2)); 
    LCS(vec1, vec2, table);
    printf("%lu\n", result.size());
    /*    
    // sort in dictionary order
    for(int i = 0; i < result.size() - 1; i++) {
	    for (int j = i+1; j < result.size(); j++) {
		    if (result.at(i) > result.at(j)) {
			    string tmp = result.at(i);
			    result.at(i) = result.at(j);
			    result.at(j) = tmp;
		    }
	    }
    }
    */
    
    sort(result.begin(), result.end());
    // print out all LCS
    for (int i = 0; i < result.size(); i++) {
	    printf("%s\n", result.at(i).c_str());
    }
    return 0;
}

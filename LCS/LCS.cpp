#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

void LCS(vector<char> vec1, vector<char> vec2) {
    vector<int> row;
    row.assign(vec1.size() + 1, 0);
    vector<vector<int>> table;
    table.assign(vec2.size() + 1, row);

    for (int i = 0; i <= vec1.size(); i++) {
	    table.at(0).at(i) = i;
    }

    for (int i = 0; i <= vec2.size(); i++) {
	    table.at(i).at(0) = i;
    }

    for (int j = 1; j <= vec2.size(); j++) {
        for(int i = 1; i <= vec1.size(); i++) {
	    if (vec1.at(i-1) == vec2.at(j-1)) {
	        table.at(j).at(i) = min(min(table.at(j).at(i-1) + 1, table.at(j-1).at(i) + 1), table.at(j-1).at(i-1) + 0);
	    }
	    else 
	        table.at(j).at(i) = min(min(table.at(j).at(i-1) + 1, table.at(j-1).at(i) + 1), table.at(j-1).at(i-1) + 2);
	}
    }

    cout << (vec1.size() + vec2.size() - table.at(vec2.size()).at(vec1.size()))/2 << endl;
}


int main() {
    char input1[100];
    char input2[100];
    cin >> input1 >> input2;
   
    vector<char> vec1(input1, input1 + strlen(input1)); 
    vector<char> vec2(input2, input2 + strlen(input2)); 
    LCS(vec1, vec2);
    return 0;
}

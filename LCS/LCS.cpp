#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stdio.h>

using namespace std;

// have bugs, needs to be fixed
void listAllLCS(int m, int n, vector<char> vec1, vector<char> vec2, vector<char> result, int length) {
    for (int i = m; i < vec2.size(); i++) {
	    for (int j = n; j < vec1.size(); j++) {
		    if (vec1.at(j) == vec2.at(i)) {
			    result.push_back(vec1.at(j));
			    if (result.size() == length) {
				    for (int k = 0; k < length; k++) {
					    printf("%c", result.at(k));
				    }
				    printf("\n");
				    result.clear();
			    }
			    listAllLCS(i+1, j+1, vec1, vec2, result, length);
		    }
	    }
    }
}

void LCS(vector<char> vec1, vector<char> vec2) {
    vector<int> row;
    row.assign(vec1.size() + 1, 0);
    vector<vector<int>> table;
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
    printf("%d\n", table.at(vec2.size()).at(vec1.size()));
    vector<char> result;
    listAllLCS(0, 0, vec1, vec2, result, table.at(vec2.size()).at(vec1.size()));
}
    


int main() {
    char input1[100];
    char input2[100];
    scanf("%s", input1);
    scanf("%s", input2);
   
    vector<char> vec1(input1, input1 + strlen(input1)); 
    vector<char> vec2(input2, input2 + strlen(input2)); 
    LCS(vec1, vec2);
    return 0;
}

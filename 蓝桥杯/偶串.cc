#include <iostream>
#include <vector>
using namespace std;
int main() {
    string input;
    cin >> input;
    vector<int> arr(26, 0);
    for (int i = 0; i < input.size(); i++) {
        if (arr[input[i] - 'a'] == 0) {
            arr[input[i] - 'a'] = 1;
        } else {
            arr[input[i] - 'a'] = 0;
        }
    }
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 1) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}
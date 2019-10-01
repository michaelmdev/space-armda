#include <iostream>

using namespace std;

bool finder(int *set, int size,  int goal, int n){
    for (int i = 0; i < size; ++i) {
        int copy[size];
        for (int j = 1; j < size; ++j) {
            copy[j - 1] = set[j];
        }
        if (goal - set[i] == 0) {
            return true;
        } else {
            bool end = finder(copy, size - 1, goal - set[i], n);

            // idea сама упростила я не просил, но оно действительно так
            return end;
        }
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    int goal = 0, size = 0, set[n];
    cin >> goal;

    // предфильтрация больших
    for (int i = 0; i < n; ++i) {
        if(arr[i] <= goal){
            set[size] = arr[i];
            ++size;
        }
    }

    bool answer = finder (set, size, goal, n);
    if (answer)
        cout << "yes";
    else
        cout << "no";

    return 0;
}
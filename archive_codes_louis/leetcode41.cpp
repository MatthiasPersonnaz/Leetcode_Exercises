#include <iostream>
#include <vector>

using namespace std;

int smallest_missing(vector<int>& l);

int main (int argc, char *argv[]) {
    vector<int> nums = {-5, 4, 42, 8, 3, -8, 0, 6, 7, 2, 1};
    
    /*
    for (int j=1; j<10000; j++) {
        nums.insert(begin(nums), j);
    }
    */

    int sm = smallest_missing(nums);
    cout << "smallest missing is " << sm << endl;

    return 0;
}

int smallest_missing(vector<int>& l) {
    unsigned int len = 0;
    int min, max = l[0];
    bool seen_one = false;
    for (int x: l) {
        len++;
        if (x < min) { min = x; }
        if (x > max) { max = x; }
        if (x == 1)  { seen_one = true; }
    }

    // simple cases
    if (min > 1)   { return 1; }
    if (max < 1)   { return 1; }
    if (!seen_one) { return 1; }

    // pre-processing
    for (int& x: l) {
        if (x < 1)   { x = 1; }
        if (x > len) { x = 1; }
    }

    // processing
    for (int x: l) {
        int idx = abs(x)-1;
        l[idx] = -abs(l[idx]); // flag up
    }
    for (size_t i=0; i<l.size(); i++) {
        if (l[i] > 0) { return i+1; }
    }
    return max+1;
}
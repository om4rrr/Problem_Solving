#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
#define ordered_set tree<pair<int, int>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_multiset tree<int, null_type, less_equal<>, rb_tree_tag, tree_order_statistics_node_update>

void fileIO() {

#ifndef ONLINE_JUDGE

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

#endif

}

void fastIO() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

}

void solve() {

    orderedSet A; // declaration

    A.insert(1);
    A.insert(3);
    A.insert(8);
    A.insert(11);

    for(auto it : A) {
        cout << it << ' ';
    }
    cout << '\n';

    cout << A.order_of_key(3) << '\n'; // 1
    cout << A.order_of_key(7) << '\n'; // 2
    cout << A.order_of_key(11) << '\n'; // 3
    cout << A.order_of_key(15) << '\n'; // 4

    cout << (end(A) == A.find_by_order(8))  << '\n'; // true // there is not element on 8th_element


    cout << *A.find_by_order(0) << '\n'; // 1
    cout << *A.find_by_order(1) << '\n'; // 3
    cout << *A.find_by_order(2) << '\n'; // 8
    cout << *A.find_by_order(3) << '\n'; // 11
    cout << *A.find_by_order(5) << '\n'; // 0


    // lower bound -> Lower Bound of X = first element >= X in the set
    cout << *A.lower_bound(6) << '\n';
    cout << *A.lower_bound(2) << '\n';

    // Upper bound -> Upper Bound of X = first element > X in the set
    cout << *A.upper_bound(6) << '\n';
    cout << *A.upper_bound(1) << '\n';


    A.erase(8);
    cout << *A.find_by_order(2) << '\n'; // 11


    for(auto it : A) {
        cout << it << ' ';
    }
    cout << '\n';

}


signed main() {
    fileIO(); fastIO();
    int t = 1; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
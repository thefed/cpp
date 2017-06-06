#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
// given coins {1, 2, 5}, return number of combinations to get amount
int change(int amount, vector<int>& coins) {
    // combinations: dp with time O(nm), space O(n), n is amount
    if (amount == 0) return 1;
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;  // d[2] += d[2 - 2]
    // try all coins
    for (int i = 0; i < coins.size(); i++) {
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    return dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 5;
    assert(change(amount, coins) == 4);
    return 0;
}

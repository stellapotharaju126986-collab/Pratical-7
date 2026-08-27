#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// Struct to hold both the minimum coins count and the actual coins used
struct ChangeResult {
    int minCoins;
    vector<int> coinsUsed;
};

/**
 * Finds the minimum number of coins needed to make the target amount
 * coins: available denominations
 * amount: target value to reach
 */
ChangeResult makeChange(const vector<int>& coins, int amount) {
    // dp[i] stores the minimum coins needed to make amount i
    // Initialize with amount + 1, which acts as an effective infinity
    vector<int> dp(amount + 1, amount + 1);
    
    // parent[i] tracks the coin chosen to reach amount i (for path reconstruction)
    vector<int> parent(amount + 1, -1);
    
    // Base case: 0 coins needed to make an amount of 0
    dp[0] = 0;

    // Iteratively build up solutions for all amounts from 1 to target
    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (i - coin >= 0) {
                // If using this coin yields a smaller total count, update dp
                if (dp[i - coin] + 1 < dp[i]) {
                    dp[i] = dp[i - coin] + 1;
                    parent[i] = coin; // Record the coin used
                }
            }
        }
    }

    // If dp[amount] didn't change, the amount cannot be formed
    if (dp[amount] > amount) {
        return {-1, {}};
    }

    // Reconstruct the exact coins used to form the amount
    vector<int> exactCoins;
    int currentAmount = amount;
    while (currentAmount > 0) {
        int coin = parent[currentAmount];
        exactCoins.push_back(coin);
        currentAmount -= coin;
    }

    return {dp[amount], exactCoins};
}

int main() {
    // Example denominations: 1 cent, 5 cents, 10 cents, 25 cents
    vector<int> coins = {1, 5, 10, 25};
    int targetAmount = 63;

    ChangeResult result = makeChange(coins, targetAmount);

    if (result.minCoins == -1) {
        cout << "It is impossible to make change for " << targetAmount << " with the given coins." << endl;
    } else {
        cout << "Minimum number of coins required: " << result.minCoins << endl;
        cout << "Coins used: ";
        for (size_t i = 0; i < result.coinsUsed.size(); ++i) {
            cout << result.coinsUsed[i] << (i == result.coinsUsed.size() - 1 ? "" : ", ");
        }
        cout << endl;
    }

    return 0;
}

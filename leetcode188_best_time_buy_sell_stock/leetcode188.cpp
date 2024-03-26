#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;






class Solution {
public:
    int maxProfit(int k, vector<int>& prices)
    {
        int l = prices.size();

        if (l == 0 || l == 1) {return 0;}
        if (l == 2) {return Solution::ReLU(prices[1] - prices[0]);}


        vector<int> fronts(l, 0); // upwards fronts (to be computed)
        vector<int> gains;  // list of gains
        vector<int> losses; // list of losses
        vector<int> transactions(l, 0); // transaction indicator

        for (int i; i < l-1; i++) // compute one pass fronts
        {
            fronts[i] = prices[i+1] - prices[i];
        }
        fronts[l-1] = 0; // arbitrarily neutral (outside of known time series, not used anyway)


        // BEGIN TRAVERSAL
        int nb_trans_buy  = 0;
        int nb_trans_sell = 0;
        int pos = 0;
        int last_trans;
        int new_trans;
        int last_price;
        int diff_price;
        
        while (fronts[pos] <= 0)
        {
            pos++; // 
        }
        
        std::cout << "Fronts \n"; 
        for (int x : fronts) {std::cout << x << " ";} std::cout << "\n";
        
        if (pos == l) {return 0;} // if function is constantly non-increasing, stop here and return 0 max gain
        
        transactions[pos] = 1; // otherwise, first positive front, buy
        nb_trans_buy++;
        last_trans = 1;
        last_price = prices[pos];
        
        while (pos <= l-1)
        {
            while (fronts[pos] * last_trans >= 0 && pos < l-1)
            {
                pos++;
            }

            new_trans = -last_trans; 
            diff_price = prices[pos] - last_price;

            if (diff_price > 0) // NE PAS FAIRE SI UNIQUEMENT DES 0 à la fin
            {
                assert(new_trans == -1); // assert we now want to sell at the highest price
                nb_trans_sell++; // record a sell 
                gains.push_back(diff_price); // record the gain
                transactions[pos] = new_trans;
            }
            
            

            if (diff_price <= 0 && pos < l-1) // check if the position is not last
            // if the position is last, don't buy at this point, end of data time series
            {
                assert(new_trans == +1); // assert we now want to buy at the lowest price
                nb_trans_buy++; // record a buy
                losses.push_back(diff_price); // record the loss
                transactions[pos] = new_trans;
            }

            last_price = prices[pos];
            last_trans = new_trans;
            pos++;
        }
        std::cout << "Transactions \n";
        for (int x : transactions) {std::cout << x << " ";} std::cout << "\n";

        // at this point the # of buys and sells is necessarily equal because
        // - we started with a Buy and
        // - we ended with a Sell

        assert(nb_trans_buy == nb_trans_sell);

        // then, operate verification of constraints
        auto total_gains = std::accumulate(gains.begin(), gains.end(), 0);
        
        if (nb_trans_buy < k && nb_trans_sell < k)
        {
            return total_gains;
        }
        else
        {
            std::cout << "Losses \n";
            for (int x : losses) {std::cout << x << " ";} std::cout << "\n";
            std::sort(losses.begin(), losses.end());
            // losses is now sorted
            int res = 0;
            while (nb_trans_buy > k)
            {
                total_gains += losses[res]; // decrease by the smallest loss and so on
                res++;
                nb_trans_buy--;

            }
        }
        return total_gains;
    }

    int ReLU(int u)
    {
        return std::max(0, u);
    }
};



int main()
{
    Solution sol; 
    vector<int> prices = {3,2,6,5,0,3};
    std::cout << "Prices \n";
    for (int x : prices) {std::cout << x << " ";} std::cout << "\n";
    int max_profit = sol.maxProfit(1, prices);
    std::cout << "Max_profit: " << max_profit << "\n";
    return 0;
}

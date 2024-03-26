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
        fronts[l-1] = 0; // prices[l] set to arbitrarily constant (outside of known time series, not used anyway)


        // BEGIN TRAVERSAL
        int nb_trans_buy  = 0;
        int nb_trans_sell = 0;
        int pos = 0;
        int last_trans; // contains either +1 (buy) of -1 (sell)
        int new_trans;
        int last_trans_price; // price of the stock at the last transaction
        int diff_price;
        
        // First step forward till the first rising front appears
        while (fronts[pos] <= 0)
        {
            pos++;
        }
        std::cout << "Position of 1st rising front: pos[" << pos << "] = " << prices[pos] << std::endl;
        if (pos == l) {return 0;} // if function is constantly non-increasing, stop here and return 0 max gain
        
        // First buy transaction
        transactions[pos] = 1; // otherwise, first positive front, buy
        nb_trans_buy++;
        last_trans = 1;
        last_trans_price = prices[pos]; // price of the last transaction
        std::cout << " * bought first at pos[" << pos << "]" << " for that price." << std::endl;
        
        std::cout << "- started traverse at pos[" << pos << "] = " << prices[pos] << std::endl;

        // Then iterate forward to sell and buy
        while (pos <= l-1)
        {
            // Step forward as far as the stock varies monotonically (i.e. either increases or decreases)
            while (fronts[pos] * last_trans >= 0 && pos < l-1)
            // while the variation is opposite to last transaction (ex last_trans = bought +1 and front >= 0 increases)
            {
                pos++; // step forward
            }
            std::cout << "- stopped traverse at pos[" << pos << "] = " << prices[pos] << std::endl;

            new_trans = -last_trans; // if last bought, then sell || if last sold, then buy
            diff_price = prices[pos] - last_trans_price;
            // stock price difference between the two turning points,
            // that is, over the course of the single subtimeline where the price was monotonically varying

            if (diff_price > 0) // NE PAS FAIRE SI UNIQUEMENT DES 0 à la fin
            {
                assert(new_trans == -1); // assert we now want to sell at the highest price
                nb_trans_sell++; // record a sell 
                gains.push_back(diff_price); // record the gain for later constraints
                transactions[pos] = new_trans;
                std::cout << "  * sold   at pos[" << pos << "]. Gain over period = " << diff_price << ".\n" << std::endl;
            }
            
            

            if (diff_price <= 0 && pos < l-1) // check if the position is not the last
            // because if the position is last, don't buy at this point, end of data time series
            {
                assert(new_trans == 1); // assert we now want to buy at the lowest price
                nb_trans_buy++; // record a buy
                losses.push_back(diff_price); // record the loss for later constraints
                transactions[pos] = new_trans;
                std::cout << "  * bought at pos[" << pos << "]. Loss over pediod = " << diff_price << "." << std::endl;
            }

            last_trans_price = prices[pos];
            last_trans = new_trans;


            std::cout << "- started traverse at pos[" << pos << "] = " << prices[pos] << std::endl;
            pos++;

            
        }

        // at this point the number of buys and sells is necessarily equal because
        // * we started with a Buy and
        // * we ended with a Sell
        // * the transactions alternate

        assert(nb_trans_buy == nb_trans_sell);

        // then, operate verification of constraints
        auto total_gains = std::reduce(gains.begin(), gains.end());
        std::cout << "TOTAL GAINS = " << total_gains << std::endl;
        
        
        if (nb_trans_buy < k && nb_trans_sell < k)
        {
            return total_gains;
        }
        else // if constraints are not met, there are either too much Buys or Sells
        {
            // First let's build a list of all fronts: losses and gains
            // At this point there should be no losses taken into account in the build of our strategy
            // But to cut down the number of transactions, we will merge some transaction
            // We still want to maximize our gains so let's register gradually the smallest losses possible 
            // by deleting transactions, until the criterion is met.
            // Don't forget that registered gains from positive fronts can also be deleted.
            // We count them as misses to win.
            // So let's buiild the list of losses and negative gains (misses to win) before we order the list.  
            std::vector<int> additional_negative_transactions(gains); // list the transactions
            for (int& gain : additional_negative_transactions) {gain = -gain;}

            additional_negative_transactions.insert( additional_negative_transactions.end(), losses.begin(), losses.end() );
            std::sort(additional_negative_transactions.begin(), additional_negative_transactions.end());
            std::reverse(additional_negative_transactions.begin(),additional_negative_transactions.end());
            // losses is now sorted
            int res = 0;
            while (nb_trans_buy > k)
            {
                total_gains += additional_negative_transactions[res]; // decrease by the smallest loss and so on (elements are negative)
                std::cout << "deleted one transaction pair and gained " << additional_negative_transactions[res] << std::endl;         
                res++;
                nb_trans_buy--; // this is arbitrary, even if we deleted a sell transaction, since they stand equivalent at this point
                // in the function

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
    vector<int> prices = {3,2,6,5,0,3,4,9,9,10,2,18,17,4,15};
    std::cout << "Prices = [";
    for (int x : prices) {std::cout << x << " ";} std::cout << "]\n\n";
    int max_profit = sol.maxProfit(2, prices);
    std::cout << "Max_profit: " << max_profit << "\n";
    return 0;
}

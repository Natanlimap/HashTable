#include <iterator>             // std::begin(), std::end()
#include <functional>           // std::function
#include <algorithm>            // std::min_element
#include <array>
#include <map>
#include "../include/hashtbl.h"   // header file for tested functions
#include "../include/account.h"  // To get the account class
#include <cassert>



int main(){
    /// This is the hash table we use in the tests.
    ac::HashTbl< Account::AcctKey, Account, KeyHash, KeyEqual > ht_accounts{ 4 };
    assert(ht_accounts.empty());
    assert(ht_accounts.size() == 0);
    // assert(ht_accounts.insert())
}
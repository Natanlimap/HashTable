#include <iterator>             // std::begin(), std::end()
#include <functional>           // std::function
#include <algorithm>            // std::min_element
#include <array>
#include <map>
#include "../include/hashtbl.h"   // header file for tested functions
#include "../include/account.h"  // To get the account class
#include <cassert>
#include "../include/fruit.h"



int main(){
    /// This is the hash table we use in the tests.
   std::array<Fruit, 12> m_accounts;
    ac::HashTbl< std::string, Fruit, FruitHash, FruitEqual > ht_fruit{ 12 };
    assert(ht_fruit.empty());
    assert(ht_fruit.size() == 0);
     ht_fruit.insert("morango", Fruit( "morang", 10, 30 ));
    ht_fruit.insert("morango", Fruit( "morango", 100, 33 ));
      ht_fruit.insert("banana", Fruit( "banana", 99, 666 ));
       ht_fruit.insert("amora", Fruit( "amora", 99, 666 ));
     ht_fruit.insert("uva", Fruit( "uva", 1, 6 ));
     std::cout << ht_fruit;
     ht_fruit.clear();
     std::cout << ht_fruit;

}
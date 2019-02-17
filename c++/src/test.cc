/**
 * @file main.cc
 * @brief Main file for the exam, tests the functionalities of the BSTree class.
 * 
 * @author Amadio Simone, Indri Patrick
 * 
 * @date 1/2/23
 */

#include <memory>
#include"BST.h"


// Const function to call const[] operator
template<typename K, typename T, typename C>
const T& BSTree<K,T,C>::square_bracket_test(const K& key) const{
  return (*this)[key];
}


// Custom key, requires a compare function object to be used as a BSTree key
struct CustomKey_explicit {
  int one, two, three;
};

struct compareh {
   bool operator()(CustomKey_explicit bingo, CustomKey_explicit bango) const {
        return bingo.two < bango.two;
   }
};

// Test struct that contains three number, to be used as key.
// The ordering should be done comparing the 'two' variable.
// Since std::less<K> is uses the overloaded operator to make comparisons,
// there is no need to explicitely define a custom comparison function.
struct CustomKey {
  int one, two, three;
  bool operator<(CustomKey other) const {
    return two < other.two;
  }
};


// Overloading operator<< in order to easily print CustomKey
std::ostream& operator<<(std::ostream& os, const CustomKey& k) {
    os << k.one << ", " <<k.two<< ", "<<k.three;
  return os;
}



int main() {

  try{

    auto tree = BSTree<int,int>();

    // BSTree building, passing both by rvalue (numbers) and lvalues (variables)
    // using both std::pair and a pair key/value
    
    auto pair_insert=std::make_pair<int,int>(8,8);

    tree.insert(pair_insert);
    tree.insert(3,3);

    //the BSTree<int,int> will automatic cast from const int to int
    const int a = 1;
    int b = 10;

    tree.insert(a,a);
    tree.insert(b,b);
    tree.insert(6,6);
    tree.insert(4,4);
    tree.insert(7,7);
    tree.insert(14,14);
    tree.insert(13,13);
    
    std::cout << "Trying to add an already present key" << std::endl;
    tree.insert(1,1);
  
    std::cout << "\nPrinting the BSTree" << std::endl;
    std::cout << tree <<std::endl;  // Overloading of operator<<

    std::cout << "\nGetting the size of tree" << std::endl;
    std::cout<< tree.size_of() << std::endl;

    std::cout << "\nBalancing tree" << std::endl;
    tree.balance();
    

    // Copy constructor
    std::cout << "\nPrinting tree and copy tree constructed with copy ctor, they're equal" << std::endl;
    BSTree<int,int> test_copy{tree};
    test_copy.print();
    std::cout<<"Using == operator for trees"<<std::endl;
    std::cout<< std::boolalpha<< (test_copy==tree) <<std::endl;

    // Custom key testing
    std::cout << "\nTesting BSTree with custom keys" << std::endl;
    auto tree1 = BSTree<CustomKey, int>(CustomKey{0,8,41}, 8); // Testing ctor
    tree1.insert(CustomKey{11,3,51}, 3);
    tree1.insert(CustomKey{13,10,1}, 10);
    tree1.insert(CustomKey{21,6,17}, 6);
    tree1.insert(CustomKey{1,4,18}, 4);
    tree1.insert(CustomKey{1,5,18}, 10);
    tree1.insert(CustomKey{1,4,18}, 72); // Inserting identicals
    

    std::cout << "\nPrinting tree using custom key, with operator < overloading" << std::endl;
    for (auto it=tree1.cbegin();it!=tree1.cend();++it) {
      std::cout << (*it).first.two << ": " << (*it).second << std::endl;
    }

    // Testing find() for custom keys
    auto pair=*(tree1.find(CustomKey{0,8,41}));

    std::cout << "\nFinding 0 8 41, expecting 8 as output. Get: " << pair.second << std::endl;
    
    auto key = CustomKey{1,8,51};
    
    auto pair2=*(tree1.find(key));

    std::cout << "Finding 1 8 51, expecting 8 as output? Get: " << pair2.second << std::endl;


    // Is this a problem of coding? Not really: the user gave a "not biective" key: if u use for example the sum of all 
    // the three int of the keys as criteria, you'd have the same problem between (1 3 5) and (3 3 3).
    // Even though they're different keys, in the order given they're the same. It's user responsability to give a proper
    // order. So I think we're actually fine, but it's something to be aware of.
    
    std::cout << "Finding 1 8 51 with [], expecting 8 as output. Get: " << tree1[key] << std::endl;
    
    std::cout << "Finding 1 8 51 with const [], expecting 8 as output. Get: \n" << tree1.square_bracket_test(key) << std::endl;
    

    std::cout << "\nTesting copy constructor for custom keys" << std::endl;
    BSTree<CustomKey, int> tree2{tree1};

    std::cout << "\ntree2 copy ctor from previous \n" << tree2 << std::endl;
    std::cout<<"Using == operator for trees"<<std::endl;
    std::cout<< std::boolalpha<< (tree2==tree1) <<std::endl;

    tree2.clear(); //clear test for custom class

    // Testing exception handling: printing an empty tree
    // std::cout<<"tree2 empty "<<tree2<<std::endl;  // Error works

    tree2 = tree1;
    std::cout << "tree2 copy assign from previous \n" << tree2 << std::endl;
    std::cout<<"Using == operator for trees"<<std::endl;
    std::cout<< std::boolalpha<< (tree2==tree1) <<std::endl;

    BSTree<CustomKey, int> tree3{std::move(tree2)}; // Move ctor
    tree2 = std::move(tree1); // Move assign
    
    

    // the following works too, it requires the functor compareh()
    // if compareh() is omitted, the code does not compile

    /*
    auto tree2 = BSTree<CustomKey_explicit, int, compareh>();
    tree2.insert(CustomKey_explicit{0,8,41}, 8);
    tree2.insert(CustomKey_explicit{11,3,51}, 3);
    tree2.insert(CustomKey_explicit{13,10,1}, 10);
    tree2.insert(CustomKey_explicit{21,6,17}, 6);
    tree2.insert(CustomKey_explicit{1,4,18}, 4);


    std::cout<<"Printing tree using custom key, functor"<<std::endl;
    for (auto it=tree2.cbegin();it!=tree2.cend();++it) {
      std::cout<<(*it).first.two<<": "<<(*it).second<<std::endl;
      }
    */
    
  } catch(const error& e) {
    std::cerr<<"Exception encountered: "<< e.message<<std::endl;
    return 1;
  }


}

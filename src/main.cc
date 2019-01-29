/**
 * @file main.cc
 * @brief main file for the exam
 * 
 * @author William WIlson
 * 
 * @date 1/2/23
 */

#include <memory>
#include"BST.h"
// Here all the testing will be done


//const function to call const[] operator
template<typename K, typename T, typename C>
const T& BSTree<K,T,C>::square_bracket_test(const K& key) const{
  return (*this)[key];
}


    struct RandomKey_explicit {
      int one, two, three;
    };

    struct compareh {
      bool operator()(RandomKey_explicit bingo, RandomKey_explicit bango) const {
        return bingo.two < bango.two;
      }
    };



int main() {
  
  std::cout<<"at least it starts"<<std::endl;

/*    const int a =1;

    auto tree = BSTree<int,int>();


    tree.insert(8,8);
    tree.insert(3,3);
    tree.insert(a,a);
    tree.insert(10,10);
    tree.insert(6,6);
    tree.insert(4,4);
    tree.insert(7,7);
    tree.insert(14,14);
    tree.insert(13,13);
    tree.insert(1,1);
  
    tree.print();
    std::cout<<"Balancing time"<<std::endl;
    tree.balance();
  
    tree.print();


    BSTree<int,int> test_copy{tree};
    test_copy.print();

*/
    // test struct that contains three number, to be used as key.
    // the ordering should be done comparing the 'two' variable
    // apparently it works, as if std::less<K> is using the overloaded operator
    // which is not really expected (but welcomed)
    // ergo: there is no need to explicitely define a custom comparison function
    struct RandomKey {
      int one, two, three;
      bool operator<(RandomKey other) const {
        return two < other.two;
      }
    };

    auto tree1 = BSTree<RandomKey, int>();
    tree1.insert(RandomKey{0,8,41}, 8);
    tree1.insert(RandomKey{11,3,51}, 3);
    tree1.insert(RandomKey{13,10,1}, 10);
    tree1.insert(RandomKey{21,6,17}, 6);
    tree1.insert(RandomKey{1,4,18}, 4);
    tree1.insert(RandomKey{1,5,18}, 10);
    tree1.insert(RandomKey{1,4,18}, 72); //inserting identicals
    

    std::cout<<"Printing tree using custom key, with operator< overloading"<<std::endl;
    for (auto it=tree1.cbegin();it!=tree1.cend();++it) {
      std::cout<<(*it).first.two<<": "<<(*it).second<<std::endl;
    }

    //find test:
    auto pair=*(tree1.find(RandomKey{0,8,41}));

    std::cout<<"finding 0 8 41, expecting 8 as output. Get: " << pair.second <<std::endl;
    
    auto pair2=*(tree1.find(RandomKey{1,8,51}));

    std::cout<<"finding 1 8 51, expecting 8 as output? Get: " << pair2.second <<std::endl;


    //Is this a problem of coding? Not really: the user gave a "not biective" key: if u use for example the sum of all 
    //the three int of the keys as criteria, you'd have the same problem between (1 3 5) and (3 3 3).
    //Even though they're different keys, in the order given they're the same. In reverse: If we
    //said that the keys are equal if and only if all the elements are equal, how should we append a node
    // node with the same second element as a previous? It's user responsability to give a proper order
    //So I think we're actually fine, but it's something to be aware of.
    
    
    // this works too, it requires the functor compareh()
    // if compareh() is omitted, the code does not compile
    // here an error message would be good, since in this case the
    // compiler gets quite verbose and quite uninformative. I do not think
    // handling exceptions is easy, because the use of the functor is not 
    // required if the struct used as key overloads the operator<

/*    auto tree2 = BSTree<RandomKey_explicit, int, compareh>();
    tree2.insert(RandomKey_explicit{0,8,41}, 8);
    tree2.insert(RandomKey_explicit{11,3,51}, 3);
    tree2.insert(RandomKey_explicit{13,10,1}, 10);
    tree2.insert(RandomKey_explicit{21,6,17}, 6);
    tree2.insert(RandomKey_explicit{1,4,18}, 4);


    std::cout<<"Printing tree using custom key, functor"<<std::endl;
    for (auto it=tree2.cbegin();it!=tree2.cend();++it) {
      std::cout<<(*it).first.two<<": "<<(*it).second<<std::endl;
    }*/


}

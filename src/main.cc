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

    const int a =1;

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


    std::cout<<"Printing tree using custom key, with operator< overloading"<<std::endl;
    for (auto it=tree1.cbegin();it!=tree1.cend();++it) {
      std::cout<<(*it).first.two<<": "<<(*it).second<<std::endl;
    }




    // this works too, it requires the functor compareh()
    // if compareh() is omitted, the code does not compile
    // here an error message would be good, since in this case the
    // compiler gets quite verbose and quite uninformative. I do not think
    // handling exceptions is easy, because the use of the functor is not 
    // required if the struct used as key overloads the operator<

    auto tree2 = BSTree<RandomKey_explicit, int, compareh>();
    tree2.insert(RandomKey_explicit{0,8,41}, 8);
    tree2.insert(RandomKey_explicit{11,3,51}, 3);
    tree2.insert(RandomKey_explicit{13,10,1}, 10);
    tree2.insert(RandomKey_explicit{21,6,17}, 6);
    tree2.insert(RandomKey_explicit{1,4,18}, 4);


    std::cout<<"Printing tree using custom key, functor"<<std::endl;
    for (auto it=tree2.cbegin();it!=tree2.cend();++it) {
      std::cout<<(*it).first.two<<": "<<(*it).second<<std::endl;
    }


}

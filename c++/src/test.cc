/**
 * @file main.cc
 * @brief main file for the exam
 * 
 * @author Amadio Simone, Indri Patrick
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


struct CustomKey_explicit {
  int one, two, three;
};

struct compareh {
   bool operator()(CustomKey_explicit bingo, CustomKey_explicit bango) const {
        return bingo.two < bango.two;
   }
};

    // test struct that contains three number, to be used as key.
    // the ordering should be done comparing the 'two' variable
    // apparently it works, as if std::less<K> is using the overloaded operator
    // which is not really expected (but welcomed)
    // ergo: there is no need to explicitely define a custom comparison function
    struct CustomKey {
      int one, two, three;
      bool operator<(CustomKey other) const {
        return two < other.two;
      }
    };


//in order to do cout simply on CustomKey

std::ostream& operator<<(std::ostream& os, const CustomKey& k) {

    os << k.one << ", " <<k.two<< ", "<<k.three;
    
  return os;
  }


int main() {

try{
  
    //the BSTree<int,int> will automatic cast from const int to int
    const int a =1;

    auto tree = BSTree<int,int>();

    auto pair_insert=std::make_pair<int,int>(8,8);
    //passing both by rvalue (numbers) and lvalues (variables)
    tree.insert(pair_insert);
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
    std::cout<<"Balancing tree"<<std::endl;
    tree.balance();
    
    std::cout<<"Printing tree and copy tree, they're equal"<<std::endl;
    tree.print();

    //copy constructor
    BSTree<int,int> test_copy{tree};
    test_copy.print();

    //tree with custom class as key
    auto tree1 = BSTree<CustomKey, int>();
    tree1.insert(CustomKey{0,8,41}, 8);
    tree1.insert(CustomKey{11,3,51}, 3);
    tree1.insert(CustomKey{13,10,1}, 10);
    tree1.insert(CustomKey{21,6,17}, 6);
    tree1.insert(CustomKey{1,4,18}, 4);
    tree1.insert(CustomKey{1,5,18}, 10);
    tree1.insert(CustomKey{1,4,18}, 72); //inserting identicals
    

    std::cout<<"Printing tree using custom key, with operator < overloading"<<std::endl;
    for (auto it=tree1.cbegin();it!=tree1.cend();++it) {
      std::cout<<(*it).first.two<<": "<<(*it).second<<std::endl;
    }

    //find test: find works
    auto pair=*(tree1.find(CustomKey{0,8,41}));

    std::cout<<"finding 0 8 41, expecting 8 as output. Get: " << pair.second <<std::endl;
    
    auto key=CustomKey{1,8,51};
    
    auto pair2=*(tree1.find(key));

    std::cout<<"finding 1 8 51, expecting 8 as output? Get: " << pair2.second <<std::endl;


    //Is this a problem of coding? Not really: the user gave a "not biective" key: if u use for example the sum of all 
    //the three int of the keys as criteria, you'd have the same problem between (1 3 5) and (3 3 3).
    //Even though they're different keys, in the order given they're the same. In reverse: If we
    //said that the keys are equal if and only if all the elements are equal, how should we append a node
    // node with the same second element as a previous? It's user responsability to give a proper order
    // So I think we're actually fine, but it's something to be aware of.
    
    std::cout<<"finding 1 8 51 with [], expecting 8 as output. Get: " << tree1[key] <<std::endl;
    
    std::cout<<"finding 1 8 51 with const [], expecting 8 as output. Get: \n" << tree1.square_bracket_test(key) <<std::endl;
    
    BSTree<CustomKey, int> tree2{tree1}; //copy ctor for custom class
    std::cout<<"tree2 copy ctor from previous \n"<<tree2<<std::endl;
    tree2.clear(); //clear test for custom class
//    std::cout<<"tree2 empty "<<tree2<<std::endl;  //error works
    tree2=tree1;
    std::cout<<"tree2 copy assign from previous \n"<<tree2<<std::endl;	//using putto overloaded
    BSTree<CustomKey, int> tree3{std::move(tree2)}; //move ctor
    tree2=std::move(tree1); //move assign
    
    // the following works too, it requires the functor compareh()
    // if compareh() is omitted, the code does not compile

/*    auto tree2 = BSTree<CustomKey_explicit, int, compareh>();
    tree2.insert(CustomKey_explicit{0,8,41}, 8);
    tree2.insert(CustomKey_explicit{11,3,51}, 3);
    tree2.insert(CustomKey_explicit{13,10,1}, 10);
    tree2.insert(CustomKey_explicit{21,6,17}, 6);
    tree2.insert(CustomKey_explicit{1,4,18}, 4);


    std::cout<<"Printing tree using custom key, functor"<<std::endl;
    for (auto it=tree2.cbegin();it!=tree2.cend();++it) {
      std::cout<<(*it).first.two<<": "<<(*it).second<<std::endl;
    }*/
    
    }catch(const error& e){
    std::cerr<<"Exception encountered: "<< e.message<<std::endl;
    return 1;
    }


}

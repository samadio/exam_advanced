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
template<typename K, typename T>
const T& BSTree<K,T>::square_bracket_test(const K& key) const{
  return (*this)[key];
}


int main() {
  try{  
    const int a =1, b=3;
    //  NodeNamespace::BSTNode<int,int> test;

    //  auto test2 = BSTNode<int,int>(a,b);
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


    /*  for(auto& x:tree){			for works
    std::cout<<*x<<std::endl;
    } */
    //  BSTree<int,int> copy_tree{tree};
    //  tree.print();
    //  copy_tree.print();

    /*  std::cout<<"Searching for key 3"<<std::endl;
    auto find_it = tree.position_of(3);
    std::cout<<(*find_it).second<<std::endl;

    std::cout<<"tree print"<<std::endl;
    tree.print();
  
    std::cout<<"cout tree"<<std::endl;
    std::cout<<tree<<std::endl;
    tree.insert(5,5);
    tree.insert(6,6);
    tree.print();
    std::cout<<"Content of key 2 is "<<tree[2]<<std::endl;
    //tree.clear();
  
    //copy=tree;*/
  
    /*  auto newtree{std::move(tree)};
    std::cout<<"test move ctor"<<std::endl;

    tree.print();
    tree.insert(71,71); //works because tree.root==nullptr
    tree.print();
    newtree.print(); //check's fine
    newtree= std::move(tree);
    newtree.print(); //check's fine
    tree.insert(42,42); 
    tree.print();
    */

    //  auto newit = tree.find(3);
    //  std::cout<<(*newit).first<<std::endl;
    // (*newit).first = 223432; // compiler errror, as expected
    //  (*newit).second = 223432; // compiler errror, as expected

    //  tree[3]+=1;
    std::cout<< tree[3]<< std::endl;

    //  newit = tree.find(1212);
 
    auto data = std::make_pair<int,int>(44,44);
    auto test2 = BSTree<int,int>(data);

    test2 = tree;
    test2.print();
    std::cout<<"Tree size "<<tree.size_of()<<std::endl;
    
    test2.clear();
//    test2.square_bracket_test(4);  //error: empty tree

    test2[3]; //it calls the non const [], so inserts a new node
    if(test2.find(a)==tree.end()) std::cout<<"end returned"<<std::endl;

    test2.square_bracket_test(4);  //error:non existent key
    
//    auto err= BSTree<std::string,int>();

//    err.insert("Ciao",2);
//    err.find(2); 		//the compiler stops you either
    
    return 0;
    
    
  } catch(const error& e){
    std::cerr<<"Exception encountered: "<< e.message<<std::endl;
    return 1;
    }

}

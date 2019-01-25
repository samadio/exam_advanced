#ifndef BST_H
#define BST_H

/**
 * @file BST.h
 * @brief BST header file
 * @author Patrick Indri
 * @date 26/12/18
 * 
 * More detailed description of what the file contains/declares/implements.
*/

#include <memory>
#include <utility>
#include <iostream>
#include<map>
#include<vector>

namespace NodeNamespace {

template <typename K, typename T>
class BSTNode {

public:

  std::pair<K, T> content;
  std::unique_ptr<BSTNode> left;
  std::unique_ptr<BSTNode> right;
  BSTNode* parent;
  int insert_order=1;


  BSTNode() {std::cout<<"CIAO"<<std::endl;};

  BSTNode(const K& key, const T& value, BSTNode* _left=nullptr, BSTNode* _right=nullptr, BSTNode* _parent=nullptr) : content{std::make_pair(key, value)}, left{_left}, right{_right}, parent{_parent} {std::cout<<"Constructing Node"<<std::endl;};

  ~BSTNode() noexcept = default;

  bool hasLChild(){ return left!=nullptr; }
  bool hasRChild(){ return right!=nullptr; }

  BSTNode* get_next() {
    auto currNode = this;
    if (currNode -> hasRChild()) {
      currNode = currNode ->right.get();
      while(currNode->left!=nullptr){
        currNode=currNode->left.get();
      }
      return currNode;
    } else {  //if there's no right child
    return currNode -> parent;	}
    }


};

}




template <typename K, typename T>
using BSTNode =  NodeNamespace::BSTNode<K,T>;

template <typename K, typename T>
class BSTree {

  std::unique_ptr<BSTNode<K,T>> root = nullptr;

  public:

  int size = 0;

  BSTree() {std::cout<<"Defalut Tree constructor"<<std::endl;};
  ~BSTree() noexcept=default;
  
  //  copy ctor
  BSTree (const BSTree& t): root{}, size{} {
    std::cout << "copy ctor\n";
    //creating a map with insert order
    std::map<int, std::pair<const K,T>> vine;
    for (auto it=t.cbegin();it!=nullptr;++it){  
      vine.insert(std::pair<int,std::pair<const K,T>>(it.get()->insert_order,*it));
    }
    //inserting nodes in new tree according to insert order
    for(auto it=vine.begin();it!=vine.end();++it){
      (*this).insert(it->second);
//      std::cout<<it->second.first<<std::endl;
    }
 
  }
  
  
  //copy assignments
  
  BSTree& operator=(const BSTree& t){
    this->clear();
    std::cout<<"copy assignement"<<std::endl;
    BSTree temp{t};
    (*this) = std::move(temp);
    return *this;
  }
    
  // default move semantic works good
  BSTree<K,T>(BSTree<K,T>&&) = default;
  BSTree<K,T>&	 operator=(BSTree<K,T>&&) = default;
  
  class Iterator;
  class ConstIterator;
  Iterator begin() { return Iterator{get_most_left(root.get())  }; }
  Iterator end() { return Iterator{nullptr}; }
  
  ConstIterator cbegin() const { return ConstIterator{get_most_left(root.get())  }; }
  ConstIterator cend() const { return ConstIterator{nullptr}; }
  

  void insert(const K& key, const T& value);
  void insert(const std::pair<const K, T>& d);

  Iterator find(const K& key);

  Iterator position_of(const K& key);
  
  void clear();
  
  void print();
  
  void balance();
  void balance(std::vector<std::pair<const K, T>>& vine, const int&  begin, const int& end);
  
  T& operator[](const K& k) ;
  const T& operator[](const K& k) const;

  private:

  //void insert_from(const K& key, const T& value, BSTNode<K,T>* currNode) const;

  BSTNode<K,T>* get_most_left(BSTNode<K,T>* currNode) const; 

};


#include "../src/BST.hpp"

#endif //BST_H

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

namespace NodeNamespace {

template <typename K, typename T>
class BSTNode {

public:

  std::pair<K, T> content;
  std::unique_ptr<BSTNode> left;
  std::unique_ptr<BSTNode> right;
  BSTNode* parent;


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
//        currNode = currNode -> parent;
      //}
//      return currNode -> parent;	}
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
  
  /*copy ctor
  BSTree (const BSTree& t): root{}, size{0} {
  std::cout << "copy ctor\n";
  
  }

  
  
  //copy assignment
  
  BSTree& operator=(BSTree& t) {
    root.reset();
    
  }
  
  BSTree& operator=(const BSTree& t){
    root.reset();
    auto temp= t;
    (*this) = std::move(temp);
    return *this;
  }*/
  
  // default move semantic works good
  BSTree<K,T>(BSTree<K,T>&&) = default;
  BSTree<K,T>&	 operator=(BSTree<K,T>&&) = default;

  //void insert(const K& key, const T& value);
  //void insert( K&& key, T&& value);
  
  class Iterator;
  class ConstIterator;
  Iterator begin() { return Iterator{get_most_left(root.get())  }; }
  Iterator end() { return Iterator{nullptr}; }
  
  ConstIterator cbegin() const { return ConstIterator{get_most_left(root.get())  }; }
  ConstIterator cend() const { return ConstIterator{nullptr}; }
  

  void insert(const K& key, const T& value);

  Iterator find(const K& key);

  Iterator position_of(const K& key);
  
  void clear();
  
  void print();
  
  T& operator[](const K& k) ;
  const T& operator[](const K& k) const;

  private:

  //void insert_from(const K& key, const T& value, BSTNode<K,T>* currNode) const;

  BSTNode<K,T>* get_most_left(BSTNode<K,T>* currNode) const; 

};


#include "../src/BST.hpp"

#endif //BST_H

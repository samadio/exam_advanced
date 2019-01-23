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

  std::pair<const K, const T> content;
  std::unique_ptr<BSTNode> left;
  std::unique_ptr<BSTNode> right;
  BSTNode* parent;


  BSTNode() {std::cout<<"CIAO"<<std::endl;};

  BSTNode(const K& key, const T& value, BSTNode* _left=nullptr, BSTNode* _right=nullptr, BSTNode* _parent=nullptr) : content{std::make_pair(key, value)}, left{_left}, right{_right}, parent{_parent} {std::cout<<"Constructing Node"<<std::endl;};

  ~BSTNode() noexcept = default;

  bool hasLChild(){ return left!=nullptr; }
  bool hasRChild(){ return right!=nullptr; }

  bool isLChild(){ return ( parent && (this == parent -> left.get()) ); }
  bool isRChild(){ return ( parent && (this == parent -> right.get()) ); }

  BSTNode* get_next() { // const iterators are needed
    auto currNode = this;
    if (currNode -> hasRChild()) {
      currNode = currNode ->right.get();
      while (currNode -> hasLChild()) {
        currNode = currNode -> left.get();
      }
      return currNode;
    } else {
      while ( currNode -> isLChild() == false && currNode -> parent != nullptr ) {
        currNode = currNode -> parent;
      }
      return currNode -> parent;
    }
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

  //void insert(const K& key, const T& value);
  //void insert( K&& key, T&& value);
  
  class Iterator;
  class ConstIterator;
  Iterator begin() { return Iterator{get_most_left(root.get())}; }
  Iterator end() { return Iterator{nullptr}; }
  

  void insert(const K& key, const T& value);

  Iterator find(const K& key);

  Iterator position_of(const K& key);
  
  private:

  //void insert_from(const K& key, const T& value, BSTNode<K,T>* currNode) const;

  BSTNode<K,T>* get_most_left(BSTNode<K,T>* currNode) const;





};


#include "../src/BST.hpp"

#endif //BST_H

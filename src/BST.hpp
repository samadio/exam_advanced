/*!
 * 
 *
 * @file BST.cc
 * @brief Here all the fancy classes and things will be implemented
 *
 * @author William Wilson
 *
 * @date 2/2/23
 *
 * Details on the implementation of all the fancy things
	 */

#ifndef BST_HPP
#define BST_HPP

# include "BST.h"


//NODE IMPLEMENTATION



//METHODS FOR BSTREE IMPLEMENTATION

template <typename K, typename T>
using BSTNode =  NodeNamespace::BSTNode<K,T>;



/*
template <typename K, typename T>
void BSTree<K,T>::insert(K&& key, T&& value) {
  if (root == nullptr){
    root.reset(new BSTNode<K,T>{key, value, nullptr, nullptr, nullptr});
    size = 1;
    return;
  } else {
    std::cout<<"Is not root, will add BSTNode, by rvalue ref"<<std::endl;
    insert_from(key, value, root.get());
    size += 1;
  }
}
*/


/*
//must increase size
template <typename K, typename T>
void BSTree<K,T>::insert_from(const K& key, const T& value, BSTNode<K,T>* currNode) const {
  if (key == currNode -> content.first) {
    std::cout << "key already present, nothing happens" << std::endl;
  }
  if (key < currNode -> content.first) {
    if (currNode -> hasLChild()) {
      insert_from(key, value, currNode -> left.get());
    } else {
      currNode -> left.reset( new BSTNode<K,T>(key, value, nullptr, nullptr, currNode));
    }
  }
  if (key > currNode -> content.first) {
    if (currNode -> hasRChild()) {
      insert_from(key, value, currNode -> right.get());
    } else {
      currNode -> right.reset( new BSTNode<K,T>(key, value, nullptr, nullptr, currNode));
    }
  }
}
*/


template <typename K, typename T>
BSTNode<K,T>* BSTree<K,T>::get_most_left(BSTNode<K,T>* currNode) const {
  auto tmp = currNode;
  while (tmp -> left != nullptr) {
    tmp = tmp -> left.get();
  }
  return tmp;
}

template <typename K, typename T>
class BSTree<K,T>::Iterator {

  BSTNode<K,T>* currNode;

  public:
  Iterator(BSTNode<K,T>* n) : currNode{n} {}
  const T& operator*() const {return currNode -> content.second;}


  BSTNode<K,T>* get() { return currNode; }

  Iterator& operator++() {
    currNode = currNode -> get_next();
    return *this;
  }

  bool operator==(const Iterator& other) { return currNode == other.currNode; }
  bool operator!=(const Iterator& other) { return !(*this == other); }

};


template <typename K, typename T>
typename BSTree<K,T>::Iterator BSTree<K,T>::position_of(const K& key) {

  auto currNode = root.get();

  while(currNode){
    if (key < currNode -> content.first) {
      if (currNode -> hasLChild()) {
        currNode = currNode -> left.get();
      } else {
        return Iterator{currNode};
      }
    } else if (key > currNode -> content.first) {
      if (currNode -> hasRChild()) {
        currNode = currNode -> right.get();
      } else {
        return Iterator{currNode};
      }
    } else
      return Iterator{currNode};
  }
  return end(); //for when the tree is empty maybe? probably it serves no purpose

}

template <typename K, typename T>
void BSTree<K,T>::insert(const K& key, const T& value) {

  if (root == nullptr){
    root.reset(new BSTNode<K,T>{key, value, nullptr, nullptr, nullptr});
    size = 1;
    return;
  }

  auto currNode = this -> position_of(key).get();
  
  if (key > currNode -> content.first){
    currNode -> right.reset( new BSTNode<K,T>(key, value, nullptr, nullptr, currNode)); 
    size += 1;
  } else if (key < currNode -> content.first){
    currNode -> left.reset( new BSTNode<K,T>(key, value, nullptr, nullptr, currNode));
    size += 1;
  } else {
    std::cout<<"key already present, nothing happens"<<std::endl;
  }
}


template <typename K, typename T>
typename BSTree<K,T>::Iterator BSTree<K,T>::find(const K& key) {

  auto currNode = this -> position_of(key).get();

  if (root == nullptr || currNode ->content.first != key ) {
    std::cout<<"key not found"<<std::endl;
    return end();
  }

  return Iterator{currNode};

}


#endif

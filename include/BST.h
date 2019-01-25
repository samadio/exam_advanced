#ifndef BST_H
#define BST_H

/**
 * @file BST.h
 * @brief BST header file
 * @author Amadio Simone, Indri Patrick
 * @date 25/01/19
 * 
 * 
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

  std::pair<const K, T> content;
  std::unique_ptr<BSTNode> left;
  std::unique_ptr<BSTNode> right;
  BSTNode* parent;
  int insert_order=1;


  BSTNode() {std::cout<<"CIAO"<<std::endl;};

  BSTNode(const K& key, const T& value, BSTNode* _left=nullptr, BSTNode* _right=nullptr, BSTNode* _parent=nullptr) : content{std::make_pair(key, value)}, left{_left}, right{_right}, parent{_parent} {};

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

/**
 * @class BSTree
 * @breif Binary Search Tree implementation.
 *
 *
 */
template <typename K, typename T>
class BSTree {

  std::unique_ptr<BSTNode<K,T>> root = nullptr;

  public:

  int size = 0;

  BSTree() = default;
  BSTree(const K& key, const T& value) : root{}, size{} {insert(key, value);}
  BSTree(const std::pair<const K, T>& data) : root{}, size{} {insert(data);}
  
  ~BSTree() noexcept=default;
  
  private:
  BSTNode<K,T>* get_most_left(BSTNode<K,T>* currNode) const; 
  

  public:

  //  copy ctor
  BSTree (const BSTree& t) {
    copy_tree(t.get_root());
    std::cout<<"uouooo copiooo"<<std::endl;
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
  BSTree<K,T>& operator=(BSTree<K,T>&&) = default;
  
  /*! BSTree iterator */
  class Iterator;
  /*! BSTree constiterator */
  class ConstIterator;
  /*! 
   * @brief first element for iterating a BSTree.
   * @return iterator to the leftmost node.
   */
  Iterator begin() { return Iterator{get_most_left(root.get())  }; }
  /*! 
   * @brief last element for iterating a BSTree
   * @return iterator to nullptr.
   */
  Iterator end() { return Iterator{nullptr}; }
  

  ConstIterator cbegin() const { return ConstIterator{get_most_left(root.get())  }; }
  ConstIterator cend() const { return ConstIterator{nullptr}; }
  
  //! Inserts a node passing a key and a value separately.
  /*! Calls position_of(key) to find where the node should be appended. If the key
   * is already present, does nothing. Otherwise a new node is created.
   *
   * @param key key entry of the node.
   * @param value content associated to key.
   * @return none
   */
  void insert(const K& key, const T& value);

  //! Inserts a node passing a std::pair<key, value>.
  /*! Separates std::pair and calls insert(key, value).
   *
   * @param d pair of key-value
   * @return none
   */
  void insert(const std::pair<const K, T>& d);

  Iterator find(const K& key) const;

  //! Wipes out the tree.
  /*! 
   * Resets the root to nullptr, causing all the other nodes to be deleted.
   * The tree is left uninitialized, but still usable.
   *
   * @param none
   * @return none
   */
  void clear();
  
  /*! Prints the value in all the nodes, traversing the tree in order.
   *
   * @param none
   * @return none
   */
  void print() const;
  
  //! Balances the tree.
  /*!
   * The tree is linearized into a vector of std::pair<key,value>.
   * Then calls clear() and the auxiliary function balance(vector, begin, end).
   *
   * @param none
   * @return none
   */
  void balance();
  
  /*! Returns the value associated with key if found. Otherwise, appends a node
  * with the desired key and the default value.
  *
  * @param k key to be found/inserted.
  * @return the value associated with the key k.
  */
  T& operator[](const K& k) ;

  // const T& operator[](const K& k) const;

  private:

  //! Auxiliary function for the copy constructor, returns pointer to root node.
  BSTNode<K,T>* get_root() const {return root.get();}

  //! Auxiliary function for the copy constructor.
  void copy_tree(const BSTNode<K,T>* currNode);

  //! Auxiliary function for the insert(key, value) and find(key) methods.
  /*!
   * If the requested key is present, returns and iterator pointing to the node
   * that contains it (exploited by find(key)). Otherwise, it returns an iterator
   * pointing to the node N. The key should be contained in a node inserted as a
   * child of N (exploited by the insert(key,value)).
   *
   * @param key key to be found.
   * @return iterator to node required.
   */
  Iterator position_of(const K& key) const;

  //! Iteratively builds a balanced tree starting from an ordered std::vector
  /*!
   * Builds a balanced tree appending the middle element of the vector,
   * and then iteratively calling itself to append the middle element of the
   * two halves, with begin and end as the extremes of the halves.
   *
   * @param vine std::vector of std::pair<key, value> ordered by key.
   * @param begin index of the first element to be considered.
   * @param end index of the last element to be considered.
   */
  void balance(std::vector<std::pair<const K, T>>& vine, const int&  begin, const int& end);


};


#include "../src/BST.hpp"

#endif //BST_H




  /*
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
    }
  }
 */ 

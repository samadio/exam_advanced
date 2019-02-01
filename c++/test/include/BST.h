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
#include<vector>

namespace NodeNamespace {
template <typename K, typename T> 
class BSTNode {

public:

  std::pair<const K, T> content;
  std::unique_ptr<BSTNode> left;
  std::unique_ptr<BSTNode> right;
  BSTNode* parent;

  /*!
   * @brief BSTNode default constructor.
   */
  BSTNode() = default;

  /*!
   * @brief BSTNode constructor accepting a std::pair<K,T> as input.
   */
  explicit BSTNode(const std::pair<const K, T>& data): content{data} , left{nullptr}, right{nullptr}, parent{nullptr} {};
  
  /*!
   * @brief BSTNode constructor accepting a std::pair<K,T> and a pointer to the 
   * parent node as input.
   */
  BSTNode(const std::pair<const K, T>& data, BSTNode* _parent): content{data} , left{nullptr}, right{nullptr}, parent{_parent} {};


  /*!
   * @brief Sefault BSTNode destructor.
   */
  ~BSTNode() noexcept = default;

  /*!
   * @brief Checks if the node has a left child.
   *
   * @param none
   * @return True if the node has a left child, False otherwise.
   */
  bool hasLChild() const noexcept { return left!=nullptr; }

  /*!
   * @brief Checks if the node has a right child.
   *
   * @param none
   * @return True if the node has a right child, False otherwise.
   */
  bool hasRChild() const noexcept { return right!=nullptr; }

  /*!
   * @brief Returns a pointer to the next node, according to key order.
   *
   * @param none
   * @return Pointer to the next node.
   */
  BSTNode* get_next() noexcept;

};

}



template <typename K, typename T>
using BSTNode =  NodeNamespace::BSTNode<K,T>;

/**
 * @class BSTree
 * @breif Binary Search Tree implementation.
 *
 * Implementation of a Binary Search Tree. The tree is made of nodes which
 * store a key/value pair. It requires a compare structure to order keys.
 * If none is provided, it uses std::less<K>, where K is the key type.
 *
 */
template <typename K, typename T, typename C = std::less<K>>
class BSTree {


  std::unique_ptr<BSTNode<K,T>> root = nullptr;

  int size = 0;

  
  public:

  C compare_f;
  
  /*!
   * @brief Returns the number of elements of the tree.
   *
   * @param none
   * @return const int& Number of elements of the tree.
   */
  const int& size_of() const noexcept {return this -> size;}
 
 /*!
  * @brief Check if the tree is empty.
  *
  * @param none
  * @return True if the tree is empty, false otherwise.
  */ 
  bool is_empty() const noexcept {return (root == nullptr && size == 0);}

  /*!
   * @brief Returns a pointer to the root node. 
   *
   * @param none
   * @return Pointer to root BSTNode.
   */
  const BSTNode<K,T>* get_root() const {return root.get();}

  /*!
   * @brief Default BSTree constructor.
   */
  BSTree() = default;

  /*!
   * @brief BSTree constructor accepting a key and a value, inserted as root.
   */
  BSTree(const K& key, const T& value, C comp = C{}) : root{}, size{}, compare_f{comp} {insert(key, value);}

  /*!
   * @brief BSTree constructor accepting a std::pair<key,value> inserted as root.
   */
  BSTree(const std::pair<const K, T>& data, C comp = C{}) : root{}, size{}, compare_f{comp} {insert(data);}
  
  /*!
   * @brief Default BSTree destructor.
   */
  ~BSTree() noexcept = default;
  

  /*!
   * @brief Copy constructor for a BSTree.
   * Calls the auxiliary function copy_tree() which performs a deep copy
   * of the tree.
   *
   * @param t BSTree to be copied, passed by const reference.
   */
  BSTree (const BSTree& t) {
     std::cout<<"copy constructor"<<std::endl;
     copy_tree(t.root.get());
  }
 
  /*!
   * @brief Copy assignment of a BSTree.
   *
   * @param t the BSTree to be copied.
   * @return The newly copied BSTree.
   */
  BSTree& operator=(const BSTree& t);
  
  /*! @brief Default move constructor for a BSTree. */
  BSTree<K,T,C>(BSTree<K,T,C>&&) noexcept  = default;

  /*! @brief Default move assignment for a BSTree. */
  BSTree<K,T,C>& operator=(BSTree<K,T,C>&&) noexcept = default;
  

  /*! @brief BSTree iterator */
  class Iterator;

  /*! @brief BSTree constiterator */
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

  /*! 
   * @brief first element for iterating a BSTree.
   * @return constiterator to the leftmost node.
   */
  ConstIterator cbegin() const { return ConstIterator{get_most_left(root.get())  }; }
  /*! 
   * @brief last element for iterating a BSTree
   * @return cosntiterator to nullptr.
   */
  ConstIterator cend() const { return ConstIterator{nullptr}; }
  
  /*!
   * @brief Inserts a BSTNode passing a std::pair<key,value>.
   * Calls position_of(key) to find where the node should be appended. If the key
   * is already present, does nothing. Otherwise a new node is created.
   *
   * @param data Pair of key-value.
   * @return bool Boolean which is true if a new node was inserted,
   * false if the key was already present.
   */
  bool insert(const std::pair<const K, T>& data);

  /*!
   * @brief Inserts a node passing a key and a value separately.
   *
   *
   * Key and value are grouped in an std::pair<key, value>, insert() is
   * then called passing the std::pair<key,value>.
   *
   * @param key key entry of the node.
   * @param value content associated to key.
   * @return bool
   */
   bool insert(const K& key, const T& value);

  /*!
   * @brief Returns, if found, an iterator to the node labelled by key.
   *
   * Calls the auxiliary function position_of(key) which returns, if key is found,
   * an iterator pointing to the node that contains key.
   * If the key is not found or the BSTree is empty, retuns a ConstIterator to
   * nullptr.
   *
   * @param key Key to be found.
   * @return Iterator to the node containing the requested key or to nullptr.
   */
  Iterator find(const K& key) const;

  /*! 
   * @brief Wipes out the tree.
   * Resets the root to nullptr, causing all the other nodes to be deleted.
   * The tree is left uninitialized, but still usable.
   *
   * @param none
   * @return none
   */
  void clear() noexcept;
  
  /*! 
   * @brief Prints the value in all the nodes, traversing the tree in order.
   *
   * @param none
   * @return none
   */
  void print() const;
  
  /*!
   * @brief Balances the tree.
   *
   * The tree is linearized into a vector of std::pair<key,value>.
   * Then calls clear() and the auxiliary function balance(vector, begin, end).
   *
   * @param none
   * @return none
   */
  void balance();
  
  /*! 
  * @brief Operator [] to access/insert a BSTNode.
  * Returns the value associated with key if found. Otherwise, appends a node
  * with the desired key and the default value.
  *
  * @param k key to be found/inserted.
  * @return the value associated with the key k.
  */
  T& operator[](const K& k) ;

  const T& operator[](const K& k) const;
  
  /*!
   * @brief Operator << to print a BSTree.
   *
   * Iterates the tree using const iterators and prints "key: value" for each node.
   *
   * @param os OutputStream, where the content of the BSTree should be printed.
   * @param t Const reference to the BSTree to be printed.
   * @return Reference to the OutputStream.
   */


  /*!
  * @brief Test function for const[] operator
  *
  * Trivial function declared as const which calls the const[] operator
  * @param key: key to be searched
  */

  const T& square_bracket_test(const K& key) const;


private:

  /*!
   * @brief Returns a pointer to the leftmost element of a subtree.
   *
   * @param currNode The root node of the subtree to be considered.
   * @return Pointer to the leftmost element.
   */
  BSTNode<K,T>* get_most_left(BSTNode<K,T>* currNode) const noexcept; 

  /*!
   * @brief Auxiliary function for the copy constructor, performs a deep copy.
   *
   * @param currNode Pointer to the root of the subtree to be copied.
   * @return none
   */
  void copy_tree(const BSTNode<K,T>* currNode);

  /*!
   * @brief Auxiliary function for the insert(key, value) and find(key) methods.
   *
   * If the requested key is present, returns and iterator pointing to the node
   * that contains it (exploited by find(key)). Otherwise, it returns an iterator
   * pointing to the node N. The key should be contained in a node inserted as a
   * child of N (exploited by the insert(key,value)).
   *
   * @param key key to be found.
   * @return iterator to node required.
   */
  Iterator position_of(const K& key) const;

  /*!
   * @brief Iteratively builds a balanced tree starting from an ordered std::vector
   *
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


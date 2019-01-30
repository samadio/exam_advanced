/*!
 * 
 *
 * @file BST.cc
 * @brief Here all the fancy classes and things will be implemented
 *
 * @authors Amadio Simone, Patrick Indri
 *
 * @date 24/01/19
 *
 * Details on the implementation of all methods
	 */

#ifndef BST_HPP
#define BST_HPP

# include "BST.h"
#include<typeinfo>
#include<string>
#include<sstream>

//Error handling

struct error{
  std::string message;
  explicit error(const std::string& s) noexcept: message{s} {}
};


// BSTNode implementation

// Public methods

template <typename K, typename T>
NodeNamespace::BSTNode<K,T>* NodeNamespace::BSTNode<K,T>::get_next() noexcept {
  auto currNode = this;
  if (currNode -> hasRChild()) {
    currNode = currNode ->right.get();
    while(currNode->left!=nullptr){
      currNode=currNode->left.get();
    }
    return currNode;
  } else {  //if there's no right child
  return currNode -> parent;
  }
}






// BSTree implementation


// Allows to refer to a BSTNode without its fully qualifing name.
template <typename K, typename T>
using BSTNode =  NodeNamespace::BSTNode<K,T>;



// Subclasses

  template <typename K, typename T, typename C>
  class BSTree<K,T,C>::Iterator {

    BSTNode<K,T>* currNode;

    public:
  
    explicit Iterator(BSTNode<K,T>* n) : currNode{n} {}
    std::pair<const K,T>& operator*() const {return currNode -> content;}


    BSTNode<K,T>* get() { return currNode; } //returns pointer to the node the iterator is on

    Iterator& operator++() noexcept {
      currNode = currNode -> get_next();
      return *this;
    }

    bool operator==(const Iterator& other) const noexcept { return currNode == other.currNode; }
    bool operator!=(const Iterator& other) const noexcept { return !(*this == other); }

  };



  template <typename K,typename T, typename C>
  class BSTree<K,T,C>::ConstIterator : public BSTree<K,T,C>::Iterator {
   
    public:
    
    using parent = BSTree<K,T,C>::Iterator;
    using parent::Iterator;
    
    const std::pair<const K,T>& operator*() const { return parent::operator*(); }
  
  };



// Public methods


  template <typename K, typename T, typename C>
  bool BSTree<K,T,C>::insert(const std::pair<const K, T>& data) {


    if (root == nullptr) {
      root.reset(new BSTNode<K,T>{data});
      size = 1;
      return true;
    }
    
    // find the position where to append
    auto currNode = (this -> position_of(data.first)).get();
    
    if ( compare_f(currNode -> content.first, data.first) ) {
      currNode -> right.reset( new BSTNode<K,T>{data, currNode -> parent}); 
      size += 1;
      return true;
    } else if ( compare_f(data.first, currNode -> content.first) ) {
      currNode -> left.reset( new BSTNode<K,T>{data, currNode});
      size += 1;
      return true;
    } else {
//      std::cout<<"key already present, nothing happens"<<std::endl;
      return false;
    } 

  }


  template<typename K, typename T, typename C>
  bool BSTree<K,T,C>::insert(const K& key, const T& value) {
    std::pair <const K, T> data (key, value);
    return insert(data);
  }


  template <typename K, typename T, typename C>
  typename BSTree<K,T,C>::Iterator BSTree<K,T,C>::find(const K& key) const {
       
    auto currNode = this -> position_of(key).get();
    
    if ( root==nullptr || ( compare_f(key, currNode -> content.first) || compare_f(currNode -> content.first, key) ) ) {
      return cend();
    }
    return Iterator{currNode};
  }


  template <typename K, typename T, typename C>
  void BSTree<K,T,C>::clear() noexcept {
    root.reset();
    size = 0;
//    std::cout<<"Emptying your tree."<<std::endl;
  }


  template <typename K, typename T, typename C>
  void BSTree<K,T,C>::print() const {
    
    std::cout<<*this<<std::endl;
     /*for (auto it=(*this).cbegin(); it!=(*this).cend(); ++it){
      std::cout<<(*it).second<<" ";
    }
    std::cout<<std::endl;
    */
  }


  template <typename K, typename T, typename C>
  void BSTree<K,T,C>::balance(){
    
    //create a vector ordered by key containing all the pairs (key,value)
    std::vector<std::pair<const K,T> > vine;
    
    for(auto it=this->begin();it!=this->end();++it){
      vine.push_back(*it);
    }
    this->clear();
    balance(vine,0,vine.size() -1);
  }
   



// Private methods

  template <typename K, typename T, typename C>
  BSTNode<K,T>* BSTree<K,T,C>::get_most_left(BSTNode<K,T>* currNode) const noexcept {

    auto tmp = currNode;
    
    while (tmp -> left != nullptr) {
      tmp = tmp -> left.get();
    }

    return tmp;
  }


  template <typename K, typename T, typename C>
  void BSTree<K,T,C>::copy_tree(const BSTNode<K,T>* currNode) {
    
    if (currNode != nullptr) {
      insert(currNode -> content);
      copy_tree(currNode -> left.get());
      copy_tree(currNode -> right.get());
    }
  }


//position_of can be called by (find method) on an empty tree, but is not an error because this is managed inside find 
  template <typename K, typename T, typename C>
  typename BSTree<K,T,C>::Iterator BSTree<K,T,C>::position_of(const K& key) const { 
  // need ‘typename’ before ‘BSTree<K, T>::Iterator’ because ‘BSTree<K, T>’ is a dependent scope

    auto currNode = root.get();

    while (currNode) {
      
      if ( compare_f(key, currNode -> content.first) ) {
        if (currNode -> hasLChild()) {
          currNode = currNode -> left.get();
        } else {
          return Iterator{currNode};
        }        
      } else if ( compare_f(currNode -> content.first, key) ) {
        if (currNode -> hasRChild()) {
          currNode = currNode -> right.get();
        } else {
          return Iterator{currNode};
        }
      } else { return Iterator{currNode}; }

    }
    
    return this->cend();
  }


  template <typename K, typename T, typename C>
  void BSTree<K,T,C>::balance(std::vector<std::pair<const K, T>>& vine, const int&  begin, const int& end) {

    if (begin > end) return;

    int median = begin + (end-begin)/2;
    this->insert(vine[median]);
    balance(vine, begin, median-1);
    balance(vine, median+1, end);
  }



// Operators

  template <typename K, typename T, typename C>
  T& BSTree<K,T,C>::operator[](const K& k){
    if(find(k)!=cend())return (*find(k)).second;
    std::cout<<"key not found, inserting new node with content default value"<<std::endl;;
    insert(k,T{});
    return (*find(k)).second;
  }

  
  template <typename K, typename T, typename C>
  const T& BSTree<K,T,C>::operator[](const K& k)const{
    std::cout<<"const [ ]"<<std::endl;
    if (find(k)!=cend()) return (*find(k)).second;
    if (root==nullptr) throw error{"searching for a key in an empty or corrupted tree: root==nullptr"};
    throw error{"searching for a non existent key"};
  }

  
  template <typename K, typename T, typename C>
  std::ostream& operator<<(std::ostream& os, const BSTree<K,T,C>& t) {

    if (t.get_root() == nullptr) throw error{"Printing an empty tree"};    

    for (auto it=t.cbegin();it!=t.cend();++it){
      os << (*it).first << ": " <<(*it).second<< "\n";
    }
  return os;
  }


  template <typename K, typename T, typename C>
  BSTree<K,T,C>& BSTree<K,T,C>::operator=(const BSTree<K,T,C>& t) {
    this -> clear();
    BSTree<K,T,C> temp{t};
    (*this) = std::move(temp);
    return *this;
  }


#endif

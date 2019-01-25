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
  std::pair<const K,T>& operator*() const {return currNode -> content;}


  BSTNode<K,T>* get() { return currNode; } //returns pointer to the node the iterator is on

  Iterator& operator++() {
    currNode = currNode -> get_next();
    return *this;
  }

  bool operator==(const Iterator& other) { return currNode == other.currNode; }
  bool operator!=(const Iterator& other) { return !(*this == other); }

};

template <typename K,typename T>
class BSTree<K,T>::ConstIterator : public BSTree<K,T>::Iterator {
 public:
  using parent = BSTree<K,T>::Iterator;
  using parent::Iterator;
  const std::pair<const K,T>& operator*() const { return parent::operator*(); }
};



template <typename K, typename T>
typename BSTree<K,T>::Iterator BSTree<K,T>::position_of(const K& key) const { // need ‘typename’ before ‘BSTree<K, T>::Iterator’ because ‘BSTree<K, T>’ is a dependent scope

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
    }
     else
      return Iterator{currNode};
  }
  
  std::cout<<"Weird"<<std::endl;
 // return end(); //for when the tree is empty maybe? probably it serves no purpose
  //ERROR HANDLING HERE!
}

template <typename K, typename T>
void BSTree<K,T>::insert(const K& key, const T& value) {

  if (root == nullptr){
    root.reset(new BSTNode<K,T>{key, value, nullptr, nullptr, nullptr});
    size = 1;
    return;
  }

  auto currNode = this -> position_of(key).get();//it's positioned where you need to append 
  
  if (key > currNode -> content.first){
    currNode -> right.reset( new BSTNode<K,T>(key, value, nullptr, nullptr, currNode->parent)); 
    size += 1;
    currNode->right->insert_order=size;
  } else if (key < currNode -> content.first){
    currNode -> left.reset( new BSTNode<K,T>(key, value, nullptr, nullptr, currNode));
    size += 1;
    currNode->left->insert_order=size;
  } else if (key==currNode->content.first){
    std::cout<<"key already present, nothing happens"<<std::endl;
  } else {std::cout<<"PRINT ERROR"<<std::endl;}
}

template <typename K, typename T>
void BSTree<K,T>::insert(const std::pair<const K, T>& d) {
  insert(d.first,d.second);
}


template <typename K, typename T>
typename BSTree<K,T>::Iterator BSTree<K,T>::find(const K& key) const {

  auto currNode = this -> position_of(key).get();

  if (root == nullptr || currNode ->content.first != key ) {
    std::cout<<"key not found"<<std::endl;
    return cend(); //error handling? why cend? No: assignment asks for it
  }

  return Iterator{currNode};

}

template <typename K, typename T>
void BSTree<K,T>::clear(){
  root.reset();
  std::cout<<"Emptying your tree"<<std::endl;
}


template <typename K, typename T>
void BSTree<K,T>::print() const {
   for (auto it=(*this).cbegin(); it!=nullptr; ++it){
    std::cout<<(*it).second<<" ";
  }
  std::cout<<std::endl;
}

template <typename K, typename T>
void BSTree<K,T>::balance(){
  //create a vector ordered by key containing all the pairs (key,value)
  std::vector<std::pair<const K,T> > vine;
  for(auto it=this->begin();it!=this->end();++it){
    vine.push_back(*it);
  }
  this->clear();
  balance(vine,0,vine.size() -1);
}
 
template <typename K, typename T>
void BSTree<K,T>::balance(std::vector<std::pair<const K, T>>& vine, const int&  begin, const int& end){
  if (begin > end) return;
  int median = begin + (end-begin)/2;
  this->insert(vine[median]);
  balance(vine, begin, median-1);
  balance(vine, median+1, end);
}


template <typename K, typename T>
T& BSTree<K,T>::operator[](const K& k){
  std::cout<< " non const quadratno" << std::endl;
  if(find(k)!=end())return (*find(k)).second;
  std::cout<<"no key found, inserting new node with content default value"<<std::endl;;
  insert(k,T{});
  return (*find(k)).second;
}

/*
template <typename K, typename T>
const T& BSTree<K,T>::operator[](const K& k) const{
  std::cout<< "const quadratno" << std::endl;
  if(find(k)!=cend())return (*find(k)).second;
  std::cout<<"no key found, inserting new node with content default value"<<std::endl;;
  insert(k,T{});
  return (*find(k)).second;
}*/


template <typename K, typename T>
std::ostream& operator<<(std::ostream& os, const BSTree<K,T>& t) {

  for (auto it=t.cbegin();it!=nullptr;++it){
    os << (*it).first << ": " <<(*it).second<< "\n";
  }
return os;
}


template <typename K, typename T>
void BSTree<K,T>::copy_tree(const BSTNode<K,T>* currNode) {
  if (currNode != nullptr){
    insert(currNode -> content);
    copy_tree(currNode -> left.get());
    copy_tree(currNode -> right.get());
  }
}

#endif

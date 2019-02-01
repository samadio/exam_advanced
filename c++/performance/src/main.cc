/**
 * @file main.cc
 * @brief main file for the exam
 * 
 * @author William WIlson
 * 
 * @date 1/2/23
 */

#include <memory>
#include <chrono>
#include"BST.h"
#include<map>




int main(int argc, char *argv[]) {

try{
  
  auto tree = BSTree<double, double>();
  std::map<double,double> map;

//  int tree_size = atoi(argv[1]);
  int tree_size = 10000;

  std::cout<<tree_size<<std::endl;
  
  int Ntries=5;

  std::vector<double> key;
  std::vector<double> value;
  auto t0 = std::chrono::high_resolution_clock::now();
  auto t1 = std::chrono::high_resolution_clock::now();

  unsigned int BSTree_time = 0;
  unsigned int BSTree_balanced_time = 0;
  unsigned int map_time = 0;


  for(int k=10000;k<1000000;k = k + 50000){ 
 
    for(int j=0;j<Ntries;j++){    
      for(int i=0;i<k;i++){
      key.push_back(rand()/(double)RAND_MAX);
      value.push_back(rand()/(double)RAND_MAX);

      }
  
      for(int i=0;i<k;i++){
      tree.insert(key[i], value[i]);
      map[key[i]]=value[i];
      }
  
      for(int i=0;i<k;i++){
        t0 = std::chrono::high_resolution_clock::now();
        tree.find(key[i]);
        t1 = std::chrono::high_resolution_clock::now();
        BSTree_time += std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
      }
      
      tree.balance();
  
      for(int i=0;i<k;i++){
        t0= std::chrono::high_resolution_clock::now();
        tree.find(key[i]);
        t1 = std::chrono::high_resolution_clock::now();
        BSTree_balanced_time +=std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
      }
  
      for(int i=0;i<k;i++){
        t0= std::chrono::high_resolution_clock::now();
        map.find(key[i]);
        t1 = std::chrono::high_resolution_clock::now();
        map_time += std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
      }

      tree.clear();
      map.clear();
      value.clear();
      key.clear();
    }    

    std::cout<<k<<"\t"<<BSTree_time/Ntries<<"\t"<<BSTree_balanced_time/Ntries<<"\t"<<map_time/Ntries<<std::endl;
    
  }


}catch(const error& e){
std::cerr<<"Exception encountered: "<< e.message<<std::endl;
return 1;
}


} 

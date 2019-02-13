/**
 * @file main.cc
 * @brief Performance test file for the exam
 * 
 * @author Amadio Simone, Patrick Indri
 * 
 * @date 1/2/23
 */

#include <memory>
#include <chrono>
#include"BST.h"
#include<map>
#include<algorithm>
#include<random>




int main() {

try{
  
  auto tree = BSTree<double, double>();
  std::map<double,double> map;

//  int tree_size = atoi(argv[1]);
//  int tree_size = 10000;

//  std::cout<<tree_size<<std::endl;
  
  int Ntries=5;

  std::vector<double> key;
  std::vector<double> value;
  auto t0 = std::chrono::high_resolution_clock::now();
  auto t1 = std::chrono::high_resolution_clock::now();

  unsigned int BSTree_time = 0;
  unsigned int BSTree_balanced_time = 0;
  unsigned int map_time = 0;

  auto rng = std::default_random_engine {}; // random seed to shuffle key and value vectors


  for(int k=50000;k<1000000;k = k + 50000){ // cicling trough different tree sizes 
  
   // std::cout<<"tree dimension: "<<k<<std::endl;

    for(int j=0;j<Ntries;j++){    

      for(int i=0;i<k;i++){
        key.push_back((i*1.0)/(k*1.0));
        value.push_back((i*1.0)/(k*1.0));
      }

      std::shuffle(begin(key), end(key), rng);
      std::shuffle(begin(value), end(value), rng);

  
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

    std::cout<<k<<"\t"<<BSTree_time/(k*Ntries*1.0)<<"\t"<<BSTree_balanced_time/(k*Ntries*1.0)<<"\t"<<map_time/(k*Ntries*1.0)<<std::endl;
    
  }


}catch(const error& e){
std::cerr<<"Exception encountered: "<< e.message<<std::endl;
return 1;
}


} 

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


//const function to call const[] operator

struct RandomKey_explicit {
  int one, two, three;
};

struct compareh {
   bool operator()(RandomKey_explicit bingo, RandomKey_explicit bango) const {
        return bingo.two < bango.two;
   }
};

    // test struct that contains three number, to be used as key.
    // the ordering should be done comparing the 'two' variable
    // apparently it works, as if std::less<K> is using the overloaded operator
    // which is not really expected (but welcomed)
    // ergo: there is no need to explicitely define a custom comparison function
struct RandomKey {
  double one, two, three;
  bool operator<(RandomKey other) const {
    return two < other.two;
 }
 
    RandomKey(const double& _one,const double& _two,const double& _three ) : one{_one}, two{_two}, three{_three} {};
  
};


int main() {

try{
  
  
    auto tree1 = BSTree<double, double>();
    std::map<double,double> map;

    std::vector<double> values;
    std::vector<double> keys;
    
    
    int N=2000; //size of the tree
    int Ntries=10000;
    
    std::cout<<"on trees of size "<< N <<std::endl;
    unsigned int average_tree=0;  //not balanced
    unsigned int average_tree_b=0; //balanced
    unsigned int average_map=0;  //map
    

for(int j=0;j<Ntries;j++){    
        
    for(int i=0;i<N;i++){
     keys.push_back(rand()/(double)RAND_MAX);
     values.push_back(rand()% 100/1.0);
    }
    
    for(int i=0;i<N;i++){
     tree1.insert(keys[i],values[i]);
     map[keys[i]]=values[i];
    }

    
    auto t0 = std::chrono::high_resolution_clock::now();
    auto t1 = std::chrono::high_resolution_clock::now();
    
    unsigned int interval=0;
    for(int i=0;i<N;i++){
      t0= std::chrono::high_resolution_clock::now();
      tree1.find(keys[i]);
      t1 = std::chrono::high_resolution_clock::now();
      interval+=std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
    }
    
//    std::cout<<"Time for lookup <double,double>: "<< interval <<std::endl;
    
//    std::cout<<"Balancing tree1<double,double>"<<std::endl;
    tree1.balance();
    
    unsigned int interval2=0;
    for(int i=0;i<N;i++){
      t0= std::chrono::high_resolution_clock::now();
      tree1.find(keys[i]);
      t1 = std::chrono::high_resolution_clock::now();
      interval2+=std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
    }
    
    unsigned int map_time=0;
    for(int i=0;i<N;i++){
      t0= std::chrono::high_resolution_clock::now();
      map.find(keys[i]);
      t1 = std::chrono::high_resolution_clock::now();
      map_time+=std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
    }

    
//    std::cout<<"Time for lookup <double,double> balanced: "<< interval2 <<std::endl;
    
//    std::cout<<"Percentage gain: "<<  gain <<std::endl;

    average_tree+=interval;  //not balanced
    average_tree_b+=interval2; //balanced
    average_map+=map_time;  //map
    
    tree1.clear();
    keys.clear();
    values.clear();
    map.clear();
}    
average_tree=average_tree/Ntries;
average_tree_b=average_tree_b/Ntries;
average_map=average_map/Ntries;

std::cout<<"Average time on " << Ntries << " tries of tree: "<< average_tree <<std::endl;
std::cout<<"Average time on " << Ntries << " tries of tree_balanced: "<< average_tree_b <<std::endl;
std::cout<<"Average time on " << Ntries << " tries of map: "<< average_map <<std::endl;

/*
    tree1.insert(RandomKey{0,8,41}, 8);
    tree1.insert(RandomKey{11,3,51}, 3);
    tree1.insert(RandomKey{13,10,1}, 10);
    tree1.insert(RandomKey{21,6,17}, 6);
    tree1.insert(RandomKey{1,4,18}, 4);
    tree1.insert(RandomKey{1,5,18}, 10);
    tree1.insert(RandomKey{1,4,18}, 72); //inserting identicals
    

    std::cout<<"Printing tree using custom key, with operator< overloading"<<std::endl;
    for (auto it=tree1.cbegin();it!=tree1.cend();++it) {
      std::cout<<(*it).first.two<<": "<<(*it).second<<std::endl;
    }

    //find test:
    auto pair=*(tree1.find(RandomKey{0,8,41}));

    std::cout<<"finding 0 8 41, expecting 8 as output. Get: " << pair.second <<std::endl;
    
    auto key=RandomKey{1,8,51};
    
    auto pair2=*(tree1.find(key));

    std::cout<<"finding 1 8 51, expecting 8 as output? Get: " << pair2.second <<std::endl;


    //Is this a problem of coding? Not really: the user gave a "not biective" key: if u use for example the sum of all 
    //the three int of the keys as criteria, you'd have the same problem between (1 3 5) and (3 3 3).
    //Even though they're different keys, in the order given they're the same. In reverse: If we
    //said that the keys are equal if and only if all the elements are equal, how should we append a node
    // node with the same second element as a previous? It's user responsability to give a proper order
    // So I think we're actually fine, but it's something to be aware of.
    
    std::cout<<"finding 1 8 51 with [], expecting 8 as output. Get: " << tree1[key] <<std::endl;
    
    std::cout<<"finding 1 8 51 with const [], expecting 8 as output. Get: \n" << tree1.square_bracket_test(key) <<std::endl;
    
    BSTree<RandomKey, int> tree2{tree1}; //copy ctor
    std::cout<<"tree2 copy ctor from previous "<<tree2<<std::endl;
    tree2.clear();
//    std::cout<<"tree2 empty "<<tree2<<std::endl;  //error works
    tree2=tree1;
    std::cout<<"tree2 copy assign from previous "<<tree2<<std::endl;	
    BSTree<RandomKey, int> tree3{std::move(tree2)}; //move ctor
    tree2=std::move(tree1); //move assign


*/    
    // this works too, it requires the functor compareh()
    // if compareh() is omitted, the code does not compile
    // here an error message would be good, since in this case the
    // compiler gets quite verbose and quite uninformative. I do not think
    // handling exceptions is easy, because the use of the functor is not 
    // required if the struct used as key overloads the operator<

/*    auto tree2 = BSTree<RandomKey_explicit, int, compareh>();
    tree2.insert(RandomKey_explicit{0,8,41}, 8);
    tree2.insert(RandomKey_explicit{11,3,51}, 3);
    tree2.insert(RandomKey_explicit{13,10,1}, 10);
    tree2.insert(RandomKey_explicit{21,6,17}, 6);
    tree2.insert(RandomKey_explicit{1,4,18}, 4);


    std::cout<<"Printing tree using custom key, functor"<<std::endl;
    for (auto it=tree2.cbegin();it!=tree2.cend();++it) {
      std::cout<<(*it).first.two<<": "<<(*it).second<<std::endl;
    }*/
    
    }catch(const error& e){
    std::cerr<<"Exception encountered: "<< e.message<<std::endl;
    return 1;
    }


}

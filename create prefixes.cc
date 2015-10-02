//#ifdef test
#include "read.h"
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string.h>
#include<stdio.h>

using namespace std;

int len;
int rebase;
struct Key_M
{
 	int seg_length; //the segment length
	char *seg;
	Key_M(const char * seg,int seg_length){

	this->seg_length=seg_length; //the segment length
	this->seg=( char *)seg;
        hash_val=compute_hash();
}
	bool operator==(const Key_M &other) const
  { 
	return (strncmp(seg, other.seg,seg_length)==0);
      
	
}
        size_t compute_hash() const{
	size_t result = 2166136261;
         for(int i=0;i< seg_length;i++)
	result = (result * 16777619) ^  seg[i] ;
        
	return result;
}
		
        size_t hash_val;
	
};

namespace std {

  template <>
  struct hash<Key_M>
  {
    std::size_t operator()(const Key_M& k) const
    {
     return k.hash_val;
    }
  };

};

int  main(int argc, char** argv){

	char * input_file = argv[2];
	    unordered_map<Key_M,int> map;
	//passjoin p;
	string tau(argv[1]);
	stringstream str(tau);
	int tau_main;
	str >> tau_main;
	cout << input_file << endl;
	ReadFile r(input_file);
	r.sortFile();


short ** hist_2=new short*[r.wcnt];
	char a = 'a';
	char z = 'z';
	int * count=new int[2*tau_main+1];
	//cout<<"eeee"<<endl;
	memset(count,0,(2*tau_main+1)*4);
	
	for (int i=0; i <r.wcnt; i++){
			hist_2[i]=new short[2];
			memset(hist_2[i],0,4);
			//cout<<"sssss"<<endl;
			for (int j = 0; j <= 2*tau_main; j++){
			if (r.words[i][j] >= a&&r.words[i][j] <= a+13){
				hist_2[i][0]++;
				//cout<<hist_2[i][0]<<endl;
			}
			else if (r.words[i][j] >= a+14&&r.words[i][j] <= z||!(r.words[i][j] >= a&&r.words[i][j] <= z)){
				hist_2[i][1]++;
				//cout<<hist_2[i][1]<<endl;
			}

		}

		Key_M k( r.words[i],2*tau_main);
			if(map.count(k)){
				map.at(k)++;
			} else {
			count[hist_2[i][0]]++;
				map.emplace(k,1);
				
			 }
	
	}
	
			
		
cout<<map.size()<<" "<<r.wcnt<<endl;
short g=0XFFFF;
cout<<g<<endl;
for(int i=0;i<2*tau_main+1;i++){
cout<<count[i]<<endl;
}


return 0;
}
//#endif

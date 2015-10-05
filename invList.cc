#include "invList.h"
#include <string.h>
#include<stdio.h>
#include "key.h"
#include<iostream>

void InvList::insert(const char *seg, int seg_length,int word_length, int seg_index, int word_index){
	//prepare Key
	Key k(word_length,seg_index, seg_length, seg);
	if(super::count(k)){
		super::at(k)->push_back(word_index);
	} else {
		vector <int> *v=new vector<int>();
		v->push_back(word_index);
		super::emplace(k,v);
	}
	
}

vector<int>* InvList::check(char *seg, int seg_length,int word_length, int seg_index){
	Key k(word_length,seg_index, seg_length, seg);
	auto f= super::find(k);
        if(f==super::end()) return NULL;
        return f->second;
}


void InvList::print() const{

	for ( auto it = begin(); it != end(); ++it ){
		auto v=      it->second;
                printf("%d \t",v->size());
		it->first.print();
     


		for (auto it2 =v->begin();it2 !=v->end(); ++it2){
		printf ("%d,", *it2);
		}
		std::cout << std::endl;
	}

}

#include "invList_Seg.h"
#include <string.h>
#include<stdio.h>
#include<iostream>

void InvList_Seg::insert(const char *seg, int seg_length, int word_index,int seg_i){

	Key_M k( seg,seg_length,word_index,seg_i);
	if(super::count(k)){

		super::at(k)->push_back(word_index);
	} else {
		vector <int> *v=new vector<int>();
		v->push_back(word_index);
		super::emplace(k,v);
	}

}

vector<int>* InvList_Seg::check(char *seg, int seg_length,int index,int seg_i){
//	if(index==69643&&seg_i==2){
//	    cout<<"&&&&&&&&777"<<endl;
//        cout<<seg<<endl;
//        cout<<seg_length<<endl;
//        cout<<"&&&&&&&&777"<<endl;
//
//	}

	Key_M k(seg, seg_length,index,seg_i);
	auto f= super::find(k);


        if(f==super::end()) return NULL;
        return f->second;
}


void InvList_Seg::print() const{

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

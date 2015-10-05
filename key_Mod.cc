#include "key_Mod.h"
#include <iostream>
using namespace std;
Key_M::Key_M( const char * seg,int seg_length,int word_index,int seg_i){

	this->seg_length=seg_length; //the segment length
	this->seg=( char *)seg;
        hash_val=compute_hash();

}

inline size_t Key_M::compute_hash() const{
	//perfect_hash hash;

size_t result = 2166136261;
         for(int i=0;i< seg_length;i++)
	result = (result * 16777619) ^  seg[i] ;

	return result;
	//return hash(seg,seg_length);
}



bool Key_M::operator==(const Key_M &other) const
  {

//      cout<<seg<<" =="<<endl;;
//      cout<<comparestrings(seg, other.seg,seg_length)<<endl;
//      }
	return strncmp(seg, other.seg,seg_length)==0;

}
bool Key_M::comparestrings(const char*a,const char*b,int len) const{

	int i=0;
	short d;
	short d1;
	int a1,b1;
	int new_len=len+(len%2);
	int k4= new_len>>2;
	int k2= (new_len-(k4<<2));
	short res=0;
	for(int i=0;i<k4;i++){

		int a1=*a;
		int b1=*b;

		res|=a1^b1;

		a+=4;
		b+=4;
	}
	if(k2!=0){
		d=*a;
		d1=*b;
		res|=d^d1;
	}

	return res==0;
}
void Key_M::print() const{
	printf( "(%d, %d, %d, %.*s:%d)", seg_length,seg_length, seg, hash_val);
}

/*
int main()
{
  std::unordered_map<Key,int> m6;
Key k(1,1,1,"John");
Key K(1,1,2,"John");
m6.emplace (k, 1);
printf("%d\n",k.hash_val);
printf("%d\n",K.hash_val);
}*/

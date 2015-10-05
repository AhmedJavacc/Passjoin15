#include "key.h"
Key::Key(int length, int i, int seg_length,const char * s){
	this->length=length;
	this->i=i;
	this->seg_length=seg_length; //the segment length
	this->seg=( char *)s;
        hash_val=compute_hash();
}
inline size_t Key::compute_hash() const{
	size_t result = 2166136261;
	result = (result * 16777619) ^  std::hash<int>() (length) ;
	result = (result * 16777619) ^  std::hash<int>() (i) ;
	result = (result * 16777619) ^  std::hash<int>() (seg_length) ;
         for(int i=0;i< seg_length;i++)
	result = (result * 16777619) ^  seg[i] ;
        
	return result;
}
bool Key::operator==(const Key &other) const
  { 
	if(hash_val==other.hash_val)

	return ((length == other.length)
            && (i == other.i)
            && (seg_length == other.seg_length)
            &&  (strncmp(seg, other.seg,seg_length)==0)
      );
	else return false;
}

void Key::print() const{
	printf( "(%d, %d, %d, %.*s:%d)",length, i, seg_length,seg_length, seg, hash_val);
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

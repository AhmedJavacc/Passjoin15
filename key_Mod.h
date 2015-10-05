#ifndef KEY_Mod_H_INCLUDE_FILE
#define KEY_Mod_H_INCLUDE_FILE
#include <unordered_map>
#include <string>
#include <string.h>
#include<stdio.h>
#include "perfect_hash.h"
struct Key_M
{
 	int seg_length; //the segment length
	char *seg;
	int word_index;
	int seg_i;
	Key_M(const char * seg,int seg_length,int word_index=0,int seg_i=0);
	bool operator==(const Key_M &other) const;
        size_t compute_hash() const;
		bool comparestrings(const char*a,const char*b,int len) const;
        size_t hash_val;
	void print() const;
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

}
#endif

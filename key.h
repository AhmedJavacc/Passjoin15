#ifndef KEY_H_INCLUDE_FILE
#define KEY_H_INCLUDE_FILE
#include <unordered_map> 
#include <string>
#include <string.h>
#include<stdio.h>
struct Key
{
 	int length;
	int i;
	int seg_length; //the segment length
	char *seg;
	Key(int length, int i, int seg_length, const char * s);
	bool operator==(const Key &other) const;
        size_t compute_hash() const;
        size_t hash_val;
	void print() const;
};

namespace std {

  template <>
  struct hash<Key>
  {
    std::size_t operator()(const Key& k) const
    {
     return k.hash_val;
    }
  };

}
#endif

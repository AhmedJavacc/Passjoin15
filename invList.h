#ifndef INVLIST_H_INCLUDED
#define INVLIST_H_INCLUDED
#include <unordered_map>
#include "vector"
#include "key.h"
using namespace std;
//template <int x>
class InvList:unordered_map<Key, vector<int>*> {
public:
        typedef  unordered_map<Key, vector<int>*> super;
	void insert(const char *seg, int seg_length,int word_length, int seg_index, int word_index);
	vector<int>* check(char *seg, int seg_length,int word_length, int seg_index);
        void print() const;
		void clear();
		long size();
		private:

};

#endif // INVLIST_H_INCLUDED


#ifndef INVLIST_SEG_H_INCLUDED
#define INVLIST_SEG_H_INCLUDED
#include <unordered_map>
#include "vector"
#include "key_Mod.h"
using namespace std;
//template <int x>
class InvList_Seg:unordered_map<Key_M, vector<int>*> {
public:
	typedef  unordered_map<Key_M, vector<int>*> super;
	void insert(const char *seg, int seg_length,int index=0,int seg_i=0);
	vector<int>* check(char *seg, int seg_length,int index=0,int seg_i=0);
        void print() const;
		void clear();
		long size();
		private:

};

#endif // INVLIST_H_INCLUDED


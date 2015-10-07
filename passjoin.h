#ifndef PASSJOIN_H_INCLUDED
#define PASSJOIN_H_INCLUDED
#include <chrono>
#include "invList.h"
#include <fstream>
#include <unordered_map>
#include<chrono>
#include <vector>
#include <deque>
#include <unordered_map>
#include "invList_Seg.h"
#include <stack>
#include "utils.h"
//#include "trie.h"
using namespace std;

class passjoin{

public:
	vector<int> *** strings_indexed;
	vector<int> * strings_len_indexed;
	pair<long,long> * results;
	int tau;
	utils utils1;
	InvList L;
	InvList L1;
	InvList L_count;
	InvList L1_count;
	int * cand_tau_1;
	int * cand_tau_2;
	int *dist;
	int *lenc;
	int * v0;
	int * v1;
	int * e;
	int ** v01;
	int ** v11;
	int ** e1;
	int  j, r, s, start_s, end_s, start_r, end_r;
	char * word_r;
	char * word_s;
	char * output;
	long candidates;
	long candidates_l;
	long overallSubstrings;
	long matched_pair;
	ofstream myfile;
	long filter_operation;

	vector<pair<int, int>> matched_strings;
	deque<unordered_map<int,int>> matched_groups;
	deque<vector<int>> matched_groups_merge;
	vector < vector<int>*> candidates_list;
	int *mark_overlapping;
	int * mark_covered;
	int * coutChar;
	unordered_map<Key_M,int> **** substrings;
	//Trie **** substringss;

	enum iterVerfy_dir
	{
		left,
		right
	};

	int candidate_tau_plus_two_reverse(char *x, int x_len, int pos_x, char ** words);
	int candidate_tau_plus_two_reverse(char *x, int x_len, int pos_x, char ** words,passjoin& p1);
	int candidate_tau_plus_two_original_len_tree_ind(char *x, int x_len, int pos_x, char ** words);
	int candidate_tau_plus_two_hist_len_tree_ind(char *x, int x_len, int pos_x, char ** words);
	int candidate_tau_plus_two_hist_len_tree_ind_hist_index(int len,int B0,int B1,char**words);
	int candidate_tau_plus_two_hist_len_tree_ind_len_index(int len,char**words);
	int self_join(int len,int B0,int B1,char**words);
	int R_S_join(int l,int b0,int b1,int len,int B0,int B1,char**words);
	int self_join(int len,char**words,int i);
	int R_S_join(int l,int len,char**words);
	int R_S_join(int l, int len, char**words,int i);
	bool iterativeVerify(char * r, char * s, int i, int first_seg, int last_seg, int k, int start_r, int start_s, int end_r, int end_s, int pos_s, int pos_r, int tau_dash, iterVerfy_dir f);
	int * verified;
	//int * previous;
	int ** boundaries;
	int ** histograms;
	float ** histograms_first;
	float ** histograms_second;
	float **histograms_SSE;
	short ** hist_2;
	//verified_m ** verified_list;
	InvList_Seg**** L_B0_B1;
	InvList_Seg** L2;
	int start;
	int end;
	int * first_match;
	pair<int, int> * first_match_pair;
	//int **first_match_pair;
	int * cand;
	int  *curr_i;
	int *seg_count;

	unsigned long long verification_time;
	unsigned long long filter_time;

	//unordered_map <int, int> count_seg_match;
	int candidate_iterative_multi_old_complex_hash(char *x, int L, int pos_x, char ** words);
	int candidate_iterative_multi_hist_based_len_tree_ind(char *x, int L, int pos_x, char ** words);
	int candidate_iterative_multi_original_len_tree_ind(char *x, int L, int pos_x, char ** words);
	void partion(char *x, int l, int id);
	void partion_tau_1_tree_ind(char *x, int l, int id);
	void partion_tau_2_tree_ind(char *x, int l, int id);
	void partion_tau_2_tree_ind_hist_index(char *x, int l, int id);
	int LevenshteinDistance_length_aware_modified(char * word1, char * word2, int word1_len, int word2_len, int tau);
	int LevenshteinDistance_length_aware_modified(char * word1, char * word2, int word1_len, int word2_len, int tau,int i);
	int LevenshteinDistance_length_aware_modified(char * word1, char * word2, int start_1, int start_2, int end_1, int end_2, int tau);
	bool multi_match( char* s1, char * r1, int delta, int first_seg, int last_seg, int k);
	int candidate_extension_mutli(char *x, int x_len, int pos_x, char ** words);

	bool filter(int pos_x,int pos_y,int x_len,int y_len);
	bool filter_SSE(int pos_x, int pos_y, int x_len, int y_len);
	bool is_there_overlapping(int pos_x, int it,passjoin&p1);
	//bool backword_filtering_Trie_based(char  * x, int len_x, int c_ind,int c_len,int tau);
	bool backword_filtering_unordered_map_based(char  * x, int len_x, int c_ind, int c_len, int tau);
	bool newFilter(int pos_x,int pos_it,int x_len);
bool newFilter_first_second(int pos_x, int pos_it,int x_len,int it_len);
};


#endif // PASSJOIN_H_INCLUDED


#include "passjoin.h"

#include "stdio.h"
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <xmmintrin.h>



int passjoin::LevenshteinDistance_length_aware_modified(char * word1, char * word2, int word1_len, int word2_len, int tau)
{



	int  j, r, s;
	char * word_r, *word_s;
	if (word1_len >= word2_len){
		s = word1_len;
		r = word2_len;
		word_s = word1;
		word_r = word2;
	}
	else{
		s = word2_len;
		r = word1_len;
		word_s = word2;
		word_r = word1;
	}
	int delta = s - r;





	for (int i = 0; i < s + 1; i++){
		v0[i] = i;
		v1[i] = tau + 1;
	}
	for (int i = 1; i <= r; i++)
	{
		v1[0] = i;


		int st = max(1, (i - (tau - delta) / 2));
		int en = min(s, (i + (tau + delta) / 2));
		for (j = st; j <= en; j++)
		{

			int cost = (word_r[i - 1] == word_s[j - 1]) ? 0 : 1;
			v1[j] = min(min(v1[j - 1] + 1, v0[j] + 1), v0[j - 1] + cost);


			e[j] = v1[j] + abs((s - j) - (r - i));
		}

		for (int j = 0; j < s + 1; j++){
			v0[j] = v1[j];
			v1[j] = tau + 1;
			e[j] = 0;
		}
	}

	return v0[s];
}

int passjoin::LevenshteinDistance_length_aware_modified(char * word1, char * word2, int word1_len, int word2_len, int tau,int i1)
{



	int  j, r, s;
	char * word_r, *word_s;
	if (word1_len >= word2_len){
		s = word1_len;
		r = word2_len;
		word_s = word1;
		word_r = word2;
	}
	else{
		s = word2_len;
		r = word1_len;
		word_s = word2;
		word_r = word1;
	}
	int delta = s - r;





	for (int i = 0; i < s + 1; i++){
		v01[i1][i] = i;
		v11[i1][i] = tau + 1;
	}
	for (int i = 1; i <= r; i++)
	{
		v11[i1][0] = i;


		int st = max(1, (i - (tau - delta) / 2));
		int en = min(s, (i + (tau + delta) / 2));
		for (j = st; j <= en; j++)
		{

			int cost = (word_r[i - 1] == word_s[j - 1]) ? 0 : 1;
			v11[i1][j] = min(min(v11[i1][j - 1] + 1, v01[i1][j] + 1), v01[i1][j - 1] + cost);


			e1[i1][j] = v11[i1][j] + abs((s - j) - (r - i));
		}

		for (int j = 0; j < s + 1; j++){
			v01[i1][j] = v11[i1][j];
			v11[i1][j] = tau + 1;
			e1[i1][j] = 0;
		}
	}

	return v01[i1][s];
}

int passjoin::LevenshteinDistance_length_aware_modified(char * word1, char * word2, int start_1, int start_2, int end_1, int end_2, int tau)
{
	int word1_length = end_1 - start_1 + 1;
	int word2_length = end_2 - start_2 + 1;
	if (word1_length < 0 || word1_length < 0){
		return max(0, max(word1_length, word2_length));
	}







	if (word1_length == 0) return word2_length;
	if (word2_length == 0) return word1_length;
	if (word1_length >= word2_length){
		s = word1_length;
		r = word2_length;
		start_s = start_1;

		start_r = start_2;

		word_s = word1;
		word_r = word2;
	}
	else{
		s = word2_length;
		r = word1_length;
		start_s = start_2;

		start_r = start_1;

		word_s = word2;
		word_r = word1;
	}
	int delta = s - r;





	for (int i = 0; i < s + 1; i++){
		v0[i] = i;
		v1[i] = tau + 1;
	}
	int tau_plus_delta = (tau + delta) / 2;
	int tau_minus_delta = (tau - delta) / 2;
	int st;
	int en;
	int cost;
	for (int i = 1; i <= r; i++)
	{




		v1[0] = i;


		st = max(1, (i - tau_minus_delta));
		en = min(s, (i + tau_plus_delta));
		for (j = st; j <= en; j++)
		{

			cost = (word_r[i - 1 + start_r] == word_s[j - 1 + start_s]) ? 0 : 1;
			v1[j] = min(min(v1[j - 1] + 1, v0[j] + 1), v0[j - 1] + cost);


			e[j] = v1[j] + abs((s - j) - (r - i));
		}

		bool large_than_tau = 1;
		for (j = st; j <= en; j++)
		{

			if (e[j] <= tau)
			{
				large_than_tau = 0;
				break;
			}
		}
		if (large_than_tau == 1)
		{
			return tau + 1;
		}

		for (int j = 0; j < s + 1; j++){
			v0[j] = v1[j];
			v1[j]=tau+1;
			e[j] = 0;
		}
	}

	return v0[s];
}



void passjoin::partion(char *x, int l, int id){
	int first_seg = utils1.floor(l, tau + 1);
	int k = l - (first_seg)*(tau + 1);
	int last_seg = utils1.ceiling(l, tau + 1);
	char *b = (char *)x;
	for (int j = 0; j < tau + 1 - k; j++){
		L.insert(b, first_seg, l, j, id);
		b += first_seg;
	}
	for (int j = tau + 1 - k; j < tau + 1; j++) {
		L.insert(b, last_seg, l, j, id);
		b += last_seg;
	}
}
void passjoin::partion_tau_1_tree_ind(char *x, int l, int id){
	int first_seg = utils1.floor(l, tau + 1);
	int k = l - (first_seg)*(tau + 1);
	int last_seg = utils1.ceiling(l, tau + 1);
	char *b = (char *)x;
	for (int j = 0; j < tau + 1 - k; j++){

		L2[l - start][j].insert(b, first_seg, id);

		b += first_seg;
	}
	for (int j = tau + 1 - k; j < tau + 1; j++) {


		L2[l - start][j].insert(b, last_seg, id);
		b += last_seg;
	}
}
void passjoin::partion_tau_2_tree_ind(char *x, int l, int id){
	//cout<<"aaa"<<endl;
	int first_seg = utils1.floor(l, tau + 2);
	int k = l - (first_seg)*(tau + 2);
	int last_seg = utils1.ceiling(l, tau + 2);
	char *b = (char *)x;
	//cout<<"fff"<<" "<<hist_2[id][0]<<endl;
	//cout<<l<<endl;
	for (int j = 0; j < tau + 2 - k; j++){

		L2[l - start][j].insert(b, first_seg, id);
		b += first_seg;
	}
	for (int j = tau + 2 - k; j < tau + 2; j++) {


		L2[l - start][j].insert(b, last_seg, id);

		b += last_seg;
	}
	//cout<<"dddddddddd"<<endl;
}
void passjoin::partion_tau_2_tree_ind_hist_index(char *x, int l, int id){
	//cout<<"aaa"<<endl;
	int first_seg = utils1.floor(l, tau + 2);
	int k = l - (first_seg)*(tau + 2);
	int last_seg = utils1.ceiling(l, tau + 2);
	char *b = (char *)x;
	//cout<<"fff"<<" "<<hist_2[id][0]<<endl;
	//cout<<l<<endl;
	for (int j = 0; j < tau + 2 - k; j++){

		if (id == 923){
			cout << 923<<endl;
			cout << l << endl;
			cout << x << endl;
			cout << hist_2[id][0] << " " << hist_2[id][1] << endl;
		}
		if (id == 380){
			cout << 380 << endl;
			cout << l << endl;
			cout << x << endl;
			cout << hist_2[id][0] << " " << hist_2[id][1] << endl;
		}
		L_B0_B1[l - start][hist_2[id][0]][hist_2[id][1]][j].insert(b, first_seg, id);
		b += first_seg;
	}
	for (int j = tau + 2 - k; j < tau + 2; j++) {



		L_B0_B1[l - start][hist_2[id][0]][hist_2[id][1]][j].insert(b, last_seg, id);
		b += last_seg;
	}
	//cout<<"dddddddddd"<<endl;
}



bool passjoin::iterativeVerify(char * r, char * s, int i, int first_seg, int last_seg, int k, int start_r, int start_s, int end_r, int end_s, int pos_s, int pos_r, int tau_dash, iterVerfy_dir dir){
	int seg_length = 0;
	int wordr_length = end_r - start_r + 1;
	int words_length = end_s - start_s + 1;
	if (wordr_length <= 0 || words_length <= 0){
		return 1;
	}

	int delta = (words_length - wordr_length);
	if (dir == left){
		int j = (i - 1);
		if (j < tau + 1 - k){
			seg_length = first_seg;
		}
		else{
			seg_length = last_seg;
		}
		int start_j_seg = end_r - seg_length + 1;
		int end_j_seg = start_j_seg - 1;

		for (int i = end_r; i >= end_r - seg_length + 1; i--){
			if (s[end_s - (end_r - i)] != r[i]){
				end_j_seg = i - 1;
				break;
			}
		}

		int j_seg_len = end_j_seg - start_j_seg + 1;
		if (j_seg_len == 0){
			return 1;
		}
		int pmin = (max(start_j_seg - abs(j), start_j_seg + delta - tau_dash + abs(j)));
		int pmax = min(start_j_seg + abs(j), start_j_seg + delta + tau_dash - abs(j));
		bool found = false;
		int times = 0;
		int mark = 0;
		for (int p = pmin; p <= pmax; p++){
			found = true;
			if (strncmp((r + start_j_seg), (s + p), j_seg_len) == 0 && times == 0){

				mark = iterativeVerify(r, s, i - 1, first_seg, last_seg, k, 0, 0, start_j_seg - 1, p - 1, pos_s, pos_r, tau_dash - 1 + abs(start_j_seg - p), left) | mark;
			}
			else if (strncmp((r + start_j_seg), (s + p), j_seg_len) == 0){
				found = true;
				times++;
			}
			else{
				found = false;
			}


		}
		if (mark){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		int j = (i + 1);
		if (j < tau + 1 - k){
			seg_length = first_seg;
		}
		else{
			seg_length = last_seg;
		}

		int end_j_seg = start_r + seg_length - 1;
		int start_j_seg = end_j_seg + 1;
		for (int i = start_r; i < start_r + seg_length - 1; i++){
			if (s[start_s + (i - start_r)] != r[i]){
				start_j_seg = i + 1;
				break;
			}
		}

		int j_seg_len = end_j_seg - start_j_seg + 1;
		if (j_seg_len == 0){
			return 1;
		}
		int pmin = max(start_j_seg + (start_s - start_r) - 1, start_j_seg + (start_s - start_r) + delta - tau_dash + 1);
		int pmax = min(start_j_seg + (start_s - start_r) + 1, start_j_seg + (start_s - start_r) + delta + tau_dash - 1);
		bool found = false;
		int times = 0;
		int mark = 0;
		for (int p = pmin; p <= pmax; p++){
			found = true;
			if (strncmp((r + start_j_seg), (s + p), j_seg_len) == 0 && times == 0){

				mark = iterativeVerify(r, s, i + 1, first_seg, last_seg, k, start_j_seg + j_seg_len, p + j_seg_len, end_r, end_s, pos_s, pos_r, tau_dash - 1, right) | mark;
			}
			else if (strncmp((r + start_j_seg), (s + p), j_seg_len) == 0){
				found = true;
				times++;
			}
			else{
				found = false;
			}


		}
		if (mark){
			return 1;
		}
		else{
			return 0;
		}
	}
	return 1;
}

bool passjoin::multi_match(char* s1, char * r1, int delta, int first_seg, int last_seg, int k){



	int pi = 0;

	for (int i = 0; i < tau + 1 - k; i++){
		int pmin = max(pi - (i), pi - delta - tau + i);
		int pmax = min(pi + (i), pi - delta + tau - i);
		for (int p = pmin; p <= pmax; p++){
			if (strncmp(s1 + pi, r1 + p, first_seg) == 0){
				return 1;
			}
		}
		pi += first_seg;
	}
	for (int i = tau + 1 - k; i < tau + 1; i++){
		int pmin = max(pi - (i), pi - delta - tau + i);
		int pmax = min(pi + (i), pi - delta + tau - i);
		for (int p = pmin; p <= pmax; p++){
			if (strncmp(s1 + pi, r1 + p, last_seg) == 0){
				return 1;
			}
		}
		pi += last_seg;
	}
	return 0;
}
int passjoin::candidate_iterative_multi_old_complex_hash(char *x, int x_len, int pos_x, char ** words){

	int cand_l = 0;



	for (int l = x_len - tau; l <= x_len; l++){
		int delta = x_len - l;
		int first_seg = utils1.floor(l, tau + 1);
		int k = l - (first_seg)*(tau + 1);
		int last_seg = utils1.ceiling(l, tau + 1);
		int pi = 0;
		for (int i = 0; i<tau + 1 - k; i++){
			int pmin = max(pi - (i), pi + delta - tau + i);
			int pmax = min(pi + (i), pi + delta + tau - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = L.check(x + p, first_seg, l, i);
				if (v){

					if (v->size()>0){
						int tau_l = i;
						int tau_r = tau - i;

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != pos_x){
								if (first_match[*it] != pos_x){

									first_match[*it] = pos_x;

									if (iterativeVerify(words[*it], x, i, first_seg, last_seg, k, 0, 0, pi - 1, p - 1, pos_x, (*it), tau_l, left)){
										int d_l = LevenshteinDistance_length_aware_modified(x, words[*it], 0, 0, p - 1, pi - 1, tau);
										if (iterativeVerify(words[*it], x, i, first_seg, last_seg, k, pi + first_seg, p + first_seg, strlen(words[*it]) - 1, x_len - 1, pos_x, *it, tau_r, right)){

											int d_r = LevenshteinDistance_length_aware_modified(x, words[*it], p + first_seg, pi + first_seg, x_len - 1, strlen(words[*it]) - 1, tau);

											if (d_l + d_r <= tau){
												verified[*it] = pos_x;
												matched_pair++;
												matched_strings.push_back(make_pair(pos_x, *it));






											}

										}
									}
								}
								else{
									int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
									if (d <= tau){
										verified[*it] = pos_x;
										matched_pair++;
										matched_strings.push_back(make_pair(pos_x, *it));




									}
								}
							}
						}
					}
				}


			}
			pi += first_seg;
		}

		for (int i = tau + 1 - k; i<tau + 1; i++) {
			int pmin = max(pi - (i), pi + delta - tau + i);
			int pmax = min(pi + (i), pi + delta + tau - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = L.check(x + p, last_seg, l, i);
				if (v){

					if (v->size()>0){
						int tau_l = i;
						int tau_r = tau - i;
						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != pos_x){
								if (first_match[*it] != pos_x){
									first_match[*it] = pos_x;
									if (iterativeVerify(words[*it], x, i, first_seg, last_seg, k, 0, 0, pi - 1, p - 1, pos_x, *it, tau_l, left)){

										int d_l = LevenshteinDistance_length_aware_modified(x, words[*it], 0, 0, p - 1, pi - 1, tau);

										if (iterativeVerify(words[*it], x, i, first_seg, last_seg, k, pi + last_seg, p + last_seg, strlen(words[*it]) - 1, x_len - 1, pos_x, *it, tau_r, right)){

											int d_r = LevenshteinDistance_length_aware_modified(x, words[*it], p + last_seg, pi + last_seg, x_len - 1, strlen(words[*it]) - 1, tau);


											if (d_l + d_r <= tau){
												verified[*it] = pos_x;
												matched_pair++;
												matched_strings.push_back(make_pair(pos_x, *it));
												/*	myfile << x << endl;
												myfile << ',' << endl;
												myfile << words[*it] << endl;
												myfile << "<<<<<<<<<<<<<<<<<<<<<<<<<" << endl*/;
											}
										}
									}
								}
								else{
									int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
									if (d <= tau){
										verified[*it] = pos_x;
										matched_pair++;
										matched_strings.push_back(make_pair(pos_x, *it));
										/*	myfile << x << endl;
										myfile << ',' << endl;
										myfile << words[*it] << endl;
										myfile << "<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;*/
									}
								}
							}
						}
					}
				}


			}
			pi += last_seg;
		}
	}



	return cand_l;
}

int passjoin::candidate_iterative_multi_hist_based_len_tree_ind(char *x, int x_len, int pos_x, char ** words){

	int cand_l = 0;


	InvList_Seg* curr;
	for (int l = x_len - tau; l <= x_len; l++){


		int delta = x_len - l;
		if ((l - start) < 0){
			continue;
		}
		int first_seg = utils1.floor(l, tau + 1);
		int k = l - (first_seg)*(tau + 1);
		int last_seg = utils1.ceiling(l, tau + 1);
		int pi = 0;
		for (int i = 0; i<tau + 1 - k; i++){
			curr = &L2[l - start][i];
			int pmin = max(pi - (i), pi + delta - tau + i);
			int pmax = min(pi + (i), pi + delta + tau - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr->check(x + p, first_seg,pos_x,i);
				if (v){

					if (v->size()>0){
						int tau_l = i;
						int tau_r = tau - i;

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != pos_x){
								if (!filter_SSE(pos_x, *it, x_len, l)){
									verified[*it] = pos_x;
									continue;
								}
								/*if (!backword_filtering_unordered_map_based(x, x_len, *it, strlen(words[*it]), tau)){
									verified[*it] = pos_x;

									continue;
									}*/
								cand_l++;
								if (first_match[*it] != pos_x){

									first_match[*it] = pos_x;

									if (iterativeVerify(words[*it], x, i, first_seg, last_seg, k, 0, 0, pi - 1, p - 1, pos_x, (*it), tau_l, left)){
										int d_l = LevenshteinDistance_length_aware_modified(x, words[*it], 0, 0, p - 1, pi - 1, tau);
										if (iterativeVerify(words[*it], x, i, first_seg, last_seg, k, pi + first_seg, p + first_seg, strlen(words[*it]) - 1, x_len - 1, pos_x, *it, tau_r, right)){

											int d_r = LevenshteinDistance_length_aware_modified(x, words[*it], p + first_seg, pi + first_seg, x_len - 1, strlen(words[*it]) - 1, tau);

											if (d_l + d_r <= tau){
												verified[*it] = pos_x;
												matched_pair++;
												matched_strings.push_back(make_pair(pos_x, *it));



											}

										}
									}
								}
								else{
									int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
									if (d <= tau){
										verified[*it] = pos_x;
										matched_pair++;
										matched_strings.push_back(make_pair(pos_x, *it));

									}
								}
//
//					int d_l = LevenshteinDistance_length_aware_modified(x, words[*it], 0, 0, p - 1, pi - 1, tau_l);
//
//								/*cout << "left distance:" << '\0' << d_l << endl;
//								cout << "left tau:" << '\0' << tau_l << endl;
//								*/
//								if (d_l <= tau_l){
//
//									int d_r = LevenshteinDistance_length_aware_modified(x, words[*it], p + first_seg, pi + first_seg, x_len - 1, strlen(words[*it]) - 1, tau_r);
//									if (d_r <= tau_r){
//										verified[*it] = pos_x;
//
//										matched_pair++;
//										int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
//										if(d>tau){
//										      if(pos_x==85108&&*it==75263){
//										        cout<<words[pos_x]<<" "<<words[*it]<<endl;
//                                                cout<<pi<<" "<<p<<endl;
//                                                cout<<last_seg<<endl;
//                                                cout<<tau_l<<" "<<tau_r<<endl;
//										    }
//                                            //matched_strings.push_back(make_pair(pos_x,*it));
//										}
//										//matched_strings.push_back(make_pair(pos_x, *it));
//										/*myfile << x << endl;
//										myfile << ',' << endl;
//										myfile << words[*it] << endl;
//										myfile << "<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;*/
//
//									}
//								}


							}
						}
					}
				}


			}
			pi += first_seg;
		}

		for (int i = tau + 1 - k; i<tau + 1; i++) {
			curr = &L2[l - start][i];
			int pmin = max(pi - (i), pi + delta - tau + i);
			int pmax = min(pi + (i), pi + delta + tau - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr->check(x + p, last_seg,pos_x,i);
				if (v){

					if (v->size()>0){
						int tau_l = i;
						int tau_r = tau - i;
						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != pos_x){

								if (!filter_SSE(pos_x, *it, x_len, l)){
									verified[*it] = pos_x;

									continue;
								}
								/*if (!backword_filtering_unordered_map_based(x, x_len, *it, strlen(words[*it]), tau)){
									verified[*it] = pos_x;

									continue;
									}*/

								cand_l++;


								if (first_match[*it] != pos_x){
									first_match[*it] = pos_x;

									if (iterativeVerify(words[*it], x, i, first_seg, last_seg, k, 0, 0, pi - 1, p - 1, pos_x, *it, tau_l, left)){

										int d_l = LevenshteinDistance_length_aware_modified(x, words[*it], 0, 0, p - 1, pi - 1, tau);

										if (iterativeVerify(words[*it], x, i, first_seg, last_seg, k, pi + last_seg, p + last_seg, strlen(words[*it]) - 1, x_len - 1, pos_x, *it, tau_r, right)){

											int d_r = LevenshteinDistance_length_aware_modified(x, words[*it], p + last_seg, pi + last_seg, x_len - 1, strlen(words[*it]) - 1, tau);


											if (d_l + d_r <= tau){
												verified[*it] = pos_x;
												matched_pair++;
												//matched_strings.push_back(make_pair(pos_x, *it));

											}
										}
									}
								}
								else{
									int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
									if (d <= tau){
										verified[*it] = pos_x;
										matched_pair++;
										//matched_strings.push_back(make_pair(pos_x, *it));

									}
								}
//
//								int d_l = LevenshteinDistance_length_aware_modified(x, words[*it], 0, 0, p - 1, pi - 1, tau_l);
//
//								/*cout << "left distance:" << '\0' << d_l << endl;
//								cout << "left tau:" << '\0' << tau_l << endl;
//								*/
//								if (d_l <= tau_l){
//
//									int d_r = LevenshteinDistance_length_aware_modified(x, words[*it], p + last_seg, pi + last_seg, x_len - 1, strlen(words[*it]) - 1, tau_r);
//									if (d_r <= tau_r){
//										verified[*it] = pos_x;
//
//										matched_pair++;
//
//									//	matched_strings.push_back(make_pair(pos_x, *it));
//										/*myfile << x << endl;
//										myfile << ',' << endl;
//										myfile << words[*it] << endl;
//										myfile << "<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;*/
//
//									}
//								}
//
//							}
						}
					}
				}

			}
		}
			pi += last_seg;
		}
	}



	return cand_l;
}
int passjoin::candidate_tau_plus_two_reverse(char *x, int x_len, int pos_x, char ** words){
	unordered_map<int, int> a;
	vector<int>b;
	matched_groups.push_front(a);
	matched_groups_merge.push_front(b);
	int cand_l = 0;
	int current = -1;
	InvList_Seg* curr;

	for (int l = x_len; l <= x_len + tau; l++){

		int delta = x_len - l;

		if ((end - l) < 0){
			continue;
		}
		int l_tree_index = l - start;
		int first_seg = utils1.floor(l, tau + 2);
		int k = l - (first_seg)*(tau + 2);
		int last_seg = utils1.ceiling(l, tau + 2);
		int pi = 0;
		for (int i = 0; i<tau + 2 - k; i++){
			curr = &L2[l_tree_index][i];

			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){

				auto v = curr->check(x + p, first_seg);
				if (v){

					if (v->size()>0){

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != pos_x){



								if (first_match[*it] == pos_x){
									verified[*it] = pos_x;
									if (filter_SSE(pos_x, *it, x_len, l)){
										cand_l++;
										int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
										if (d <= tau){
											mark_covered[*it] = 1;
											matched_pair++;
											matched_strings.push_back(make_pair(pos_x, *it));
											matched_groups.back().emplace(*it, *it);
											matched_groups_merge.back().push_back(*it);

										}

									}

								}

								else{


									/*first_match_pair[*it].first = pos_x;
									first_match_pair[*it].second = i;*/
									first_match[*it] = pos_x;
								}
							}


						}




					}

				}


			}
			pi += first_seg;
		}

		for (int i = tau + 2 - k; i<tau + 2; i++) {
			curr = &L2[l_tree_index][i];
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){

				auto v = curr->check(x + p, last_seg);
				if (v){

					if (v->size()>0){

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){

							if (verified[*it] != pos_x){



								if (first_match[*it] == pos_x){
									verified[*it] = pos_x;
									if (filter_SSE(pos_x, *it, x_len, l)){
										cand_l++;
										int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
										if (d <= tau){
											mark_covered[*it] = 1;
											matched_pair++;
											matched_strings.push_back(make_pair(pos_x, *it));
											matched_groups.back().emplace(*it, *it);
											matched_groups_merge.back().push_back(*it);
										}

									}



								}
								else{


									/*	first_match_pair[*it].first = pos_x;
									first_match_pair[*it].second= i;*/
									first_match[*it] = pos_x;
								}

							}
						}
					}

				}
			}
			pi += last_seg;

		}

	}











	return cand_l;
}
int passjoin::candidate_tau_plus_two_original_len_tree_ind(char *x, int x_len, int pos_x, char ** words){




	int cand_l = 0;
	int current = -1;
	InvList_Seg* curr;
	for (int l = x_len - (tau); l <= x_len; l++){


		int delta = x_len - l;
		if ((l - start) < 0){

			continue;
		}
		int l_tree_index = l - start;
		int first_seg = utils1.floor(l, tau + 2);
		int k = l - (first_seg)*(tau + 2);
		int last_seg = utils1.ceiling(l, tau + 2);
		int pi = 0;
		for (int i = 0; i<tau + 2 - k; i++){
			curr = &L2[l_tree_index][i];

			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){

				auto v = curr->check(x + p, first_seg);
				if (v){

					if (v->size()>0){

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != pos_x){
								if (first_match_pair[*it].first == pos_x){
									if (first_match_pair[*it].second != i){

										verified[*it] = pos_x;

										cand_l++;
										int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
										if (d <= tau){

											matched_pair++;
											matched_strings.push_back(make_pair(pos_x, *it));
											/*matched_groups.back().emplace(*it, *it);
											matched_groups_merge.back().push_back(*it);
*/
										}

									}

								}

								else{

									first_match_pair[*it].first = pos_x;
									first_match_pair[*it].second = i;

								}
							}


						}




					}

				}


			}
			pi += first_seg;
		}

		for (int i = tau + 2 - k; i<tau + 2; i++) {
			curr = &L2[l_tree_index][i];
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){

				auto v = curr->check(x + p, last_seg);
				if (v){

					if (v->size()>0){

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){

							if (verified[*it] != pos_x){
								if (first_match_pair[*it].first == pos_x){
									if (first_match_pair[*it].second != i){


										verified[*it] = pos_x;

										cand_l++;
										int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
										if (d <= tau){

											matched_pair++;
											matched_strings.push_back(make_pair(pos_x, *it));
											/*matched_groups.back().emplace(*it, *it);
											matched_groups_merge.back().push_back(*it);*/
										}

									}



								}
								else{

									first_match_pair[*it].first = pos_x;
									first_match_pair[*it].second = i;

								}

							}
						}
					}

				}
			}
			pi += last_seg;

		}

	}











	return cand_l;
}

int passjoin::candidate_tau_plus_two_hist_len_tree_ind(char *x, int x_len, int pos_x, char ** words){




	int cand_l = 0;
	int current = -1;
	InvList_Seg* curr;
	for (int l = x_len - (tau); l <= x_len; l++){


		int delta = x_len - l;
		if ((l - start) < 0){

			continue;
		}
       if(dist[l]==dist[l+1])continue;

		int l_tree_index = l - start;
		int first_seg = utils1.floor(l, tau + 2);
		int k = l - (first_seg)*(tau + 2);
		int last_seg = utils1.ceiling(l, tau + 2);
		int pi = 0;
		for (int i = 0; i<tau + 2 - k; i++){
			curr = &L2[l_tree_index][i];

			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){

				auto v = curr->check(x + p, first_seg);

				if (v){

					if (v->size()>0){

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != pos_x){
								if (first_match_pair[*it].first == pos_x){
									if (first_match_pair[*it].second != i){

										verified[*it] = pos_x;
										if (!newFilter(pos_x, *it, x_len)){
										continue;
										}
										if (x_len == l){
											candidates_l++;
										}
											cand_l++;
											int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
											if (d <= tau){

												matched_pair++;

												/*matched_groups.back().emplace(*it, *it);
												matched_groups_merge.back().push_back(*it);
*/


										}

									}
								}
								else{

									first_match_pair[*it].first = pos_x;
									first_match_pair[*it].second = i;

								}
							}


						}




					}

				}


			}
			pi += first_seg;
		}

		for (int i = tau + 2 - k; i<tau + 2; i++) {
			curr = &L2[l_tree_index][i];
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){

				auto v = curr->check(x + p, last_seg);

				if (v){

					if (v->size()>0){

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){

							if (verified[*it] != pos_x){
								if (first_match_pair[*it].first == pos_x){
									if (first_match_pair[*it].second != i){

										verified[*it] = pos_x;
										if (!newFilter(pos_x, *it, x_len)){
											continue;
										}
										if (x_len == l){
											candidates_l++;
										}
											cand_l++;
											int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
											if (d <= tau){

												matched_pair++;

											/*	matched_groups.back().emplace(*it, *it);
												matched_groups_merge.back().push_back(*it);*/
											}






									}
								}
								else{

									first_match_pair[*it].first = pos_x;
									first_match_pair[*it].second = i;

								}

							}
						}
					}

				}

			}
			pi += last_seg;

		}








}




	return cand_l;
}
int passjoin:: candidate_tau_plus_two_hist_len_tree_ind_hist_index(int len,int B0,int B1,char**words){

	int cand_l = 0;
	cand_l+=self_join(len+start,B0,B1,words);

	for (int l = (len - (tau))<0?0:(len - (tau)); l <= len-1; l++){
		if (lenc[l]>0){
			for (int b0 = ((B0 - (tau))<0 ? 0 : (B0 - (tau))); b0 <= ((B0 + tau)>2 * tau ? 2 * tau : (B0 + tau)); b0++){

				for (int b1 = ((B1 - (tau))<0 ? 0 : (B1 - (tau))); b1 <= ((B1 + tau)>2 * tau - b0 ? 2 * tau - b0 : (B1 + tau)); b1++){
					//if (strings_indexed[l][b0][b1].size()>0)
					cand_l += R_S_join(l + start, b0, b1, len + start, B0, B1, words);
				}
			}
		}
	}


	int l = len;
		for (int b0 = ((B0 - (tau))<0 ? 0 : (B0 - (tau))); b0 <= (B0-1); b0++){

			for (int b1 =( (B1 - (tau))<0 ? 0 : (B1 - (tau))); b1 <= ((B1 + tau)>2 * tau - b0 ? 2 * tau - b0 : (B1 + tau)); b1++){

				//if (strings_indexed[l][b0][b1].size()>0)
				cand_l += R_S_join(l + start, b0, b1, len + start, B0, B1, words);
			}
		}
		int b0 = B0;
		for (int b1 = (B1 - (tau))<0 ? 0 : (B1 - (tau)); b1 <= (B1 -1) ; b1++){

			//if (strings_indexed[l][b0][b1].size()>0)
			cand_l += R_S_join(l + start, b0, b1, len + start, B0, B1, words);
		}
	return cand_l;

}
int passjoin:: candidate_tau_plus_two_hist_len_tree_ind_len_index(int len,char**words){

	int cand_l = 0;
	//cand_l+=self_join(len+start,words);

	for (int l = (len - (tau))<0?0:(len - (tau)); l <= len-1; l++){
		if (lenc[l]>0){

					cand_l += R_S_join(l + start, len + start, words);

		}
	}
	return cand_l;

}
int passjoin::self_join(int len,char**words,int i1){
	InvList_Seg* curr;
	int cand_l = 0;

		int first_seg = utils1.floor(len, tau + 2);
		int k = len - (first_seg)*(tau + 2);
		int last_seg = utils1.ceiling(len, tau + 2);
		curr=L2[len-start];
		int delta=0;
	for(auto it1=strings_len_indexed[len-start].begin();it1!=strings_len_indexed[len-start].end();++it1){

		int pi = 0;
		for (int i = 0; i<tau + 2 - k; i++){
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr[i].check(words[*it1] + p, first_seg);
								if (v){

										if (v->size()>0){

											for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
												if (verified[*it] != *it1){
													if (first_match_pair[*it].first == *it1){
														if (first_match_pair[*it].second != i){

															verified[*it] = *it1;
															if (!newFilter(*it1, *it, strlen(words[*it1]))){
															continue;
															}
																cand_l++;
																int d = LevenshteinDistance_length_aware_modified(words[*it1], words[*it], strlen(words[*it1]), len, tau,i1);
																if (d <= tau){
																	results[len - start].first++;
																	//matched_pair++;
																	//matched_strings.push_back(make_pair(*it1, *it));

															}

														}
													}
													else{

														first_match_pair[*it].first = *it1;
														first_match_pair[*it].second = i;

													}
												}


											}




										}

									}

			}
			pi+=first_seg;
		}
		for (int i = tau + 2-k; i<tau + 2 ; i++){
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr[i].check(words[*it1] + p, last_seg);
								if (v){

									if (v->size()>0){

										for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){

											if (verified[*it] != *it1){
												if (first_match_pair[*it].first == *it1){
													if (first_match_pair[*it].second != i){

														verified[*it] = *it1;
														if (!newFilter(*it1, *it, strlen(words[*it1]))){
															continue;
														}
															cand_l++;
															int d = LevenshteinDistance_length_aware_modified(words[*it1], words[*it], strlen(words[*it1]), len, tau,i1);
															if (d <= tau){
																results[len - start].first++;
																//matched_pair++;
																//matched_strings.push_back(make_pair(*it1, *it));
															}
													}
												}
												else{

													first_match_pair[*it].first = *it1;
													first_match_pair[*it].second = i;

												}

											}
										}
									}

				}

			}
			pi+=last_seg;
		}
		partion_tau_2_tree_ind(words[*it1],  len, *it1);
	}
	results[len - start].second = cand_l;
	return cand_l;
}
int passjoin::R_S_join(int l,int len,char**words){
	InvList_Seg* curr;
	int cand_l = 0;


		int first_seg = utils1.floor(l, tau + 2);
		int k = l - (first_seg)*(tau + 2);
		int last_seg = utils1.ceiling(l, tau + 2);
		curr=L2[l-start];
		int delta=len-(l);
	for(auto it1=strings_len_indexed[len-start].begin();it1!=strings_len_indexed[len-start].end();++it1){
		int pi = 0;
		for (int i = 0; i<tau + 2 - k; i++){
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr[i].check(words[*it1] + p, first_seg);
								if (v){

										if (v->size()>0){

											for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
												if (verified[*it] != *it1){
													if (first_match_pair[*it].first == *it1){
														if (first_match_pair[*it].second != i){

															verified[*it] = *it1;
															if (!newFilter(*it1, *it, strlen(words[*it1]))){
															continue;
															}
																cand_l++;
																int d = LevenshteinDistance_length_aware_modified(words[*it1], words[*it], strlen(words[*it1]), l, tau);
																if (d <= tau){

																	matched_pair++;
																	//matched_strings.push_back(make_pair(*it1, *it));

															}

														}
													}
													else{

														first_match_pair[*it].first = *it1;
														first_match_pair[*it].second = i;

													}
												}


											}




										}

									}

			}
			pi+=first_seg;
		}
		for (int i = tau + 2-k; i<tau + 2 ; i++){
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr[i].check(words[*it1] + p, last_seg);
								if (v){

									if (v->size()>0){

										for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){

											if (verified[*it] != *it1){
												if (first_match_pair[*it].first == *it1){
													if (first_match_pair[*it].second != i){

														verified[*it] = *it1;
														if (!newFilter(*it1, *it, strlen(words[*it1]))){
															continue;
														}
															cand_l++;
															int d = LevenshteinDistance_length_aware_modified(words[*it1], words[*it], strlen(words[*it1]), l, tau);
															if (d <= tau){

																matched_pair++;
																//matched_strings.push_back(make_pair(*it1, *it));
															}
													}
												}
												else{

													first_match_pair[*it].first = *it1;
													first_match_pair[*it].second = i;

												}

											}
										}
									}

				}

			}
			pi+=last_seg;
		}
	}
	return cand_l;
}

int passjoin::R_S_join(int l, int len, char**words,int i1){
	InvList_Seg* curr;
	int cand_l = 0;


	int first_seg = utils1.floor(l, tau + 2);
	int k = l - (first_seg)*(tau + 2);
	int last_seg = utils1.ceiling(l, tau + 2);
	curr = L2[l - start];
	int delta = len - (l);
	//cout << l << " " << len << endl;
	//cout << l-start << " dd " << len << endl;
	for (auto it1 = strings_len_indexed[len - start].begin(); it1 != strings_len_indexed[len - start].end(); ++it1){
		int pi = 0;
		for (int i = 0; i<tau + 2 - k; i++){
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr[i].check(words[*it1] + p, first_seg);
				if (v){

					if (v->size()>0){

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != *it1){
								if (first_match_pair[*it].first == *it1){
									if (first_match_pair[*it].second != i){

										verified[*it] = *it1;
										if (!newFilter(*it1, *it, strlen(words[*it1]))){
											continue;
										}
										results[len - start].second++;
										int d = LevenshteinDistance_length_aware_modified(words[*it1], words[*it], strlen(words[*it1]), l, tau,i1);
										if (d <= tau){

											results[len - start].first++;
											//matched_strings.push_back(make_pair(*it1, *it));

										}

									}
								}
								else{

									first_match_pair[*it].first = *it1;
									first_match_pair[*it].second = i;

								}
							}


						}




					}

				}

			}
			pi += first_seg;
		}
		for (int i = tau + 2 - k; i<tau + 2; i++){
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr[i].check(words[*it1] + p, last_seg);
				if (v){

					if (v->size()>0){

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){

							if (verified[*it] != *it1){
								if (first_match_pair[*it].first == *it1){
									if (first_match_pair[*it].second != i){

										verified[*it] = *it1;
										if (!newFilter(*it1, *it, strlen(words[*it1]))){
											continue;
										}
										results[len - start].second++;
										int d = LevenshteinDistance_length_aware_modified(words[*it1], words[*it], strlen(words[*it1]), l, tau,i1);
										if (d <= tau){

											results[len - start].first++;
											//matched_strings.push_back(make_pair(*it1, *it));
										}
									}
								}
								else{

									first_match_pair[*it].first = *it1;
									first_match_pair[*it].second = i;

								}

							}
						}
					}

				}

			}
			pi += last_seg;
		}
	}
	//results[len - start].second = cand_l;
	return 0;
}

int passjoin::self_join(int len,int B0,int B1,char**words){
	InvList_Seg* curr;
	int cand_l = 0;

		int first_seg = utils1.floor(len, tau + 2);
		int k = len - (first_seg)*(tau + 2);
		int last_seg = utils1.ceiling(len, tau + 2);
		curr=L_B0_B1[len-start][B0][B1];
		int delta=0;
	for(auto it1=strings_indexed[len-start][B0][B1].begin();it1!=strings_indexed[len-start][B0][B1].end();++it1){

		int pi = 0;
		for (int i = 0; i<tau + 2 - k; i++){
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr[i].check(words[*it1] + p, first_seg);
								if (v){

										if (v->size()>0){

											for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
												if (verified[*it] != *it1){
													if (first_match_pair[*it].first == *it1){
														if (first_match_pair[*it].second != i){

															verified[*it] = *it1;
															if (!newFilter(*it1, *it, strlen(words[*it1]))){
															continue;
															}
																cand_l++;
																int d = LevenshteinDistance_length_aware_modified(words[*it1], words[*it], strlen(words[*it1]), len, tau);
																if (d <= tau){

																	matched_pair++;
																	matched_strings.push_back(make_pair(*it1, *it));

															}

														}
													}
													else{

														first_match_pair[*it].first = *it1;
														first_match_pair[*it].second = i;

													}
												}


											}




										}

									}

			}
			pi+=first_seg;
		}
		for (int i = tau + 2-k; i<tau + 2 ; i++){
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr[i].check(words[*it1] + p, last_seg);
								if (v){

									if (v->size()>0){

										for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){

											if (verified[*it] != *it1){
												if (first_match_pair[*it].first == *it1){
													if (first_match_pair[*it].second != i){

														verified[*it] = *it1;
														if (!newFilter(*it1, *it, strlen(words[*it1]))){
															continue;
														}
															cand_l++;
															int d = LevenshteinDistance_length_aware_modified(words[*it1], words[*it], strlen(words[*it1]), len, tau);
															if (d <= tau){

																matched_pair++;
																matched_strings.push_back(make_pair(*it1, *it));
															}
													}
												}
												else{

													first_match_pair[*it].first = *it1;
													first_match_pair[*it].second = i;

												}

											}
										}
									}

				}

			}
			pi+=last_seg;
		}
		partion_tau_2_tree_ind_hist_index(words[*it1],  len, *it1);
	}
	return cand_l;
}
int passjoin::R_S_join(int l,int b0,int b1,int len,int B0,int B1,char**words){
	InvList_Seg* curr;
	int cand_l = 0;


		int first_seg = utils1.floor(l, tau + 2);
		int k = l - (first_seg)*(tau + 2);
		int last_seg = utils1.ceiling(l, tau + 2);
		curr=L_B0_B1[l-start][b0][b1];
		int delta=len-(l);
	for(auto it1=strings_indexed[len-start][B0][B1].begin();it1!=strings_indexed[len-start][B0][B1].end();++it1){
		int pi = 0;
		for (int i = 0; i<tau + 2 - k; i++){
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr[i].check(words[*it1] + p, first_seg);
								if (v){

										if (v->size()>0){

											for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
												if (verified[*it] != *it1){
													if (first_match_pair[*it].first == *it1){
														if (first_match_pair[*it].second != i){

															verified[*it] = *it1;
															if (!newFilter(*it1, *it, strlen(words[*it1]))){
															continue;
															}
																cand_l++;
																int d = LevenshteinDistance_length_aware_modified(words[*it1], words[*it], strlen(words[*it1]), l, tau);
																if (d <= tau){

																	matched_pair++;
																	matched_strings.push_back(make_pair(*it1, *it));

															}

														}
													}
													else{

														first_match_pair[*it].first = *it1;
														first_match_pair[*it].second = i;

													}
												}


											}




										}

									}

			}
			pi+=first_seg;
		}
		for (int i = tau + 2-k; i<tau + 2 ; i++){
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr[i].check(words[*it1] + p, last_seg);
								if (v){

									if (v->size()>0){

										for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){

											if (verified[*it] != *it1){
												if (first_match_pair[*it].first == *it1){
													if (first_match_pair[*it].second != i){

														verified[*it] = *it1;
														if (!newFilter(*it1, *it, strlen(words[*it1]))){
															continue;
														}
															cand_l++;
															int d = LevenshteinDistance_length_aware_modified(words[*it1], words[*it], strlen(words[*it1]), l, tau);
															if (d <= tau){

																matched_pair++;
																matched_strings.push_back(make_pair(*it1, *it));
															}
													}
												}
												else{

													first_match_pair[*it].first = *it1;
													first_match_pair[*it].second = i;

												}

											}
										}
									}

				}

			}
			pi+=last_seg;
		}
	}
	return cand_l;
}

int passjoin::candidate_tau_plus_two_reverse(char *x, int x_len, int pos_x, char ** words, passjoin& p1){
	int cand_l = 0;
	int current = -1;
	InvList_Seg* curr;
	for (int l = x_len; l <= x_len + tau; l++){


		int delta = x_len - l;

		if ((end - l) < 0){
			continue;
		}
		int l_tree_index = l - start;
		int first_seg = utils1.floor(l, tau + 2);
		int k = l - (first_seg)*(tau + 2);
		int last_seg = utils1.ceiling(l, tau + 2);
		int pi = 0;
		for (int i = 0; i<tau + 2 - k; i++){
			curr = &L2[l_tree_index][i];

			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){

				auto v = curr->check(x + p, first_seg);
				if (v){

					if (v->size()>0){

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != pos_x){



								if (first_match[*it] == pos_x){
									verified[*it] = pos_x;
									if (filter_SSE(pos_x, *it, x_len, l)){
										cand_l++;
										if (p1.matched_groups[pos_x].count(*it)){
											matched_pair++;
											matched_strings.push_back(make_pair(pos_x, *it));

										}
										else if (is_there_overlapping(pos_x, *it, p1)){
											if (pos_x == 36281 && *it == 36291){
												cout << "aaaaa" << endl;
											}
											matched_pair++;
											matched_strings.push_back(make_pair(pos_x, *it));

										}
										else{
											int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
											if (d <= tau){

												matched_pair++;
												matched_strings.push_back(make_pair(pos_x, *it));

											}
											else if (d >= tau + 1 + tau / 2){
												for (std::vector<int>::iterator it1 = p1.matched_groups_merge[*it].begin(); it1 != p1.matched_groups_merge[*it].end(); ++it1){
													verified[*it1] = pos_x;
												}
											}
										}

										/*					cand_l++;
															if (p1.matched_groups[pos_x].count(*it)){
															matched_pair++;
															matched_strings.push_back(make_pair(pos_x, *it));

															}
															else {
															if (min(x_len, l)*(tau + 1) > (p1.matched_groups_merge[pos_x].size() + p1.matched_groups_merge[*it].size())){
															if (is_there_overlapping(pos_x, *it, p1)){
															matched_pair++;
															matched_strings.push_back(make_pair(pos_x, *it));

															}
															else{
															int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
															if (d <= tau){

															matched_pair++;
															matched_strings.push_back(make_pair(pos_x, *it));

															}

															}
															}
															else{
															int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
															if (d <= tau){

															matched_pair++;
															matched_strings.push_back(make_pair(pos_x, *it));

															}

															}
															}

															*/

									}
								}

								else{


									/*first_match_pair[*it].first = pos_x;
									first_match_pair[*it].second = i;*/
									first_match[*it] = pos_x;
								}
							}


						}




					}

				}


			}
			pi += first_seg;
		}

		for (int i = tau + 2 - k; i<tau + 2; i++) {
			curr = &L2[l_tree_index][i];
			int pmin = max(pi - (i), pi + delta - (tau + 1) + i);
			int pmax = min(pi + (i), pi + delta + (tau + 1) - i);
			for (int p = pmin; p <= pmax; p++){

				auto v = curr->check(x + p, last_seg);
				if (v){

					if (v->size()>0){

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){

							if (verified[*it] != pos_x){



								if (first_match[*it] == pos_x){
									verified[*it] = pos_x;
									if (filter_SSE(pos_x, *it, x_len, l)){
										cand_l++;
										if (p1.matched_groups[pos_x].count(*it)){
											matched_pair++;
											matched_strings.push_back(make_pair(pos_x, *it));

										}
										else if (is_there_overlapping(pos_x, *it, p1)){
											if (pos_x == 36281 && *it == 36291){
												cout << "aaaaa" << endl;
											}
											matched_pair++;
											matched_strings.push_back(make_pair(pos_x, *it));

										}
										else{
											int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
											if (d <= tau){

												matched_pair++;
												matched_strings.push_back(make_pair(pos_x, *it));

											}
											else if (d >= tau + 1 + tau / 2){
												for (std::vector<int>::iterator it1 = p1.matched_groups_merge[*it].begin(); it1 != p1.matched_groups_merge[*it].end(); ++it1){
													verified[*it1] = pos_x;
												}
											}
										}

									}



								}
								else{


									/*	first_match_pair[*it].first = pos_x;
									first_match_pair[*it].second= i;*/
									first_match[*it] = pos_x;
								}

							}
						}
					}

				}
			}
			pi += last_seg;

		}

	}











	return cand_l;
}

int passjoin::candidate_extension_mutli(char *x, int x_len, int pos_x, char ** words){
	int cand_l = 0;
	InvList_Seg* curr;

	int first_seg_x = utils1.floor(x_len, tau + 1);
	int k_x = x_len - (first_seg_x)*(tau + 1);
	int last_seg_x = utils1.ceiling(x_len, tau + 1);
	for (int l = x_len - tau; l <= x_len; l++){
		if ((l - start) < 0){
			continue;
		}
		int delta = x_len - l;
		int first_seg = utils1.floor(l, tau + 1);
		int k = l - (first_seg)*(tau + 1);
		int last_seg = utils1.ceiling(l, tau + 1);
		int pi = 0;
		for (int i = 0; i<tau + 1 - k; i++){
			curr = &L2[l - start][i];
			int pmin = max(pi - (i), pi + delta - tau + i);
			int pmax = min(pi + (i), pi + delta + tau - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr->check(x + p, first_seg);
				if (v){
					if (v->size()>0){
						int tau_l = i;
						int tau_r = tau - i;
						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != pos_x){
								if (!multi_match(x, words[*it], delta, first_seg_x, last_seg_x, k_x)){
									verified[*it] = pos_x;
									continue;

								}
								int d_l = LevenshteinDistance_length_aware_modified(x, words[*it], 0, 0, p - 1, pi - 1, tau_l);

								/*cout << "left distance:" << '\0' << d_l << endl;
								cout << "left tau:" << '\0' << tau_l << endl;
								*/
								if (d_l <= tau_l){

									int d_r = LevenshteinDistance_length_aware_modified(x, words[*it], p + first_seg, pi + first_seg, x_len - 1, strlen(words[*it]) - 1, tau_r);
									if (d_r <= tau_r){
										verified[*it] = pos_x;

										matched_pair++;
										matched_strings.push_back(make_pair(pos_x, *it));
										/*myfile << x << endl;
										myfile << ',' << endl;
										myfile << words[*it] << endl;
										myfile << "<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;*/

									}
								}

							}
						}
					}
				}

			}
			pi += first_seg;
		}

		for (int i = tau + 1 - k; i<tau + 1; i++) {
			curr = &L2[l - start][i];
			int pmin = max(pi - (i), pi + delta - tau + i);
			int pmax = min(pi + (i), pi + delta + tau - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr->check(x + p, last_seg);
				if (v){
					if (v->size()>0){
						int tau_l = i;
						int tau_r = tau - i;
						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != pos_x){
								if (!multi_match(x, words[*it], delta, first_seg_x, last_seg_x, k_x)){
									verified[*it] = pos_x;
									continue;

								}
								int d_l = LevenshteinDistance_length_aware_modified(x, words[*it], 0, 0, p - 1, pi - 1, tau_l);
								if (d_l <= tau_l){

									int d_r = LevenshteinDistance_length_aware_modified(x, words[*it], p + last_seg, pi + last_seg, x_len - 1, strlen(words[*it]) - 1, tau_r);
									if (d_r <= tau_r){
										verified[*it] = pos_x;
										matched_pair++;
										matched_strings.push_back(make_pair(pos_x, *it));
										/*	myfile << x << endl;
										myfile << ',' << endl;
										myfile << words[*it] << endl;
										myfile << "<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;*/
									}
								}
							}
						}
					}
				}

			}
			pi += last_seg;
		}
	}

	return cand_l;
}

int passjoin::candidate_iterative_multi_original_len_tree_ind(char *x, int x_len, int pos_x, char ** words){

	int cand_l = 0;


	InvList_Seg* curr;
	for (int l = x_len - tau; l <= x_len; l++){


		int delta = x_len - l;
		if ((l - start) < 0){
			continue;
		}
		int first_seg = utils1.floor(l, tau + 1);
		int k = l - (first_seg)*(tau + 1);
		int last_seg = utils1.ceiling(l, tau + 1);
		int pi = 0;
		for (int i = 0; i<tau + 1 - k; i++){
			curr = &L2[l - start][i];
			int pmin = max(pi - (i), pi + delta - tau + i);
			int pmax = min(pi + (i), pi + delta + tau - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr->check(x + p, first_seg);

				if (v){

					if (v->size()>0){
						int tau_l = i;
						int tau_r = tau - i;

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != pos_x){









								if (!newFilter(pos_x, *it, x_len)){
									verified[*it] = pos_x;

									continue;
								}
								cand_l++;
								if (first_match[*it] != pos_x){

									first_match[*it] = pos_x;

									if (iterativeVerify(words[*it], x, i, first_seg, last_seg, k, 0, 0, pi - 1, p - 1, pos_x, (*it), tau_l, left)){
										int d_l = LevenshteinDistance_length_aware_modified(x, words[*it], 0, 0, p - 1, pi - 1, tau);
										if (iterativeVerify(words[*it], x, i, first_seg, last_seg, k, pi + first_seg, p + first_seg, strlen(words[*it]) - 1, x_len - 1, pos_x, *it, tau_r, right)){

											int d_r = LevenshteinDistance_length_aware_modified(x, words[*it], p + first_seg, pi + first_seg, x_len - 1, strlen(words[*it]) - 1, tau);

											if (d_l + d_r <= tau){
												verified[*it] = pos_x;
												matched_pair++;



											}

										}
									}
								}
								else{
									int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
									if (d <= tau){
										verified[*it] = pos_x;
										matched_pair++;


									}
								}

							}
						}


					}
				}


			}
			pi += first_seg;
		}

		for (int i = tau + 1 - k; i<tau + 1; i++) {
			curr = &L2[l - start][i];
			int pmin = max(pi - (i), pi + delta - tau + i);
			int pmax = min(pi + (i), pi + delta + tau - i);
			for (int p = pmin; p <= pmax; p++){
				auto v = curr->check(x + p, last_seg);

				if (v){

					if (v->size()>0){
						int tau_l = i;
						int tau_r = tau - i;

						for (std::vector<int>::iterator it = v->begin(); it != v->end(); ++it){
							if (verified[*it] != pos_x){





								/*if (!utils1.LCS(x, words[*it], tau + 2, 2)){
									verified[*it] = pos_x;
									continue;
								}*/
								if (!newFilter(pos_x, *it, x_len) ){
									verified[*it] = pos_x;

									continue;
								}
								cand_l++;
								if (first_match[*it] != pos_x){
									first_match[*it] = pos_x;
									if (iterativeVerify(words[*it], x, i, first_seg, last_seg, k, 0, 0, pi - 1, p - 1, pos_x, *it, tau_l, left)){

										int d_l = LevenshteinDistance_length_aware_modified(x, words[*it], 0, 0, p - 1, pi - 1, tau);

										if (iterativeVerify(words[*it], x, i, first_seg, last_seg, k, pi + last_seg, p + last_seg, strlen(words[*it]) - 1, x_len - 1, pos_x, *it, tau_r, right)){

											int d_r = LevenshteinDistance_length_aware_modified(x, words[*it], p + last_seg, pi + last_seg, x_len - 1, strlen(words[*it]) - 1, tau);


											if (d_l + d_r <= tau){
												verified[*it] = pos_x;
												matched_pair++;

											}
										}
									}
								}
								else{
									int d = LevenshteinDistance_length_aware_modified(x, words[*it], x_len, l, tau);
									if (d <= tau){
										verified[*it] = pos_x;
										matched_pair++;


									}
								}
							}
						}

					}
				}


			}
			pi += last_seg;
		}
	}




	return cand_l;
}

bool passjoin::filter(int pos_x, int pos_y, int x_len, int y_len){
	int delta = 0;
	for (int i = 0; i < 27; i++){
		delta += abs(histograms[pos_x][i] - histograms[pos_y][i]);

	}
	return delta <= 2 * tau - abs(x_len - y_len);
}

bool passjoin::filter_SSE(int pos_x, int pos_y, int x_len, int y_len) {

	int delta = 0;
	int i;
	__m128 X, Y, Z;
	__m128 absval;
	static const __m128 SIGNMASK =
		_mm_castsi128_ps(_mm_set1_epi32(0x80000000));
	for (int i = 0; i < 28; i += 4){
		X = _mm_load_ps(&histograms_SSE[pos_x][i]);
		Y = _mm_load_ps(&histograms_SSE[pos_y][i]);
		X = _mm_sub_ps(X, Y);
		absval = _mm_andnot_ps(SIGNMASK, X);
		Z = _mm_add_ps(absval, Z);

	}


	for (i = 0; i < 4; i++) {
		delta += (int)Z[i];
	}

	return delta <= 2 * tau - abs(x_len - y_len);

}
bool passjoin::is_there_overlapping(int pos_x, int it_ind, passjoin &p1) {
	for (std::vector<int>::iterator it = p1.matched_groups_merge[pos_x].begin(); it != p1.matched_groups_merge[pos_x].end(); ++it){

		mark_overlapping[*it] = pos_x;
	}
	for (std::vector<int>::iterator it = p1.matched_groups_merge[it_ind].begin(); it != p1.matched_groups_merge[it_ind].end(); ++it){
		if (mark_overlapping[*it] == pos_x){

			return 1;
		}
	}

	return 0;

}
bool passjoin::backword_filtering_unordered_map_based(char * x, int len_x, int c_ind, int c_len, int tau) {
	int first_seg = utils1.floor(len_x, tau + 1);
	int k = len_x - (first_seg)*(tau + 1);
	int last_seg = utils1.ceiling(len_x, tau + 1);
	int pi = 0;
	unordered_map <Key_M, int>**curr = substrings[c_ind][len_x - c_len];
	for (int i = 0; i < tau + 1 - k; i++){
		Key_M k1(x + pi, first_seg);
		if (curr[i]->count(k1)){
			return 1;
		}
		pi += first_seg;
	}
	for (int i = tau + 1 - k; i < tau + 1; i++){
		Key_M k1(x + pi, last_seg);
		if (curr[i]->count(k1)){
			return 1;
		}
		pi += last_seg;
	}
	return 0;
}
// bool passjoin::backword_filtering_Trie_based(char * x, int len_x, int c_ind, int c_len, int tau) {
	// int first_seg = utils1.floor(len_x, tau + 1);
	// int k = len_x - (first_seg)*(tau + 1);
	// int last_seg = utils1.ceiling(len_x, tau + 1);
	// int pi = 0;
	// Trie**curr = substringss[c_ind][len_x - c_len];
	// for (int i = 0; i < tau + 1 - k; i++){
		// if (curr[i]->searchWord(x + pi, first_seg)){
			// return 1;
		// }
		// pi += first_seg;
	// }
	// for (int i = tau + 1 - k; i < tau + 1; i++){
		// Key_M k1(x + pi, last_seg);
		// if (curr[i]->searchWord(x + pi, last_seg)){
			// return 1;
		// }
		// pi += last_seg;
	// }
	// return 0;
// }

bool passjoin::newFilter(int pos_x, int pos_it,int x_len) {

	int res = utils1.commonChar(histograms_SSE[pos_x], histograms_SSE[pos_it]);

	return res>=x_len - tau;

}
bool passjoin::newFilter_first_second(int pos_x, int pos_it,int x_len,int it_len) {
	int len_f=x_len/2;
	int len_e=x_len-len_f;
	int len_f1=it_len/2;
	int len_e1=it_len-len_f1;
	int delta=len_f-len_f1;
	int delta1=len_e-len_e1;
	int res = utils1.commonChar(histograms_first[pos_x], histograms_first[pos_it]);
	int res1 = utils1.commonChar(histograms_second[pos_x], histograms_second[pos_it]);
	return res>=len_f-tau-delta&&res1>=len_e-tau-delta1;

}

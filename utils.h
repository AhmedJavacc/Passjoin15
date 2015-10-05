#ifndef utils_Hu_INCLUDED
#define utils_Hu_INCLUDED
#include <string>
#include <iostream>
#include <xmmintrin.h>
using namespace std;
class utils{
public :
	inline int ceiling(int x, int y){
		return 1 + ((x - 1) / (y));
	}

	inline int floor(int x, int y){
		return x / y;
	}
	int NumberOfSetBits(int i)
	{
		i = i - ((i >> 1) & 0x55555555);
		i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
		return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
	}
	
	int countChar(char*a){
		//char a = 'a';
		int res = 0;
		for (int i = 0; i < strlen(a); i++){
			if (a[i] >= 'a'&&a[i] <= 'z'){
				res |= (1 << (int)(a[i] - 'a'));
			}
			else{
				res |= (1 << 26);
			}
		}
		return res;
	}

void combinationUtil(char * arr, char* data, int start, int end, int index, int r, unordered_map<string, int>&a)
	{
		if (index == r)
		{
			data[r] = '\0';
			string data1 = string(data);
			//cout << data1 << endl;
			auto it = a.find(data1);
			if (it!=a.end()){
				(*it).second += 1;
			}
			else{
				a.emplace(string(data), 1);
			}
			return;
		}


		for (int i = start; i <= end && end - i + 1 >= r - index; i++)
		{
			if (index == 0){
				data = new char[r + 1];
			}
			data[index] = arr[i];
			combinationUtil(arr, data, i + 1, end, index + 1, r, a);
		}
	}

	void printCombination(char * arr, int n, int q, unordered_map<string, int>&a)
	{

		char * data = new char[q + 1];
		combinationUtil(arr, data, 0, n - 1, 0, q, a);

	}
	bool LCS(char * X, char * Y,int len,int q)
	{
	
		
		vector< vector<int> > c(2, vector<int>(len + 1, 0));
		int i, j;
		for (i = 1; i <= len; i++)
		{
			for (j = 1; j <= len; j++)
			{
				if (X[i - 1] == Y[j - 1])
					c[1][j] = c[0][j - 1] + 1;
				else
					c[1][j] = max(c[1][j - 1], c[0][j]);
			}
			for (j = 1; j <= len; j++){
				if (c[1][j] >= q){
					return 1;
				}
				c[0][j] = c[1][j];
			}
		}
		return (c[1][len])>=q?1:0;
	}
	int commonChar(float *m1, float *m2){
		__m128 X, Y, Z;
		float prod;
		int i;
		for (i = 0; i<28; i += 4) {
			X = _mm_load_ps(&m1[i]);
			Y = _mm_load_ps(&m2[i]);
			X = _mm_min_ps(X, Y);
			Z = _mm_add_ps(X,Z);
		}

		for (i = 0; i<4; i++) {
			prod += Z[i];
		}
		int res = (int)prod;
		return res;
	}
};
#endif
//#ifdef test
#include "read.h"

#include <map>
#include <iostream>
#include <math.h>

using namespace std;
int  main(int argc, char** argv){
	map<int,int> count;
	char * input_file = argv[1];
	ReadFile r(input_file);
	r.sortFile();
				for (int i=0; i <r.wcnt; i++){
					count[strlen(r.words[i])]++;

				}
				cout<<argv[1]<<endl;
for(auto it=count.begin();it!=count.end();++it){
	cout<<it->first<<" "<<it->second<<endl;
}

cout<<"*******************************************"<<endl;
return 0;
}
//#endif

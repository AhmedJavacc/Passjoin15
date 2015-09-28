#define _CRT_SECURE_NO_WARNINGS
#include "expr.h"
#include "read.h"
ReadFile::ReadFile(char *filename){
       auto start=std::chrono::system_clock::now();
	FILE * fp=fopen(filename,"rb");
	long sz;
	//get the size of file
	fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	buffer=(char*)malloc(sz*sizeof(char)+10);
	fread(buffer,sizeof(char),sz,fp);
	fclose(fp);
	long cnt=0;
	for(long i=0;i<sz;i++){
		if(buffer[i]=='\n'){
			buffer[i]='\0';
			cnt++;
		}
	}
	words=(char **) malloc(sizeof(char*)*cnt);
	words[0]=&(buffer[0]);

	wcnt=cnt;
	cnt=1;
	for(long i=1;i<sz;i++){
		if(buffer[i]=='\0'){
			words[cnt++]=&(buffer[i+1]);


		}
	}
   auto end = chrono::high_resolution_clock::now();
   auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
  EXPR::read_time=ms;

}
bool length_sort(const char * x, const char * y){
	const size_t lhsLength = strlen(x);
	const size_t rhsLength = strlen(y);
	if(lhsLength==rhsLength)
		return strcmp(x,y)<=0;
	return lhsLength < rhsLength;
}

void ReadFile::sortFile(){
	  auto start=std::chrono::system_clock::now();
	  sort(words,words+wcnt,length_sort);
	  auto end = chrono::high_resolution_clock::now();
	  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	  EXPR::sort_time=ms;
}
ReadFile::ReadFile(){
words=NULL;
buffer=NULL;

}

ReadFile::~ReadFile(){
//if(words) free(words);
//if(buffer) free(buffer);
words=NULL;
buffer=NULL;

}




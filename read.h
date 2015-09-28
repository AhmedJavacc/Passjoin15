#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <chrono>
#include<iostream>

using namespace std;

using namespace std;
class ReadFile{
    public:
    char *buffer;
    char ** words;
    long wcnt;
    bool is_sorted=false;

    ReadFile(char *filename);
    void sortFile();
    long get_number_strings();
    int get_longest_strings();
    ReadFile();
    ~ReadFile();
};


#endif // READFILE_H_INCLUDED


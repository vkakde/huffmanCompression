/*@desc HuffMan Encoding 
 *@author Rahul Sharma, Vishwajeet Kakde
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <algorithm>
#include <malloc.h>
#include <queue> 
#include <ctype.h>
#include <windows.h>
#include <math.h>

using namespace std;

struct MinHeapNode;

struct compare;

bool sortAscendingByFrequency(const pair<char,int> &HuffmanPair_1, const pair<char,int> &HuffmanPair_2);

bool sortDescendingByFrequency(const pair<char,int> &HuffmanPair_1, const pair<char,int> &HuffmanPair_2);

bool sortCodeByBits(const pair<char,string> &HuffmanPair_1, const pair<char,string> &HuffmanPair_2);

void printCode(const vector< pair <char, string> > &freq,string tempFilePath);

void printCodes(struct MinHeapNode* root, string codeString, string tempFilePath);

void GenerateHuffmanCodes(const vector< pair <char, int> > &Huffman_Char_Freq_Vector, string outputFilePath, string tempFilePath);
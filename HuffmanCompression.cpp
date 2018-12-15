#include "HuffmanCompression.hpp"

struct MinHeapNode{
    char inputCharacter;  // One of the input characters
    int characterFreq; // Frequency of the character
    MinHeapNode *left, *right; // Left and right child
 
    MinHeapNode(char inputCharacter,  int characterFreq){
        left = right = NULL;
        this->inputCharacter = inputCharacter;
        this->characterFreq = characterFreq;
    }
};

struct compare{
    bool operator()(MinHeapNode* left, MinHeapNode* right){
        return (left->characterFreq > right->characterFreq);
    }
};

bool sortAscendingByFrequency(const pair<char,int> &HuffmanPair_1, const pair<char,int> &HuffmanPair_2){
    return (HuffmanPair_1.second < HuffmanPair_2.second);
}

bool sortDescendingByFrequency(const pair<char,int> &HuffmanPair_1, const pair<char,int> &HuffmanPair_2){
    return (HuffmanPair_1.second > HuffmanPair_2.second);
}

bool sortCodeByBits(const pair<char,string> &HuffmanPair_1, const pair<char,string> &HuffmanPair_2){
	return (HuffmanPair_1.second > HuffmanPair_2.second);
}

void printCode(const vector< pair <char, string> > &freq,string tempFilePath){
	std::fstream myFile; //change to outputfile
	char defaultChar = '#';
			
	for (int i=0; i<freq.size(); i++){
        if(freq[i].first == defaultChar){
            continue;
        }
        else{
            std::fstream fs;
            myFile.open(tempFilePath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
            myFile << "   "<<freq[i].first << " " << freq[i].second << "\n";
            myFile.close();
        }			
	}
}

void printCodes(struct MinHeapNode* root, string codeString, string tempFilePath){
	vector< pair <char, string> > freq;
	char defaultChar = '#';
	
    if (!root){
		return;
    }
 
    if (root->inputCharacter != defaultChar){
        freq.push_back( make_pair(root->inputCharacter, codeString));
    }
    
    // we can have designated strings for 0 and 1
    printCodes(root->left, codeString + "0", tempFilePath);
    printCodes(root->right, codeString + "1", tempFilePath);
    printCode(freq, tempFilePath);
}

void GenerateHuffmanCodes(const vector< pair <char, int> > &Huffman_Char_Freq_Vector, string outputFilePath, string tempFilePath){
    struct MinHeapNode *left, *right, *top;
    int size;
    int counter = 0;
    std::fstream myFile; //change to outputfile
    //string tempFileName = "\temp.txt";
    char defaultChar = '#';
    
    char symbol;
    string huffmanCode;
    vector <pair <char, string> >  patVec;
    map<char, string> HuffmanMap;
	
    size = Huffman_Char_Freq_Vector.size();
    
    //tempFilePath = tempFilePath + tempFileName;
		
    // Create a min heap & insert all characters of data
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
	
	//change i to index
	for (int i = 0; i < size; ++i){
        minHeap.push(new MinHeapNode(Huffman_Char_Freq_Vector[i].first, Huffman_Char_Freq_Vector[i].second));
    }
 
    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1){
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        minHeap.pop();
 
        right = minHeap.top();
        minHeap.pop();
 
        top = new MinHeapNode(defaultChar, left->characterFreq + right->characterFreq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
 
    // Print Huffman codes using the Huffman tree built above
    printCodes(minHeap.top(), "",tempFilePath);
    
    std::ifstream inFile(tempFilePath.c_str());
    
    while (inFile >> symbol >> huffmanCode){
        patVec.push_back( make_pair(symbol, huffmanCode) );
    }
    
    inFile.close();
    
    for (int i=0; i<patVec.size(); i++){
        HuffmanMap[patVec[i].first] = patVec[i].second;        
    }
    
    remove(tempFilePath.c_str());
		
	map<char, string>::iterator it;
	
	myFile.open(outputFilePath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	myFile <<"\n";
	myFile << "  Symbol" << "          " <<"HuffmanCode";
	myFile <<"\n----------     ----------------";
	myFile <<"\n";
	myFile.close();
        
	for (int i=0; i<Huffman_Char_Freq_Vector.size(); i++){
        myFile.open(outputFilePath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
        myFile << "   "<<Huffman_Char_Freq_Vector[i].first <<"              	" << HuffmanMap[Huffman_Char_Freq_Vector[i].first] << "\n";
        myFile.close();
    }
    
    int totalBits = 0;
    for(int i=0; i<Huffman_Char_Freq_Vector.size(); i++){
        int freq = Huffman_Char_Freq_Vector[i].second;
        int encodingLength = HuffmanMap[Huffman_Char_Freq_Vector[i].first].length();
        totalBits += freq * encodingLength;
        // cout<<"\n\nTotal Bits for symbol "<<Huffman_Char_Freq_Vector[i].first<<": "<<freq<<" * "<<encodingLength<<":  "<<freq*encodingLength;
    }
    myFile.open(outputFilePath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
    myFile << "\n\nTotal Bits: "<<totalBits<<"\n";
    myFile.close();
}

int main(int argc, char **argv){
    vector<char> ReadFileVector; 
    int counter = 0;
    int initialcount = 1;
    int currentcount;
    map<char, int> HuffmanMap;
    vector<pair <char, int> > Huffman_Char_Freq_Vector;
    ifstream inFile;
    string tempFilePath;
    
    std::fstream myFile; //change to outputfile
    string inputFilePath;
    string outputFilePath="";
    string outputFileName = "\\output.dat";
    string tempFileName = "\\temp.txt";
    
    cout <<"\n\n>>>>>>>>>>>-    WELCOME TO HUFFMAN ENCODER    -<<<<"<<"\n\nEnter full input DAT file path+name (example- C:\\Users\\User1\\Desktop\\input.dat):  ";
    cin>>inputFilePath;
    inFile.open(inputFilePath.c_str(), ios::binary); 
    while(!inFile.is_open()){
        cout<<"\n\nFile open failed. Try again!";
        cout<<"\n\nEnter full input DAT file path+name (example- C:\\Users\\User1\\Desktop\\input.dat):  ";
        cin>>inputFilePath;
        inFile.open(inputFilePath.c_str(), ios::binary); 
    }
    
    cout<<"\n\nEnter Output File Location (example- C:\\Users\\User1\\Desktop):  ";
    cin>>outputFilePath;
        
    tempFilePath = outputFilePath + tempFileName;
    outputFilePath = outputFilePath + outputFileName;
    
    remove(outputFilePath.c_str()) ; //purge output.dat if  it exists already
    remove((tempFilePath+tempFileName).c_str()); //purge temp file if it exists already
  
    // get length of input file
    inFile.seekg(0, std::ios::end);
    size_t file_size_in_byte = inFile.tellg();
    ReadFileVector.resize(file_size_in_byte);
    inFile.seekg(0, std::ios::beg);
    inFile.read(&ReadFileVector[0], file_size_in_byte);
    
    inFile.close();
    
    // translate vector contents into a map (character, frequency)
    for(counter=0; counter < ReadFileVector.size(); counter++){
        char element = ReadFileVector[counter];
        // read and process characters and numbers
        if(((int)element >= 65 && (int)element <= 122) || ((int)element >= 48  && (int)element <= 57)){
            if(HuffmanMap.empty()){                                 // if map is empty, add element with frequency initialized to 1
                HuffmanMap[element] = initialcount;
            }
            else if(HuffmanMap.count(element) == 0){                // if map contains no entry for element, add element with frequency initialized to 1
                HuffmanMap[element] = initialcount;
            }
            else{                                                   // if map contains an entry for element, simply increment its frequency by 1
                currentcount = (int)HuffmanMap.at(element);
                HuffmanMap[element] = currentcount+initialcount;
            }
        }
        // ignore special characters and white space
        else{
            continue;
        }
    }

    //iterator to see the push map content into vector
    map<char, int>::iterator it;
    
    // translate the map contents into a vector of pairs
    for (it=HuffmanMap.begin(); it!=HuffmanMap.end(); ++it){
        Huffman_Char_Freq_Vector.push_back( make_pair(it->first,it->second) );
    }
    
    //sorting vector of pairs in DESC order of frequency (vector.second)
    sort(Huffman_Char_Freq_Vector.begin(), Huffman_Char_Freq_Vector.end(), sortDescendingByFrequency);
    
    myFile.open(outputFilePath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
    
    myFile <<"  Symbol" <<"          " <<"Frequency";
    myFile <<"\n----------     ---------------";
    myFile <<"\n";
    myFile.close();
						
	//writing character-frequency pairs to file output.dat
	for (int i=0; i<Huffman_Char_Freq_Vector.size(); i++){
        myFile.open(outputFilePath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
        myFile << "   "<<Huffman_Char_Freq_Vector[i].first<<"  			" << Huffman_Char_Freq_Vector[i].second << "\n";
        myFile.close();
    }

    cout<<"\n\nEncoding ...";
    GenerateHuffmanCodes(Huffman_Char_Freq_Vector, outputFilePath, tempFilePath);
    Sleep(1500);
    cout<<"\n\nEncoded successfully. View output file at: "<<outputFilePath;
    Sleep(5000);
    
    return 0;
}
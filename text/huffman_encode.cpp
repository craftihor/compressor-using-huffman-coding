//libraries
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>

using namespace std;

string str;
vector<pair<char,string>> charactermapping;
vector<int> Huffcode;
int charactermappingcount = 0;
int def_charactercount = 0;
char block = char(254);//'■' symbol used in tree
string codes;
char filename[50];
char codefilename[50];

class write{
private:
  char buff;
  int tbits;
  ostream& out;
public:
  write(ostream & os) : out(os),buff(0),tbits(0){

  }
  void flush();
  void writebit(int i);
};

void write::flush(){
  out.put(buff);
  out.flush();
  buff = tbits = 0;
}

void write::writebit(int i){
  if( i == -1){
    flush();
  }
  if(tbits == 8){
    flush();
  }
  //bit masking
  unsigned char mask = 1;
  if(i == 1){
    mask = mask << (7 - tbits);
    buff = buff | mask;
  }
  if(i == 0){
    mask = mask << (7 - tbits);
    mask = ~mask;
    buff = buff & mask;
  }
  tbits++;
}

struct huffman_tree{
  int data;
  int frequency;
  huffman_tree *left , *right;
  huffman_tree(int data , int frequency){
    left = right = NULL;
    this->data = data;
    this->frequency = frequency;
  }
};

struct compare{
  bool operator()(huffman_tree* l, huffman_tree* r){
    return (l->frequency > r->frequency);
  }
};

//function to calculate frequency of each character in the file
void calc_frequency(int frequency[] , char filename[]){
  char ch,ch1;
  int temp;
  ifstream file;
  file.open(filename);
  if(!file.is_open()){
    std::cout << "Error !!! cannot open the file - "<<filename<< '\n';
    exit(1);
  }
  while(file.get(ch)){
    if(ch >=32 && ch < 255){
      charactermapping.push_back(make_pair(ch,""));
      charactermappingcount++;
    }
    temp = int(ch);
    frequency[temp] = frequency[temp] + 1;
  }
  ch1 = char(129);//char value 129 == space
  charactermapping.push_back(make_pair(ch1,""));
  charactermappingcount++;
  file.close();
}

//For seperating occurring and non-occurring characters & to create actual frequency array & ASCII_values array
void def_character(int frequency[] , int actual_frequency[] , int ascii_values[]){
  int temp = 0;
  int temp1 = 0;
  for (size_t i = 32; i < 254; i++) {
    if(frequency[i] != 0){
      actual_frequency[temp] = frequency[i];
      ascii_values[temp1] = i;
      temp1++;
      temp++;
      def_charactercount++;
    }
  }
  actual_frequency[temp1] = 1; // For adding pseudo-EOF in actual_frequency & ASCII_values arrays
  ascii_values[temp] = 129;
  def_charactercount++;
}

//print frequncy Table
void print_frequency_table(int actual_frequency[] , int ascii_values[]){
  char ch;
  string str = "";
  str = str + "Space";
  std::cout << "\nfrequency Table of Characters Present in "<<filename<< '\n';
  std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << '\n';
  std::cout << "Characters\t\tFrequency" << '\n';
  std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << '\n';
  for (size_t i = 0; i < def_charactercount; i++) {
    ch = char(ascii_values[i]);
    if(ch == ' ')
       std::cout << "    "<<str<<"\t\t  "<<actual_frequency[i]<< '\n';
    else
       std::cout << "    "<<ch<<"\t\t  "<<actual_frequency[i]<< '\n';
  }
}

//function to print the character and the codes used for them
void print_huffman_codes(struct huffman_tree* root , string str){
  if(!root){
    return;
  }
  if(root->data != block){
    char temp = char(root->data);
    cout <<"\t    "<< temp << "\t\t\t  " << str << "\n";
    if(root->data == ' '){
      codes = codes + "_" + " " + str + "\n";
    }
    else
      codes = codes + temp + " " + str + "\n";
      for (size_t i = 0; i < charactermappingcount; i++) {
        if(charactermapping[i].first == temp){
          charactermapping[i].second = str;
        }
      }
  }
  print_huffman_codes(root->left , str + "0");
  print_huffman_codes(root->right , str + "1");
}

// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
priority_queue<huffman_tree*, vector<huffman_tree*>, compare> minHeap;

void build_huffman_tree(int data[] , int frequency[] , int size){
  struct huffman_tree *left, *right, *top;
  //creating a min heap & inserting all characters of ascii_values into data
  for (size_t i = 0; i < size; ++i) {
    minHeap.push(new huffman_tree(data[i], frequency[i]));
  }
  // Iterate while size of heap doesn't become 1
  while (minHeap.size() != 1) {
    //extracting the two min frequency items from the minHeap
    left = minHeap.top();
    minHeap.pop();
    right = minHeap.top();
    minHeap.pop();
    //creating a new internal node with data as '■' and frequency as the sum of two frequencies
    top = new huffman_tree(block, left->frequency + right->frequency);
    top->left = left;
    top->right = right;
    minHeap.push(top);
  }
  print_huffman_codes(minHeap.top(),"");
}

//converting the characters from charactermapping to an int vector
void converting_string_to_integer(){
  string temp;
  for (size_t i = 0; i < charactermapping.size(); i++) {
    temp = charactermapping[i].second;
    for (size_t j = 0; j < temp.size(); j++) {
      if(temp[j] == '1'){
        Huffcode.push_back(1);
      }
      else{
        Huffcode.push_back(0);
      }
    }
  }
  Huffcode.push_back(-1);
}

void printtree(struct huffman_tree* root , int indent){
  if(root != NULL){
    printtree(root->right,indent + 4);
    std::cout << setw(indent) << " " << (char)root->data << '\n';
    printtree(root->left,indent+4);
  }
}

void create_code_file(){
  ofstream out;
  char code_filename[32];
  std::cout << "\nEnter the name of the code file :: " << '\n';
  std::cin >> code_filename;
  out.open(code_filename,ios::out);
  for (size_t i = 0; i < codes.size() ; i++) {
    if(codes[i] != '\n'){
      out<<codes[i];
    }
    else
    out<<endl;
  }
  out.close();
}

void cal_compression_ratio(){
long double ori_size = charactermappingcount;
long double comp_size = Huffcode.size() / 8 ;
std::cout << "\n Compression ratio achieved :: "<< ((comp_size/ori_size)*100) << '\n';
}

//Driver program
int main() {
  int frequency[256];
  int ascii_values[256];
  int actual_frequency[256];
  char ch;
  string decode;
  std::cout << "\n+++++++++++++++++++++++++++++++++++++++++" << '\n';
  std::cout << "\t File compressor" << '\n';
  std::cout << "+++++++++++++++++++++++++++++++++++++++++\n" << '\n';
  std::cout << "Enter name of the file to be compressed : ";
  std::cin >> filename;
  //setting initial values for the arrays
  for (size_t i = 0; i < 255; i++) {
    ascii_values[i] = 0;
    frequency[i] = 0;
    actual_frequency[i] = 0;
  }
  calc_frequency(frequency,filename);//function to calculate frequency of each character in the file
  def_character(frequency,actual_frequency,ascii_values);//Make actual frequency array and ASCII values
  print_frequency_table(actual_frequency,ascii_values);//print frequency table
  std::cout << "\nCharacter Table with Huffman codes" << '\n';
  std::cout << "\n\tCharacter\t\tHuffman Code" << '\n';
  build_huffman_tree(ascii_values,actual_frequency,def_charactercount);//function to biuld huffman tree
  converting_string_to_integer();//converting the characters from charactermapping to an int vector
  std::cout << "\nHuffman tree : " << '\n';
  printtree(minHeap.top(),0);
  create_code_file();//function to create huffman codes as an txt file
  //naming the extension
  int len = strlen(filename);
  filename[len-1] = 'f';
  filename[len-2] = 'u';
  filename[len-3] = 'h';
  ofstream out;
  out.open(filename,ios::binary);
  std::cout << "\nThe Size of the Compressed File is "<<Huffcode.size()/8 << '\n';
  write temp(out);
  int temp1;
  std::cout << "\nWriting the Compressed File" << '\n';
  for (size_t i = 0; i < Huffcode.size(); i++) {
     temp1 = Huffcode[i];
     temp.writebit(temp1);
  }
  std::cout << "\ncompression successful!!!!!" << '\n';
  cal_compression_ratio();
  return 0;
}

//libraries
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>

using namespace std;

class BitwiseRead {
private:
  char buff;                       //buffer
  int nbits;                      //no of bits read by buffer
  istream& in;
public:
  //Initializing the BitwiseRead class for the istream as input
  BitwiseRead(istream & is);
 void fill();//fill the buffer from the input
  int readBit();
};

BitwiseRead::BitwiseRead(istream & is) : in(is){
  buff = 0;
  nbits = 8;
}

//function to fill the inputs in buffer
void BitwiseRead::fill(){
  buff = in.get();
  nbits = 0;
}
//function that reads the bits and fills the buffer from the input
int BitwiseRead::readBit(){
  if(nbits == 8){
    fill();
  }
  unsigned char mask = 1; //used to extract the nth bit among the current bit
  mask = mask << (7-nbits);
  mask = mask & buff;
  nbits++;
  if(mask == 0){
    return 0;
  }
  else{
    return 1;
  }
}

class huffman {
private:
  class node{
  public:
    char data;
    node *left,*right;

    node(char temp){
      data = temp;
      left = right = 0;
    }
  };
  typedef node *pointer;
public:
  huffman();
  void build_tree (ifstream & codes);
  void insert_node_in_tree ( char ch , string code);
  char decode (BitwiseRead &in);
  void print_huffman_tree (ostream & out,huffman::pointer root,int indent);
  void display_huffman_tree (ostream & out);
private:
  pointer root;
};

inline huffman::huffman(){
  root = new node('*');
}

inline void huffman::display_huffman_tree(ostream & out){
  print_huffman_tree(out, root , 0);
}

void huffman::build_tree(ifstream & codes){
  char ch;
  string code;
  std::cout << "\nCharacter Table with Huffman codes" << '\n';
  std::cout << "\n\tCharacter\t\tHuffman Code" << '\n';
  for(;;){
    if(codes.eof())  return ;
    codes >> ch >> code;
    cout << "\t    " << ch << " \t\t\t   " << code<<endl;
    if(ch == '_'){
      ch = ' ';
    }
    insert_node_in_tree(ch, code);
  }
}

//traverses each character in the code file and creates node along the path
void huffman::insert_node_in_tree( char ch , string code){
  huffman::pointer ptr;
  ptr = root;
  for (size_t i = 0; i < code.length(); i++) {
    switch (code[i]) {
      case '0':
         if(ptr->left == 0)
         ptr->left = new huffman::node('*');
         ptr = ptr->left;
         break;
      case '1':
            if(ptr->right == 0)
            ptr->right = new huffman::node('*');
            ptr = ptr->right;
            break;
      default:
            std::cerr << ">>> illegal character in code <<<" << '\n';
            exit(1);
    }
  }
  ptr->data = ch;
}

//function to decode the huffman tree
char huffman::decode(BitwiseRead &in){
  huffman::pointer ptr;
  ptr = root;
  int bit;
  while(true){
    bit = in.readBit();
    if(bit == 1){
      ptr = ptr->right;
    }
    if(bit ==0){
      ptr = ptr->left;
    }
    if(ptr->right == NULL || ptr->left == NULL){
      break;
    }
  }
  return (ptr->data);
}

void huffman::print_huffman_tree(ostream & out,huffman::pointer root,int indent){
  if(root!=0){
    print_huffman_tree(out,root->right,indent+4);
    out << setw(indent) << " " << root->data << endl;
    print_huffman_tree(out,root->left,indent+4);
  }
}

int main(){
  char data;
  char codes_filename[32];
  char decomp_filename[32];
  char filename[32];
  std::cout << "\n+++++++++++++++++++++++++++++++++++++++++" << '\n';
  std::cout << "\t File compressor" << '\n';
  std::cout << "+++++++++++++++++++++++++++++++++++++++++\n" << '\n';
  cout << "\n\nEnter name of code file: ";
  cin >> codes_filename;
  ifstream codestream(codes_filename);
  if(!codestream.is_open()){
    std::cout << "Error!! cannot open code file named " <<codes_filename<< '\n';
    exit(1);
  }
  huffman huff;
  std::cout << "\n\n Huffman codes used :: " << '\n';
  huff.build_tree (codestream);
  std::cout << "\n\n\n>>> huffman decoding tree <<<" << '\n';
  huff.display_huffman_tree(cout);
  std::cout << "\n\n Enter Name of the Compressed file ::  " << '\n';
  std::cin >> filename;
  ifstream fin;
  ofstream fout;
  std::cout << "Enter the name of the of decompressed file :: " << '\n';
  std::cin >> decomp_filename;
  fout.open(decomp_filename);
  fin.open(filename,ios::binary);
  BitwiseRead os(fin);
  if(!fin.is_open()){
    std::cout << "Error !! cannot open the compressed file ." << '\n';
    exit(1);
  }
  std::cout << "\n>>> Decompressing might take a lil Longer <<<" << '\n';
  char qwe;
  qwe = char(129);
  while(true){
    data = huff.decode(os);
    if(data == qwe){
      break;
    }
    fout << data;
  }
  std::cout << "\nDecompression done Successfully" << '\n';
  return 0;
}

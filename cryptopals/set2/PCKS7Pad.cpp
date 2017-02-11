/**
 * Author: Juan Carlos Ramirez
 *
 * This will implement PCKS#7 padding.
 * This padding will add the number of bytes
 *  needed to the end of a string using the number.
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
using namespace std;

int main(int argc, char** argv){

  if(argc < 3){
    cerr << "USAGE: " << argv[0] << " <block size> <text>" << endl;
    return -1;
  }

  int blockSize = atoi(argv[1]);
  string text(argv[2]);

  if(blockSize < text.size()){
    cerr << "Block size is less than the input text size..." << endl;
    return -1;
  }

  int padSize = blockSize - text.size();
  cout  << text;
  for(int i = text.size(); i < blockSize; i++){
    cout << '\\' << showbase << internal << setfill('0') << setw(2) << hex << padSize;
  }
  cout << endl;
  return 0;
}

#include <iostream>
#include <fstream>
#include <string>


int main() {
  // std::string filename = "test.bin";
  // std::fstream s(filename, s.binary | s.in | s.out | s.ate);
  // if (!s.is_open()) {
  //   std::cout << "failed to open " << filename << '\n';
  // } else {
  //   // write
  //   double d = 3.14;
  //   s.write(reinterpret_cast<char*>(&d), sizeof d); // binary output
  //   s << 123 << "abc";                              // text output

  //   // for fstream, this moves the file position pointer (both put and get)
  //   s.seekp(0);
    
  //   // read
  //   s.read(reinterpret_cast<char*>(&d), sizeof d); // binary input
  //   int n;
  //   std::string str;
  //   if (s  >> str)                             // text input
  //     std::cout << "read back from file: " << d << ' ' << n << ' ' << str << '\n';
  // }

  std::string filename = "test1.txt";
  std::fstream f(filename, f.in |f.out|f.ate);

  if(!f.is_open()){
    std::cout << "Not such a file \n";
  }else{

    f << "hello world \n second \n third\n";

    f.seekp(0);

    //read
    std::string str;
    while(f >> str){
      std::cout << str << '\n';
    }
  }

  f.close();
  return 0;
}
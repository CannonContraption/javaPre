#include<iostream>
#include<fstream>
using namespace std;
int main(int argc, char* argv[]){
	int argcount=0;
	string fname;
	if(argv<2){
		cout<<"Too few arguments."<<endl;
	} else{
		argcount = argc-2;
	}
	fname = argv[1];
	return 0;
}

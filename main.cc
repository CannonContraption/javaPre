#include<iostream>
#include<fstream>
using namespace std;
#include "kv.cc"

/*
 * Return codes:
 * 1: File not found
 */
int main(int argc, char* argv[]){
	int argcount=0;
	string fname = "";
	if(argc<2){
		cout<<"Too few arguments."<<endl;
		return 1;
	} else{
		argcount = argc-2;
	}
	fname = argv[1];
	ifstream javasource;
	javasource.open(fname);
	string line;
	string subline;
	kv kvpairs;
	bool valfound = true;
	string val = ""; //value of key
	string asn = ""; //assignment of key
	while(!javasource.eof()){
		getline(javasource, line);
		if(line[0] == '#'){
			subline = line.substr(1,7);
		}
		if(subline == "DEFINE" || subline == "define"){
			subline = line.substr(8, line.length());
			val = "";
			asn = "";
			for(char c : subline){
				if(c == '='){
					valfound = false;
				}
				else if(valfound){
					val+=c;
				}
				else{
					asn+=c;
				}
			}
			if(line.find("$#")&&line[0]!='#'){
				if(line.find("#$")){
					for(int i = line.find("$#"); i<line.find("#$"); i++){
						asn += line[i];
					}
				}
			}
			kvpairs.insert(val, asn);
		}
	}
	return 0;
}

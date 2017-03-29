#include<iostream>
#include<fstream>
using namespace std;
#include "kv.cc"

void parseline(string line, kv &pairs){
	size_t lsfind = line.find("$#");
	size_t rsfind = line.find("#$");
	string asn = "";
	string newline = "";
	if(lsfind!=string::npos&&line[0]!='#'&&rsfind!=string::npos){
		asn = "";
		for(int i = 0; i<lsfind && i<line.length(); i++){
			newline+=line[i];
		}
		for(int i = lsfind+2; i<rsfind && i<line.length(); i++){
			asn += line[i];
		}
		newline+=pairs.grab(asn);
		for(int i = rsfind+2; i<line.length(); i++){
			newline+=line[i];
		}
		parseline(newline, pairs);
	}
	else cout<<line<<endl;
}

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
	bool valnfound = true;
	string val = ""; //value of key
	string asn = ""; //assignment of key
	int lsfind = 0;
	int rsfind = 0;
	while(!javasource.eof() && !javasource.fail()){
		getline(javasource, line);
		if(line[0] == '#' && line.size()>7){
			subline = line.substr(1,6);
		}
		if(subline == "DEFINE" || subline == "define"){
			subline = line.substr(8, line.length());
			val = "";
			asn = "";
			for(char c : subline){
				if(c == '='){
					valnfound = false;
				}
				else if(valnfound){
					val+=c;
				}
				else{
					asn+=c;
				}
			}
			kvpairs.insert(val,asn);
		}
		else parseline(line, kvpairs);
		subline = "";
		valnfound = true;
	}
	return 0;
}

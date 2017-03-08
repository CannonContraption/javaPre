#include<iostream>
#include<fstream>
#define HASHSIZE 1
#define VOWEL 4
#define CONSONANT 1
using namespace std;

class kv{
public:
	struct pair{
		string key;
		string value;
		pair* next;
		pair* prev;
	};
	pair * listofpairs[HASHSIZE];
	char vow[12] = {'a','e','i','o','u','y','A','E','I','O','U','Y'};
	int hash(string key){
		int sum = 0;
		bool got = false;
		for(char c : key){
			for(char d : vow){
				if(c == d){
					sum+=VOWEL;
					got = true;
				}
			}
			if(!got) sum+=CONSONANT;
			got=false;
		}
		return sum%HASHSIZE;
	}
	void insert(string key, string val){
		int hashindex = hash(key);
		if(listofpairs[hashindex] == NULL){
			listofpairs[hashindex] = new pair;
			listofpairs[hashindex]->key=key;
			listofpairs[hashindex]->value=val;
			listofpairs[hashindex]->next=nullptr;
			listofpairs[hashindex]->prev=nullptr;
		} else {
			pair* current = listofpairs[hashindex];
			while(current->next != nullptr){
				current = current->next;
			}
			current -> next = new pair;
			current -> next -> prev = current;
			current = current -> next;
			current -> key = key;
			current -> value = val;
		}
	}
	string grab(string key){
		int hashindex = hash(key);
		if(listofpairs[hashindex]->key == key){
			return listofpairs[hashindex]->value;
		} else {
			pair* current = listofpairs[hashindex];
			while(current->key != key && current->next != nullptr){
				current = current->next;
			}
			if(current->key == key){
				return current->value;
			} else {
				return "";
			}
		}
	}
};

int main(int argc, char* argv[]){
	int argcount=0;
	string fname = "";
	if(argc<2){
		cout<<"Too few arguments."<<endl;
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
		if(subline == "DEFINE"){
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
			kvpairs.insert(val, asn);
		}
	}
	return 0;
}

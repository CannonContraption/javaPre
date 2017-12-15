#define HASHSIZE 6
#define VOWEL 4
#define CONSONANT 1
class kv
{
public:
	struct pair
	{
		string key;
		string value;
		pair* next;
		pair* prev;
	};
	pair * listofpairs[HASHSIZE];
	kv()
    {
		for(
			int i = 0;
			i<HASHSIZE;
			i++)
		{
			listofpairs[i]=nullptr;
		}
	}
	char vow[12] = {'a','e','i','o','u','y','A','E','I','O','U','Y'};
	int hash(string key)
	{
		int sum = 0;
		bool got = false;
		for(
			char c
			: key)
		{
			for(
				char d 
				: vow)
			{
				if(c == d)
				{
					sum+=VOWEL;
					got = true;
				}
			}
			if(!got)
				sum+=CONSONANT;
			got=false;
		}
		return sum%HASHSIZE;
	}
	
	void insert(
		string key,
		string val)
	{
		int hashindex = hash(key);
		if(listofpairs[hashindex] == nullptr)
		{
			listofpairs[hashindex] = new pair;
			listofpairs[hashindex] -> key=key;
			listofpairs[hashindex] -> value=val;
			listofpairs[hashindex] -> next=nullptr;
			listofpairs[hashindex] -> prev=nullptr;
		}
		else
		{
			pair* current = listofpairs[hashindex];
			while(current->next != nullptr)
			{
				current = current->next;
			}
			current -> next = new pair;
			current -> next -> prev = current;
			current = current -> next;
			current -> key = key;
			current -> value = val;
		}
	}
	string grab(
		string key)
	{
		int hashindex = hash(key);
		if(listofpairs[hashindex] == nullptr)
			return "";
		if(listofpairs[hashindex]->key == key)
		{
			return listofpairs[hashindex]->value;
		}
		else
		{
			pair* current = listofpairs[hashindex];
			while(
				current->key != key
					&& current->next != nullptr)
			{
				current = current->next;
			}
			if(current->key == key)
			{
				return current->value;
			}
			else
			{
				return "";
			}
		}
	}
};

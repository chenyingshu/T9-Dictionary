/*
	Retrieved from: https://github.com/mt-rozi/Cpp_dictionaryT9
	Autor: Mateusz Rozmus mt.rozmus@wp.pl
	T9 with Trie Tree - Test Code
	Edited by Yingshu Chen, Oct 2017
*/

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>
#include <algorithm>

#define LETTER_SIZE 26

using namespace std;

ifstream file;

typedef string elementType;

//Tree node
struct node{
	bool endOfWord; //if it is the end of a word
	int prefix_count = 0;
	char number; //typing number of last letter in this node
	struct node* child[LETTER_SIZE];
};

typedef node *position;

class Tree{
	protected:
		position head;

	public:

	Tree(){
		head=new node();
		head->prefix_count = 0;
		head->endOfWord = false;
	}

	~Tree(){
		cout << "Releasing the Tree..." << endl;
		DeleteNode(head);
		cout << "Tree is released." << endl;
	}

	//Insert the given words in the Trie
	void Insert(elementType word)
	{
		position p=head;
		p->prefix_count++;

		for(int i=0; i<word.length();i++)
		{
			int letter=(int)word[i]-(int)'A';
			if(p->child[letter]==NULL)
			{
				p->child[letter]=new node();
				p->child[letter]->number=NumberLetter(word[i]);
			}
			p=p->child[letter];
		}
		p->endOfWord=true;
	}

	void DeleteWord(elementType word)
	{
		node *n=head;
		int size;

		for(int i=0; i<word.length(); i++)
		{
			size=(int)word[i]-(int)'A';
			if ((size > 25) || (size < 0)) continue;
			if(n->child[size]==NULL)
			{
				cout << "Deleted." << endl;
				return;
			}
			n=n->child[size];
		}
		if(n->endOfWord) n->endOfWord=false;
	}

	//Search for the given word in the Trie and 
	//Return true or false as the case may be
	bool SearchWord(elementType word)
	{
		node *n=head;
		int size;

		for(int i=0;i<word.length();i++)
		{
			size=(int)word[i]-(int)'A';
			if(n->child[size]==NULL) return false;
			n=n->child[size];
		}
		if(n->endOfWord) return true;
		return false;
	}
	
	//find the count of words in the Trie 
	// which has the given word as prefix
	void SearchNumberWord(elementType word)
	{
		node *n=head;

		SearchNumberWordIf(word,"",n,0);
	}

	private:

	void DeleteNode(position p)
	{
		for(int i=0;i<LETTER_SIZE;i++)
			if(p->child[i]!=NULL) DeleteNode(p->child[i]);
		delete p;
	}

	void SearchNumberWordIf(elementType word, elementType result, position n, int i)
	{
		if(word[i]=='2')
			for( int k=0; k<3; k++)
				if(n->child[k]!=NULL) SearchNumberWordContinue(word,result,n->child[k],i,k);
		if(word[i]=='3')
			for( int k=3; k<6; k++)
				if(n->child[k]!=NULL) SearchNumberWordContinue(word,result,n->child[k],i,k);
		if(word[i]=='4')
			for( int k=6; k<9; k++)
				if(n->child[k]!=NULL) SearchNumberWordContinue(word,result,n->child[k],i,k);
		if(word[i]=='5')
			for( int k=9; k<12; k++)
				if(n->child[k]!=NULL) SearchNumberWordContinue(word,result,n->child[k],i,k);
		if(word[i]=='6')
			for( int k=12; k<15; k++)
				if(n->child[k]!=NULL) SearchNumberWordContinue(word,result,n->child[k],i,k);
		if(word[i]=='7')
			for( int k=15; k<19; k++)
				if(n->child[k]!=NULL) SearchNumberWordContinue(word,result,n->child[k],i,k);
		if(word[i]=='8')
			for( int k=19; k<22; k++)
				if(n->child[k]!=NULL) SearchNumberWordContinue(word,result,n->child[k],i,k);
		if(word[i]=='9')
			for( int k=22; k<26; k++)
				if(n->child[k]!=NULL) SearchNumberWordContinue(word,result,n->child[k],i,k);		
	}

	void SearchNumberWordContinue(elementType word, elementType result, position n, int i, int j)
	{
		int size = word.length()-1;

		if(n->number==word[i])
		{
			result+=(char)(j+(int)'A');
			if(n->endOfWord && i==size) cout << result << ", ";
			if(i<=size)
				SearchNumberWordIf(word,result,n,i+1);
		}
	}

	//letter and letter mapping
	char NumberLetter(char letter)
	{
		if(letter=='A'||letter=='B'||letter=='C') return '2';
		else if(letter=='D'||letter=='E'||letter=='F') return '3';
		else if(letter=='G'||letter=='H'||letter=='I') return '4';
		else if(letter=='J'||letter=='K'||letter=='L') return '5';
		else if(letter=='M'||letter=='N'||letter=='O') return '6';
		else if(letter=='P'||letter=='Q'||letter=='R'||letter=='S') return '7';
		else if(letter=='T'||letter=='U'||letter=='V') return '8';
		else if(letter=='W'||letter=='X'||letter=='Y'||letter=='Z') return '9';
	}
};

int main()
{
	Tree tree;
	string result;
	bool z;
	int i=0;

	cout << "Loading dictionary file 'dictionary.txt'..." << endl;
	file.open("dictionary.txt");
	if (file.is_open()) {
		while (!(file.eof()))
		{
			//file>>word;
			string word;
			getline(file, word);
			transform(word.begin(), word.end(), word.begin(), ::toupper);
			//cout << word << endl;
			tree.Insert(word);
			i++;
		}
	}
	else {
		cout << "Cannot open the dictionary file." << endl;
	}
	cout << "The Trie tree has been inserted " << i << " words.\n" << endl;

	while(1)
	{
		string word="";
		cout << "\n\n" << endl;
		cout << "+===========================+" << endl;
		cout << "|    7    |   8   |    9    |" << endl;
		cout << "| p q r s | t u v | w x y z |" << endl;		
		cout << "+===========================+" << endl;
		cout << "|    4    |   5   |    6    |" << endl;
		cout << "|  g h i  | j k l |  m n o  |" << endl;
		cout << "+===========================+" << endl;
		cout << "|    1    |   2   |    3    |" << endl;
		cout << "|  exit   | a b c |  d e f  |" << endl;
		cout << "+===========================+" << endl;
		cout << "Please input numbers in a string: ";
		cin >> word;
		cout << endl;
		if(word[0]=='1') break;
		tree.SearchNumberWord(word);
	}

	return 0;
}

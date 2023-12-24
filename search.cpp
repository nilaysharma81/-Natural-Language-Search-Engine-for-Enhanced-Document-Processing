// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine(){
    // Implement your function here  
}

SearchEngine::~SearchEngine(){
    list.clear(); 
}


void tolower(string &s) {
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
}


void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here  
    sen* newsen = new sen;
    newsen->book_code = book_code;
    newsen->page = page;
    newsen->paragraph = paragraph;
    newsen->sentence_no = sentence_no;
    tolower(sentence);
    newsen->sentence = sentence;
    list.push_back(newsen);
    return;
}

void SearchEngine::findlps(string pattern, int* lps){
	lps[0] = 0;
	int i=1;
	int index =0;
	tolower(pattern);
	while (i < pattern.length()){
		if (pattern[i] == pattern[index]){
			index++;
			lps[i] = index;
			i++;
		}
		else{
			if (index>0){
				index = lps[index-1];
			}
			else{
				lps[i] = 0;
				i++;
			}
		}
	}
}


Node* SearchEngine::findpat(string pattern, sen* object, int& count){
	Node* root = new Node();
	Node* pointer = root;
	int lps[pattern.length()];
	findlps (pattern, lps);
	string sentence = object->sentence;
	
	int index = 0;
	int lpsindex = 0;
	while (index< sentence.length() && lpsindex< pattern.length()){
		if (sentence.length()-index < pattern.length()-lpsindex){
			break;
		}
		else if (sentence [index] == pattern[lpsindex]){
			index++;
			lpsindex++;
			if (lpsindex== pattern.length()){
				int offset = index- lpsindex;
				count++ ;
				Node* next = new Node( object->book_code, object->page, object->paragraph, object->sentence_no, offset);
				pointer->right = next;
				next->left = pointer;
				pointer = pointer->right;
				lpsindex = lps [lpsindex - 1];
			}
		}
		else{
			if (lpsindex > 0){
				lpsindex = lps [lpsindex-1];
			}
			else{
				index++;
			}
		}
		
	}
	pointer->right = nullptr;
	if (root->right != nullptr){
		pointer = root->right;
		delete root;
		return pointer;
	}
	else {
		return nullptr;
	}
}


Node* SearchEngine::search(string pattern, int& n_matches){
   	Node* root = new Node();
   	Node* temp = root;
   	int count = 0;
	for (int i=0; i< list.size(); i++){
    		temp->right = findpat(pattern, list[i], count);
    		
    		while (temp->right != nullptr){
    			temp->right->left = temp;
    			temp = temp->right;
    		}
	}
	n_matches = count;
    	temp = root->right;
    	delete root;
    	return temp;
}

/*int main(){
	SearchEngine s;
	string a = "hey There djiwd there fojro.";
	string b = "there is ahfie.";
	s.insert_sentence(1,1,1,1,a);
	s.insert_sentence(2,2,2,2,b);
	int cnt = 0;
	Node* h = s.search("there", cnt);
	cout << "count" << cnt << endl;
	while (h != nullptr){
		cout << h->book_code << "===bc" << h->offset << "=== offset" << endl;
		h = h->right;
	}
}*/

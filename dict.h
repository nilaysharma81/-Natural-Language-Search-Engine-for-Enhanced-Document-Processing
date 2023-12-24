// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Dict {
private:
    // You can add attributes/helper functions here
    struct phrase{
        string text;
        long long unsigned int count;
    };

    long long unsigned int cap;
    long long unsigned int sz;
    vector<vector<phrase>>* haash;
    long long unsigned int hash(string &s);
    long long unsigned int searchf(string &s);
    long long unsigned int insertf(string &s);
    void split(string &s, vector<string>& words);
    void resizeHaash();

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string phrase);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};
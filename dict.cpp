// Do NOT add any other includes
#include "dict.h"

Dict::Dict()
{
    sz = 0;
    cap = 10240000;
    // haash.resize(cap);
    haash = new vector<vector<phrase>>(cap,vector<phrase>());
    // for (int i = 0; i < cap; i++)
    // {
    //     haash[i].clear();
    // }
    // Implement your function here
}

void Dict::resizeHaash()
{

    long long unsigned int newCap = cap * 2;
    cap = newCap;
    vector<vector<phrase>>*newHaash = new vector<vector<phrase>>(cap,vector<phrase>());

    for (int i = 0; i < (*haash).size(); i++)
    {
        for (phrase &p : (*haash)[i])
        {
            phrase  temp;
            temp.text = p.text;
            temp.count = p.count ;
            long long unsigned int newHash = hash(p.text);
            (*newHaash)[newHash].push_back(temp);
        }
    }
    delete haash;
    haash = newHaash;
    
}

void toLower(string &s) {
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
}

long long unsigned int Dict::insertf(string &s)
{
    vector<string> words;
    split(s, words);

    for (string &word : words)
    {
        toLower(word);
        long long unsigned int wordHash = hash(word);
        long long unsigned int index = searchf(word);
        if (index != -1)
            
        {   
            (*haash)[wordHash][index].count++;
            // cout<<"incrementing frequency of word "<<word<<" new freq is "<<(*haash)[wordHash][index].count<<endl;
            // cout<<word<<" "<<get_word_count(word)<<endl;
        }
        else
        {
            phrase p ;
            p.text = word;
            p.count = 1;
            (*haash)[wordHash].push_back(p);
            sz++ ;
            // if (sz + 1 >= cap)
            // {
            //     resizeHaash();
            // }
            // cout<<"inserting word "<<word<<"and at that moment s is "<<s<<endl;
            // cout<<word<<" "<<get_word_count(word)<<endl;
        }
    }

    return 0;
}

long long unsigned int Dict::searchf(string &s)
{
    toLower(s);
    // cout<<"searching for word "<<s<<" "<<endl;
    long long unsigned int wordHash = hash(s);

    
        for (long long unsigned int i = 0; i < (*haash)[wordHash].size(); ++i)
        {
            if ((*haash)[wordHash][i].text == s)
            {
                return i;
            }
        }
    
    return -1;
}

long long unsigned int Dict::hash(string &s) {
    const long long p = 31;
    const long long m = 1e9 + 9;
    long long unsigned int hf = 0;
    long long unsigned int p_pow = 1;
    // if(s == "adver")
    // {
    //     // cout<<"Calculating hash for adver"<<endl;
    // }
    for (char c : s) {
        hf = (hf + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
//     long long unsigned int hf = 0;
//   int k = 1;
//   for (char c : s)
//   {
//     hf = hf + k * (c + 1);
//     k++;
//   }
//   return hf % 10103;
    
    return hf % cap;
}

void Dict::split(string &s, vector<string> &words)
{
    string word = "";

    for (auto &x : s)
    {
        if (x == ' ' || x == '.' || x == ',' || x == '-' || x == ':' || x == '!' || x == '(' || x == ')' || x == '?' || x == '—' || x == '[' || x == ']' || x == '"' || x == '\''  || x == '˙' || x == ';' || x == '@')
        {
            if (!word.empty())
            {
                words.push_back(word);
                word = "";
            }
        }
        else
        {
            word.push_back(x);
        }
    }

    if (!word.empty())
    {
        words.push_back(word);
    }
}

Dict::~Dict()
{

    // Implement your function here

}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // phrase p;
    // p.text = sentence;
    // p.count = 1;
    insertf(sentence);
}

int Dict::get_word_count(string word)
{
    long long unsigned int wordHash = hash(word);
    
        for (phrase &p : (*haash)[wordHash])
        {
            if (p.text == word)
            {
                return p.count;
            }
        }
    
    return 0;
}

void Dict::dump_dictionary(string filename)
{
    ofstream a;
    a.open(filename, ios::out);
    for (int i = cap-1; i >=0; i--)
    {
        for (int j = 0; j < (*haash)[i].size(); j++)
        {
            a << (*haash)[i][j].text << ","
              << " " << (*haash)[i][j].count << endl;
        }
    }
    a.close();
    // Implement your function here
    return;
}

// int main()
// {
//     Dict d ;
//     string s1 = "HI I am nilay adversely" ;
//     string s2 = "nvfi s! as hit" ;
//     d.insert_sentence(0,0,0,0,s1);
//     d.insert_sentence(0,0,0,0,s2);
//     cout<<"Hi"<<endl;
//     cout<<d.get_word_count("adver")<<endl;
//     cout<<d.get_word_count("am")<<endl;
//     d.dump_dictionary("check.txt");
// }
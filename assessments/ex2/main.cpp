#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <math.h>

using namespace std;

int checkInterpretation(map <char, int> layout, vector <string> words, int wordNum);
int convertWordToNum(map <char, int> layout, string word);

int main() {
    ifstream fd ("duota.txt");
    ofstream fr ("rez.txt");

    vector <string> words;
    int wordNum = 0;
    set <char> characters;
    int maxWordLength = 0;

    //reading words, counting characters
    while(!fd.eof()) {
        string newWord;
        fd >> newWord;

        words.push_back(newWord);
        ++wordNum;

        int currWordLength = newWord.length();
        for(int i = 0; i < currWordLength; ++ i) {
            characters.insert(toupper(newWord[i]));
        }

        maxWordLength = (newWord.length() > maxWordLength) ? newWord.length() : maxWordLength;
    }

    if(characters.size() > 10 || words[wordNum-1].length() < maxWordLength) {
        fr << "Current cryptoarithmetic puzzle is impossible to solve.";
        return 0;
    }

    map <char, int> test;
    test['A'] = 1;
    test['B'] = 2;
    test['C'] = 3;

    // int count = 0;
    // for(set <char> :: iterator i = characters.begin(); i != characters.end(); ++i) {
    //     test[*i] = count;
    //     fr << *i << " " << test[*i] << endl;
    //     ++count;
    // }

    if(checkInterpretation(test, words, wordNum))
        fr << "alles gut!" << endl;

    fr << "dirbam toliau" << endl;

    fd.close();
    fr.close();

    return 0;
}

int checkInterpretation(map <char, int> layout, vector <string> words, int wordNum) {
    int sum = 0;
    
    for(int i = 0; i < wordNum-1; ++i) {
        int currWordLength = words[i].length();
        cout << words[i] << endl;
        
        sum += convertWordToNum(layout, words[i]);
    }
    cout << sum << endl;

    if(sum == convertWordToNum(layout, words[wordNum-1]))
        return 1;
        
    return 0;
}

int convertWordToNum(map <char, int> layout, string word) {
    int result = 0;
    int wordLength = word.length(); 

    for(int i = 0; i < wordLength; ++i)
        result += layout[toupper(word[i])] * pow(10, wordLength - i - 1);

    cout << result << endl;

    return result;
}
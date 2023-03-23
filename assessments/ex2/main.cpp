#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <math.h>

using namespace std;

void printQueue(queue <int> data);
void printLayout(map <char, int> layout);

void solve(map <char, int> &layout, bool &solutionIsFounded, queue <int> unusedNum, vector <string> words, queue <char> stack);
int checkInterpretation(map <char, int> layout, vector <string> words);
int convertWordToNum(map <char, int> layout, string word);


int main() {
    ifstream fd ("duota.txt");
    ofstream fr ("rez.txt");

    vector <string> words;
    map <char, int> characterLayout;
    set <char> characters;

    // getting words, initialising layout map
    while(!fd.eof()) {
        string newWord;
        fd >> newWord;

        int wordLength = newWord.length();
        for(int i = 0; i < wordLength; ++i) {
            char currCharacter = toupper(newWord[i]);
            if(i == 0 || characters.count(tolower(currCharacter))) {
                characters.erase(currCharacter);
                currCharacter = tolower(currCharacter);
            }
            
            characters.insert(currCharacter);
            newWord[i] = currCharacter;  
            characterLayout[currCharacter] = -1;
        }
        words.push_back(newWord);
    }
    int wordNum = words.size();

    // filling stack with characters
    queue <char> characterStack;
    for(set <char> :: iterator i = characters.begin(); i != characters.end(); ++i) {
        characterStack.push(*i);
    }

    // creating and filling unused num queue
    queue <int> unusedNum;
    for(int i = 0; i < 10; ++i)
        unusedNum.push(i);

    // solving puzzle
    bool solutionIsFounded = 0;
    solve(characterLayout, solutionIsFounded, unusedNum, words, characterStack);

    if(!solutionIsFounded) {
        fr << "Unable to find solution." << endl;
        return 0;
    }

    fr << "Solution: " << endl;
    for(map <char, int> :: iterator i = characterLayout.begin(); i != characterLayout.end(); ++i) {
        char currCharacter = toupper(i->first);
        fr << currCharacter << " = " << characterLayout[currCharacter] << " ";
    }
    fr << endl;

    for(int i = 0; i < wordNum; ++i) {
        fr << words[i] << " = " << convertWordToNum(characterLayout, words[i]) << endl; 
    }

    return 0;
}

void printQueue(queue <int> data) {
    int queueLength = data.size();

    cout << "Queue: ";
    for(int i = 0; i < queueLength; ++i) {
        cout << data.front();
        data.pop();
    }
    cout << endl;
}

void printLayout(map <char, int> layout) {
    cout << "Layout: ";
    for(map <char, int> :: iterator i = layout.begin(); i != layout.end(); ++i) {
        cout << i->first << ": " << i->second << ", ";
    }
    cout << endl;
}

void solve(map <char, int> &layout, bool &solutionIsFounded, queue <int> unusedNum, vector <string> words, queue <char> stack) {
    printLayout(layout);
    int unusedNumCount = unusedNum.size();
    char currCharacter = stack.front();
    stack.pop();

    for(int i = 0; i < unusedNumCount; ++i) {
        if(!solutionIsFounded) {
            int assignedNum = unusedNum.front();
            unusedNum.pop();
            
            if(assignedNum == 0 && islower(currCharacter)) {
                unusedNum.push(assignedNum);
                continue;
            }
            layout[currCharacter] = assignedNum;

            if(!stack.empty()) {
                solve(layout, solutionIsFounded, unusedNum, words, stack);
                unusedNum.push(assignedNum);
            }
            else if (checkInterpretation(layout, words)) {
                solutionIsFounded = 1;
                break;
            }
        }        
    }
}

int checkInterpretation(map <char, int> layout, vector <string> words) {
    int wordCount = words.size();    
    int sum = 0;
    
    for(int i = 0; i < wordCount-1; ++i) {
        int currWordLength = words[i].length();
        sum += convertWordToNum(layout, words[i]);
    }

    if(sum == convertWordToNum(layout, words[wordCount-1]))
        return 1;
        
    return 0;
}

int convertWordToNum(map <char, int> layout, string word) {
    int result = 0;
    int wordLength = word.length(); 

    for(int i = 0; i < wordLength; ++i)
        result += layout[word[i]] * pow(10, wordLength - i - 1);

    return result;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <math.h>

using namespace std;

void printErr(string msg);
void solve(map <char, int> &layout, bool &solutionIsFounded, queue <int> unusedNum, vector <string> words, queue <char> stack);
int checkInterpretation(map <char, int> layout, vector <string> words);
int convertWordToNum(map <char, int> layout, string word);


int main(int argc, char **argv) {
    if(argc != 3) {
        printErr("nepakanka argumentų komandinėje eilutėje");
        return 0;
    }

    string dataFileName = argv[1];
    string resultFileName = argv[2];

    ifstream fd (dataFileName);
    cout << "Atidaromas įvesties failas: " << dataFileName << '\n';
    if(!fd.is_open()) {
        string msg = "nepavyksta atidaryti " + dataFileName;
        printErr(msg);
        return 0;
    }
    
    ofstream fr (resultFileName);
    cout << "Atidaromas išvesties failas: " << resultFileName << '\n';
    if(!fr.is_open()) {
        string msg = "nepavyksta atidaryti " + resultFileName;
        printErr(msg);
        return 0;
    }

    // reading data, adding characters to the set
    vector <string> words;
    map <char, int> characterLayout;
    set <char> characters;

    while(!fd.eof()) {
        string newWord;
        fd >> newWord;

        if(newWord.empty())
            continue;

        int wordLength = newWord.length();
        for(int i = 0; i < wordLength; ++i) {
            char currCharacter = toupper(newWord[i]);
            if(i == 0 || characters.count(tolower(currCharacter))) {
                characters.erase(currCharacter);
                currCharacter = tolower(currCharacter);
            }
            
            characters.insert(currCharacter);
            newWord[i] = currCharacter;
        }
        words.push_back(newWord);
    }
    int wordNum = words.size();

    // creating queue filled with unsigned characters
    queue <char> unsignedCharacters;
    for(set <char> :: iterator i = characters.begin(); i != characters.end(); ++i)
        unsignedCharacters.push(*i);

    // creating queue filled with unsigned characters
    queue <int> unusedNum;
    for(int i = 0; i < 10; ++i)
        unusedNum.push(i);

    // searching for solution if it possible to find one
    bool solutionIsFounded = 0;
    solve(characterLayout, solutionIsFounded, unusedNum, words, unsignedCharacters);

    // printing the results
    if(!solutionIsFounded) {
        fr << "Pateikta užduotis sprendimo neturi." << endl;
        return 0;
    }

    fr << "Užduoties sprendimas: " << endl;
    for(map <char, int> :: iterator i = characterLayout.begin(); i != characterLayout.end(); ++i) {
        char currCharacter = i->first;
        fr << (char) toupper(currCharacter) << " = " << characterLayout[currCharacter] << " ";
    }
    fr << "\n\n";

    for(int i = 0; i < wordNum; ++i) {
        int currWordLength = words[i].length();
        int currWordValue = convertWordToNum(characterLayout, words[i]);
        
        for(int j = 0; j < currWordLength; ++j)
            words[i][j] = toupper(words[i][j]);

        fr << words[i] << " = " << currWordValue << '\n';
    }

    return 0;
}

void printErr(string msg) {
    cout << "Klaida: " << msg << '\n';
}

void solve(map <char, int> &layout, bool &solutionIsFounded, queue <int> unusedNum, vector <string> words, queue <char> stack) {
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

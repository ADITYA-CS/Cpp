/**
 *  H A N G M A N
 */

#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <set>
#include <cctype>
#include <time.h>
#include <stdlib.h>

//function declaration
char CheckInput(std::string, std::set<char> &);
void StartGame();
std::string ChooseWord();

int main() {

    while(true){
        std::cout << "Type \"play\" to play the game, \"exit\" to quit: ";
        std::string option;
        getline(std::cin, option);

        std::cout << '\n';
        if(option == "exit"){
            break;
        }
        else if(option == "play"){
            StartGame();
        }
        else{
            std::cout << "Unkown choice" << "\n\n";
        }
    }

}


// function definition
char CheckInput(std::string input, std::set<char> &s){

    if(input.size() != 1){
        throw "You should print a single letter";
    }
    else if(!islower(input[0])){
        throw "It is not an ASCII lowercase letter";
    }
    else if(s.find(input[0]) != s.end()){
        throw "You already typed this letter";
    }
    return input[0];
}

std::string ChooseWord(){

    // List of words, one word will chosen in every game
    std::vector<std::string> word_list = {"python", "java", "kotlin",
    "javascript"};
    int word_list_size = word_list.size();

    // choosing an random word
    srand (time(0));
    return word_list[rand() % word_list_size];
}

void StartGame(){

    // for checking whether user reenter the same letter or not
    std::set<char> user_input_letter;

    //choosing word for the game
    const auto word = ChooseWord();
    const int word_len = word.size();

    // Hint for user;
    std::string hint;
    hint.assign(word_len, '-');

    // A player has only 8 chance
    int chance = 8;
    bool success = false;

    while(chance && !success){
        std::cout << hint << "\n";

        // choice, made by player, reading in string form
        std::string choice;
        getline(std::cin, choice);
        char letter;

        try{
            letter = CheckInput(choice, user_input_letter);
        }
        catch (const char* exception){
            std::cout << exception << "\n\n";
            continue;
        }
        // is letter found in 'word', then set in_word = true
        bool in_word = false;
        for (int i = 0; i < word_len; i++) {
            if(word[i] == letter){
                in_word = true;
                hint[i] = letter;
            }
        }

        // letter not found means fault, so chance -= 1
        if(!in_word){
            std::cout << "No such letter in the word" << "\n\n";
            chance--;
            continue;
        }
        else{
            user_input_letter.insert(letter);
        }

        // success = true will terminate the loop
        if(hint == word){
            success = true;
        }
        std::cout << '\n';
    }

    if(success){
        std::cout << hint << '\n';
        std::cout << "You guessed the word!" << '\n';
        std::cout << "You survived!" << "\n\n";
    }
    else{
        std::cout << "You are hanged!" << "\n\n";
    }
}

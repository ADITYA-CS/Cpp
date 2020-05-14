/*
 * @Author: Aditya Kumar Singh <the__martian>
 * @Email:  cr7.aditya.cs@gmail.com
 * @Last modified by:   the__martian
 */

//
//      Tic-Tac-Toe
//

#include <bits/stdc++.h>
using namespace std;

char matrix[3][3];

// Prototype
void PrintCoordinate();
void CreateEmptyMatrix();
vector<string> TokenizeString(string &str);
pair<int,int> ReadInput();
void PrintMatrix();
bool Win(char player);
bool Draw();

int main()
{
    PrintCoordinate();
    CreateEmptyMatrix();
    PrintMatrix();
    int toggle = 1;
    while (true){
        auto coordinate = ReadInput();
        if(coordinate.first == -1)
            continue;
        int x = coordinate.first, y = coordinate.second;
        if(matrix[x][y] != ' '){
            cout << "Cell is not empty\n";
            continue;
        }
        else {
            toggle ? matrix[x][y] = 'X' : matrix[x][y] = 'O';
            toggle = 1 - toggle;
            PrintMatrix();
            if (Win('X')) {
                cout << "X wins\n";
                break;
            } else if (Win('O')) {
                cout << "O wins\n";
                break;
            } else if (Draw()) {
                cout << "Draw\n";
                break;
            }
        }
    }
}


void CreateEmptyMatrix()
{
    for(auto & i : matrix) {
        for(char & j : i) {
            j = ' ';
        }
    }
}

void PrintCoordinate()
{
    cout << "Board coordinates\n";
    cout<<" -----------------\n";
    cout << "|(1,1) (1,2) (1,3)|\n";
    cout << "|(2,1) (2,2) (2,3)|\n";
    cout << "|(3,1) (3,2) (3,3)|\n";
    cout<<" -----------------\n";
}

vector<string> TokenizeString(string &str)
{
    vector<string> res;

    // now tokenize on the basis of whitespace
    for(int i = 0, len = str.size(); i < len; i++){
        string temp;
        while(i < len && str[i] != ' ')
            temp += str[i++];
        if(temp != " " && !temp.empty())
            res.push_back(temp);
    }
    return res;
}


pair<int,int> ReadInput()
{
    cout << "Enter the coordinates: ";
    string input;
    getline(cin, input);
    cout << input << "\n";
    auto input_token = TokenizeString(input);
    if(input_token.size() != 2){
        cout << "Board is 2-D plane, enter XY-coordinate\n";
        return make_pair(-1,-1);
    }
    vector<int> coordinate;
    for(auto &s : input_token) {
        int x = 0;
        for (auto c : s) {
            if (c < '0' || c > '9') {
                cout << "You should enter numbers!\n";
                return make_pair(-1,-1);
            } else{
                x = x * 10 + c - '0';
            }
        }
        if(x < 1 || x > 3){
            cout << "Coordinates should be from 1 to 3!\n";
            return make_pair(-1,-1);
        }
        coordinate.push_back(x-1);
    }
    return make_pair(coordinate[0], coordinate[1]);
}


void PrintMatrix()
{
    cout<<" ------\n";
    for(auto & i : matrix) {
        cout << "|";
        for(char j : i) {
            cout << " " << j;
        }
        cout << "|\n";
    }
    cout<<" ------\n";
}


bool Win(char player)
{
    // checking row
    for(auto & i : matrix){
        if(i[0] == player
           && i[1] == player
           && i[2] == player)
            return true;
    }

    // checking column
    for(int i = 0; i < 3; i++){
        if(matrix[0][i] == player
           && matrix[1][i] == player
           && matrix[2][i] == player){
            return true;
        }
    }

    // checking diagonal
    if(matrix[0][0] == player
       && matrix[1][1] == player
       && matrix[2][2] == player)
        return true;

    return (matrix[0][2] == player
            && matrix[1][1] == player
            && matrix[2][0] == player);
}

bool Draw()
{
    if(Win('X') || Win('O'))
        return false;

    for(auto &x : matrix)
        for(auto y : x)
            if(y == ' ')
                return false;
    return true;
}

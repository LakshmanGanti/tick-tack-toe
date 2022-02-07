#include <iostream>
#include <cstdlib>
#include<ctime>
#include <windows.h>

using namespace std;

char board [3] [3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

char current_marker;
int current_player;

void drawBoard(){
    cout<<"\n\n\n";
    cout<<"\t      |   |  \n";
    cout<<"\t    "<<board [0][0]<<" | "<< board [0][1] <<" | "<< board [0][2]<< endl;
    cout<<"\t______|___|______\n";
    cout<<"\t      |   |  \n";
    cout<<"\t    "<<board [1][0]<<" | "<< board [1][1] <<" | "<< board [1][2]<< endl;
    cout<<"\t______|___|______\n";
    cout<<"\t      |   |  \n";
    cout<<"\t    "<<board [2][0]<<" | "<< board [2][1] <<" | "<< board [2][2]<< endl;
    cout<<"\t      |   |  \n";
    cout<<"\n\n\n";
    
}

bool placeMarker (int slot){ //get the position of marker by the value present on the display board (1-9)
    int row, col;
    if(slot % 3 == 0){
       row = slot/3 - 1;
       col = 2;  
    }         
    else {
       row = slot/3;
       col = (slot % 3) - 1;
    }     
    if(board[row][col] != 'X' && board[row][col] != 'O'){
        board[row][col] = current_marker; 
        return true; //TO make sure that the second player doesn't choose the existing slot
    }
    else return false;
}

char winner(){
    for(int i=0; i<3; i++)
    {
        //checking rows
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2]) return current_player;
        
        //checking columns
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i]) return current_player;
    
    }
    //checking both the diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) return current_player;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) return current_player;

    return 0;
}

void swap_player_and_marker(){ //Alternate turns for the players

    if(current_marker == 'X') current_marker = 'O';
    else current_marker = 'X';

    if(current_player == 1) current_player = 2;
    else current_player = 1;
}
void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                  //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
 }
 
void ClearConsoleToColors(int ForgC, int BackC)
{
 WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
               //Get the handle to the current output buffer...
 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
                     //This is used to reset the carat/cursor to the top left.
 COORD coord = {0, 0};
                  //A return value... indicating how many chars were written
                    //   not used but we need to capture this since it will be
                      //   written anyway (passing NULL causes an access violation).
  DWORD count;

                               //This is a structure containing all of the console info
                      // it is used here to find the size of the console.
 CONSOLE_SCREEN_BUFFER_INFO csbi;
                 //Here we will set the current color
 SetConsoleTextAttribute(hStdOut, wColor);
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                          //This fills the buffer with a given character (in this case 32=space).
      FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

      FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
                          //This will set our cursor position for the next print statement.
      SetConsoleCursorPosition(hStdOut, coord);
 }
 return;
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void game(){
    int ch;
    char marker_p1; 

    string q = "\n\n\t\t======== WELCOME TO TIC TAC TOE GAME ========\n\n";
     for(int i=0;i<q.size();i++)
    {
        cout<<q[i];
        delay(120);

    }
    cout<< "\n\tPlayer 1, choose your marker: \n"; 
    cout<< "\tPress\n\t1. For'X'\n\t2. For'O'\n\tChoice: ";    
    cin>>ch;
    if(ch == 1) marker_p1 = 'X'; 
    if(ch == 2) marker_p1 = 'O'; 

    current_player = 1;
    current_marker = marker_p1;
    if(current_marker == 'X') cout<< "\n\n\t\tPlayer1 [X]\n\t\tPlayer2 [O]";
    if(current_marker == 'O') cout<< "\n\n\t\tPlayer1 [O]\n\t\tPlayer2 [X]";
    drawBoard();

    int player_won ;

    for(int i=0; i<9; i++)
    {
        cout<<"\tIt's player "<<current_player<< "'s turn ["<< current_marker<<"]\n\tEnter your slot: ";
         Beep(500, 600);
        int slot;
        cin>>slot;

        if(slot < 1 || slot > 9){ //Accept only the valid marker positions
            cout<< "\n\tINVALID slot! try another slot!\n\n"; 
            i--; 
            continue;   
        }        

        if(!placeMarker(slot)) { //If the selected slot is already marked
            cout<< "\n\tThat slot is occupied! try another slot!\n\n"; 
            i--; 
            continue;
        }
        drawBoard();

        player_won = winner(); //Gets the status from winner funtion 
        
        //Stop the game if anyone won
        if (player_won == 1){ cout<<"\n\tPlayer 1 WON the GAME, CONGRATULATIONS :-)\n\n\n"; Beep(850, 800);  break; }
        if (player_won == 2){ cout<<"\n\tPlayer 2 WON the GAME, CONGRATULATIONS :-)\n\n\n"; Beep(850, 800); break; }
        swap_player_and_marker();
       

    }
    if (player_won == 0){ cout<<"\n\tThat is a tie game!\n\n\n"; Beep(750, 800);  }    

}


int main(){

    ClearConsoleToColors(0,0);
    SetColor(3);
    game();
   
    return 0;
}
#include <iostream> 
#include <vector>
using namespace std; 

void restartBoard(vector<vector<string>> &board){
	for (int i= 0; i < 3; i ++){
		for (int j=0; j< 3; j ++) {
			board[i][j] = " "; 
		}
	}
}		

void displayBoard(vector<vector<string>> board){
	for (int i=0; i < 3 ; i ++) {
      		for (int j=0; j <3 ; j ++ ) {
			cout << board[i][j];
			if ( j < 2) cout << "|"  ; 
		}	
		cout << "\n"; 
		if (i < 2 ) cout << "-----" << endl ; 
	} 

}

void chooseTurn(string& turn){
	if (turn == "X"){
		turn = "O"; 
	}else {
		turn = "X";	
	
	}	
}

void placeTile(string turn, vector<vector<string>> &board){
	do { 
		cout << "It is " << turn << "'s turn" << endl; 
		cout << "Please select the row you would like to place : " << endl; 
		cin >> row; 
		cout << "Please select the column you would like to place : " << endl; 
		cin >> col; 
	}while(		


}

void ticTacToe(){
	vector<vector<string>> board(3,vector<string>(3)); 
	restartBoard(board); 
	bool gamerun = true; 
	string turn = "X"; 
	while (gamerun){
		displayBoard(board); 	
		chooseTurn(turn); 
		placeTile(turn); 			
	};

}


int main() 

{
	int userInput; 
	do{
		cout << "What would you like to do?" << endl; 
		cout << "1. Play" << endl; 
		cout << "2. Exit" << endl;
	       	cin >> userInput ; 	
		switch (userInput){

			case 1: 
				ticTacToe();
				break; 
			case 2: 
				cout << "Goodbye" << endl; 
				return 0; 
			default: 
				cout << "Invalid input" ; 

		}
		
	
	
	
		}while(userInput !=2) ;	



	}

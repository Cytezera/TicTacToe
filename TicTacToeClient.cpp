#include <iostream> 
#include <vector>
using namespace std; 

void connectServer() {
	int clientSocket;
	struct sockaddr_in serverAddr; 
	char buffer[1024] = {0};

	clientSocket = socket (AF_INET, SOCK_STREAM) , 0 ) ; 
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_port = htons(8080); 
       	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	recv(clientSocket, buffer, 1024, 0 ) ;
	cout << buffer; 
	int row , col; 
	cout << "Please enter the row " << endl; 	
	cin >> row; 
	cout << "Please enter the column " << endl; 
	cin >> col ;	

	
}
void displayBoard(vector<vector<string>> board){
	cout << "  0 1 2" << endl; 
	for (int i=0; i < 3 ; i ++) {
		cout << i << " " ; 
      		for (int j=0; j <3 ; j ++ ) {
			cout << board[i][j];
			if ( j < 2) cout << "|"  ; 
		}	
		cout << "\n"; 
		if (i < 2 ) cout << "  -----" << endl ; 
	} 
	cout << "\n"; 
}

void chooseTurn(string& turn){
	if (turn == "X"){
		turn = "O"; 
	}else {
		turn = "X";	
	
	}	
}

void placeTile(string turn, vector<vector<string>> &board){
	int row, col; 	
	bool check; 
	do { 
		cout << "It is " << turn << "'s turn" << endl; 
		cout << "Please select the row you would like to place : " << endl; 
		cin >> row; 
		cout << "Please select the column you would like to place : " << endl; 
		cin >> col;
	       	if (board[row][col] != " ") {
			cout << "Invalid input, please try again" << endl; 
			check = false; 	
		}else { 
			board[row][col] = turn; 
			check = true ;			
		} 	
	}while(!check);		


}

void checkResult (bool& gamerun, vector<vector<string>> board, string turn) {
	
	if ((board[0][0] == board[1][1] && board[1][1] == turn && board[2][2] == turn ) || ( board[0][2] == board[1][1] && board[1][1] == turn && board[2][0] == turn )) {

		displayBoard(board); 
		cout << turn << " wins " << endl;
	        gamerun = false; 
       		return; 		       
	}	

	for (int i = 0 ; i < 3; i ++ ) {
		if ((board[i][0] == board[i][1] && board[i][1] == turn &&  board[i][2] == turn ) || (board[0][i]==board[1][i] && board[1][i] == turn && board[2][i] == turn )) { 

			displayBoard(board); 
			cout << turn <<  " wins " << endl; 
			gamerun = false;
			return ;	
			
		}	
		
		
	}
	for (int i = 0 ; i < 3 ; i ++) { 
		for (int j = 0; j < 3 ; j++) {
			if (board[i][j] == " " ) {
				return; 
			}
		}
	} 
	displayBoard(board);	
	cout << "It is a draw " << endl; 
	gamerun = false; 
	return ;
} 
void ticTacToe(){
	vector<vector<string>> board(3,vector<string>(3)); 
	restartBoard(board); 
	bool gamerun = true; 
	string turn = "O"; 
	while (gamerun){
		chooseTurn(turn); 
		displayBoard(board); 	
		placeTile(turn, board); 			
		checkResult(gamerun,board,turn);	
	};

}


int main() 

{
	connectServer() ;
		return 0 ; 
	}

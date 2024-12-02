#include <iostream> 
#include <vector>
using namespace std; 

void connectClient(){  //all the comments are to explain to my future self in very simplified terms
	int serverSocket, client1, client2;  // initialize the bridge, player 1 and 2  
	struct sockaddr_in serverAddr, clientAddr ;  //creates a struct that holds the address for server and client  
	socklen_t addr_size; //stores the size of the address for future use 

	serverSocket = socket(AF_INET, SOCK_STREAM, 0) ; //creates the bridge , AFINET is telling it to use IPV4 and sockstream tells it to use tcp
	serverAddr.sin_family = AF_INET; // Setting the server IP to sue IPV4 
      	serverAddr.sin_port = htons(8080); // seeting the port to be 8080  	
	serverAddr.sin_addr.s_addr = INADDR_ANY; // setting the ip address but in 32 bit form
	bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr); // setting up to accept clients 
	listen(serverSocket, 2) ; // accept only 2 clients 
	cout << "Connecting ..... " << endl; 
	addr_size = sizeof(clientAddr); 
	client1 = accept(serverSocket, (struct sockaddr*)&serverAddr, &addr_size);
	cout << "Player 1 has joined  "<< endl; 

	client2 = accept(serverSocket, (struct sockaddr*)&serverAddr, &addr_size); 
	cout << "Player 2 has joined "  << endl ;

	runGame(client1, client2 ) ; 
	close (client1, client2) ;
	close(serverSocket) ;
	
}


void restartBoard(vector<vector<string>> &board){
	for (int i= 0; i < 3; i ++){
		for (int j=0; j< 3; j ++) {
			board[i][j] = " "; 
		}
	}
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

void chooseTurn(string& turn, int playerTurn, int client1 , int client2 ){
	if (turn == "X"){
		turn = "O";
	       	playerTurn = client2; 	
	}else {
		turn = "X";	
		playerTurn = client1; 	
	}	
}


void checkResult (bool& gamerun, vector<vector<string>> board, string turn) {
	
	if ((board[0][0] == board[1][1] && board[1][1] == turn && board[2][2] == turn ) || ( board[0][2] == board[1][1] && board[1][1] == turn && board[2][0] == turn )) {

		displayBoard(board); 
		string winMsg = "The winner is " + turn ; 
		send(client1, winMsg.c_str(), winMsg.size(), 0 ) ;
		send(client2, winMsg.c_str(),winMsg.size(),0); 
	        gamerun = false; 
       		return; 		       
	}	

	for (int i = 0 ; i < 3; i ++ ) {
		if ((board[i][0] == board[i][1] && board[i][1] == turn &&  board[i][2] == turn ) || (board[0][i]==board[1][i] && board[1][i] == turn && board[2][i] == turn )) { 

			displayBoard(board); 
			string winMsg = "The winner is " + turn ; 
			send(client1, winMsg.c_str(), winMsg.size(), 0 ) ;
			send(client2, winMsg.c_str(),winMsg.size(),0); 
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
	string drawMsg = "It is a draw \n " ;
	send(client1, drawMsg.c_str(), drawMsg.size() , 0 ) ;
	send(clietn2, drawMsg.c_str(), drawMsg.size(), 0 ) ; 	
	gamerun = false; 
	return ;

} 

void sendClientData(string turn, int playerTurn, vector<vector<int>> &board) { 
	string boardData = ""; 
	int row , col;
       	bool inputRecieve = true; 	
	for (int i = 0; i < 3 ; i ++ ) { 
		for (int j = 0 ; j < 3 ; j++ ) {
	     		boardData += board[i][j] + " " ;  
	
			
		}
	}
	boardData += turn; 
	do { 
		send(playerTurn, boardData.c_str(), boardData.size(), 0 ) ; 
		recv(playerTurn, &row, sizeof(row), 0 ); 
		recv(playerTurn, &row, sizeof(col), 0) ; 
		if (board[row][col] != " ") { 
			string errorMsg = "Invalid input"; 
			send (playerTurn, errorMsg.c_str(), errorMsg.size(), 0 ) ; 
			inputRecieve = false;
			
		}else {
			inputRecieve = true; 
			board[row][col] = turn; 
		}	

	}while (inputRecieve) ;

}
void runGame(int client1, int client2 ){
	vector<vector<string>> board(3,vector<string>(3)); 
	restartBoard(board); 
	bool gamerun = true; 
	int playerTurn = client1; 
	while (gamerun){
		chooseTurn(turn,playerTurn,client1,client2); 
		displayBoard(board); 	
		sendClientData(turn,playerTurn,board); 
		checkResult(gamerun,board,turn);	
	};

}


int main() 


{
	connectClient(); 	


}

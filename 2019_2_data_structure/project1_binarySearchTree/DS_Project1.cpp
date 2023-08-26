#include <iostream>
#include "TransferWindowManager.h"

using namespace std;				

int main(int argc, char** argv)
{
	TransferWindowManager transfer_window_manager(argv[1], atoi(argv[2]));//read text name and value of total money
	//file open and make first soccerplayer list based budget
	cout << transfer_window_manager << endl;	
	//print list
	TransferWindowManager::SoccerTeam team = transfer_window_manager.getBestTeam();//make best team about soccer players in list
	//make best team
	cout << "Best Players" << endl;
	cout << team << endl;												 //print best team
	cout << "-----" << endl;
	cout << "The Transfer window close" << endl;
	cout << transfer_window_manager << endl;							 //print soccerplayer list after delete best team
	//print list after delete best team
	return 0;
} 


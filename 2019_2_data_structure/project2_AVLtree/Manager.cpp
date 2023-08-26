#define _CRT_SECURE_NO_WARNINGS
#include "Manager.h"
#include <stdlib.h>
#include <fstream>
using namespace std;

Manager::Manager()
{
	didload = 0;//initalize error check variables about load, graph, mst
	didgraph = 0;
	didmst = 0;

	flog.open("log.txt", ios::app);//open log txt to write to log txt
	flog.setf(ios::fixed);			//set log can fixed
	avl = new AVLTree(&flog);		//make avltree data place
	gp = new Graph(&flog);			//make graph data place
	iter = 0;						
	cmd = NULL;
}

Manager::~Manager()
{
	fin2.close();//close txt files
	flog.close();
}

void Manager::run(const char * command)
{
	fin.open(command);//open command.txt

	cmd = new char[40];
	
	while (!fin.eof())
	{
		iter = iter + 1;		//check loop
		fin.getline(cmd, 40);	//get line string in getline
		char * one = strtok(cmd, " ");//take command from line's first string

		if (!strcmp(one, "LOAD")) {//if commpand is load
			if (LOAD()) printSuccessCode("LOAD");//call load and success check
			else printErrorCode(100, "LOAD");//not success and print error
		}
		else if (!strcmp(one, "INSERT")) {
			if (INSERT()) printSuccessCode("INSERT");//call insert and success check
			else printErrorCode(200, "INSERT");//not success and print error

		}
		else if (!strcmp(one, "PRINT_AVL")) {
			if (didload == 1) {//success check
				flog << "==> command " << iter << ") " << "PRINT_AVL" << endl;
				PRINT_AVL();//call print
			}
			else printErrorCode(300, "PRINT_AVL");//not success and print error
		}
		else if (!strcmp(one, "SEARCH_AVL")) {
			int two = atoi(strtok(NULL, "\0"));
			if (two<1000||two>9999||!two) {
				printErrorCode(500, "SEARCH_AVL");
			}
			else if (SEARCH_AVL2(two)) {//success check
				flog << "==> command " << iter << ") " << "SEARCH_AVL" << endl;
				if (SEARCH_AVL(two)) {
				}
			}
			else printErrorCode(500, "SEARCH_AVL");//not success and print error
		}
		else if (!strcmp(one, "DELETE_AVL")) {
			if (DELETE_AVL()) printSuccessCode("DELETE_AVL");//call delete and success check
			else printErrorCode(400, "DELETE_AVL");//not success and print error
		}
		else if (!strcmp(one, "BUILD_GP")) {
			if (BUILD_GP()) printSuccessCode("BUILD_GP");
			else printErrorCode(600, "BUILD_GP");//not success and print error
		}
		else if (!strcmp(one, "PRINT_GP")) {
			if (didgraph == 1) {//success check
				flog << "==> command " << iter << ") " << "PRINT_GP" << endl;
				PRINT_GP();
			}
			else printErrorCode(700, "PRINT_GP");//not success and print error
		}
		else if (!strcmp(one, "BUILD_MST")) {
			if (didgraph == 1) {//success check
				printSuccessCode("BUILD_MST");
				BUILD_MST();
			}
			else printErrorCode(800, "BUILD_MST");//not success and print error
		}
		else if (!strcmp(one, "PRINT_MST")) {
			if (didmst == 1) {//success check
				flog << "==> command " << iter << ") " << "PRINT_MST" << endl;
				PRINT_MST();
			}
			else printErrorCode(900, "PRINT_MST");//not success and print error
		}		
		else if (!strcmp(one, "EXIT")) {
			EXIT();	//end of program
		}
		else {
			printErrorCode(0,"Unknown");//unknown commant input
		}
	}
	fin.close();
	return;
}

bool Manager::LOAD()//load function
{
	fin2.open("city_list.txt");//open city list to take data
	if (!fin2) {//if city list is not exist
		return false;//fail
	}
	char* city_data;
	if (didload == 0) {//success check 
		while (!fin2.eof()) {
			CityData * city1 = new CityData();//put data place to city1
			char *ptr = new char[200];	//string take datas
			fin2.getline(ptr, 200);		//take string from city list
			if (*ptr == '\0')break;		//linux error(core dump)
			city_data = strtok(ptr, "\t");//first word get
			city1->SetLocationId(atoi(city_data));//put firstword in city data about location id
			city_data = strtok(NULL, "\t");//second word get
			city1->Setname(city_data);//put second word in name data about name
			city_data = strtok(NULL, "\n");//third word get
			city1->Setcountry(city_data);//put third word in country data about country
			avl->Insert(city1);//load node
		}
		didload = 1;//we did load
	}
	else {//load is done so we cant load
		return false;
	}
	return true;
}

bool Manager::INSERT()//insert function
{
	if (didload==1) {
		char * two = strtok(NULL, " ");//first word get
		char * three = strtok(NULL, " ");//second word get
		char * four = strtok(NULL, "\0");//third word get
		CityData * innode = new CityData();//citydata node get data place
		if (atoi(two) < 1000 || 9999 < atoi(two)) {
			return false;
		}
		innode->SetLocationId(atoi(two));//give 3 datas to innode
		innode->Setname(three);
		innode->Setcountry(four);
		avl->Insert(innode);//insert innode to avl
		return true;
	}
	else {
		return false;
	}


}

bool Manager::PRINT_AVL()
{
	if (didload == 1) {//success check
		avl->Print();//call print function about avl
		return true;
	}
	else {//fail check
		return false;
	}
}

bool Manager::SEARCH_AVL2(int two)
{
	avl->searched2 = 0;//search check variable initialize
	avl->Search2(two);//call function
	if (avl->searched2 == 1) {//success check
		return true;
	}
	else {//fail check
		return false;
	}
}

bool Manager::SEARCH_AVL(int two)
{
	avl->searched = 0;//search check variable initialize
	avl->Search(two);//call function
	if(avl->searched==1){//success check
		return true;
	}
	else {//fail check 
		return false;
	}
}

bool Manager::DELETE_AVL()
{
	return true;
}

bool Manager::BUILD_GP()
{
	if (didload == 1) {//check did load (success check)
		gp->Build(avl);//call build function
		didgraph = 1;//you did graph
		return true;
	}
	else {//fail check
		return false;
	}
}

bool Manager::PRINT_GP()
{
	if (didgraph == 1) {//check did graph(success check)
		gp->Print_GP();//call print function
		return true;
	}
	else {//fail check
		return false;
	}
}

bool Manager::BUILD_MST()
{
	if (didgraph == 1) {//success check(did you make graph)
		gp->Kruskal();//do kruskal 
		didmst = 1;//you did make mst
		return true;
	}
	else {
		return false;
	}
}

bool Manager::PRINT_MST()
{
	if (didmst == 1) {//success check (did you make mst)
		gp->Print_MST();//print mst
		return true;
	}
	else {//fail check 
		return false;
	}
}

void Manager::EXIT()//end of program
{
	exit(1);
}

void Manager::printErrorCode(int n, const char * cmdname) {//ERROR CODE PRINNT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	flog << "Error code: " << n << endl;
}

void Manager::printSuccessCode(const char * cmdname) {//SUCCESS CODE PRINNT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	flog << "Success" << endl;
}


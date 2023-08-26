#include "Manager.h"
#include <cstring>

Manager::~Manager()
{
    if (fout.is_open())	
        fout.close();		//close fout
	//delete ferr data
}

void Manager::Run(const char* filepath)
{
    fout.open(RESULT_LOG_PATH);
    //ferr.open(ERROR_LOG_PATH);

    // TODO: implement
	ifstream comand;
	comand.open(filepath);//open file
	if (!comand)		//file is not open
	{
		fout << "====== SYSTEM ======" << endl << "CommandFileNotExist" << endl << "======================" << endl << endl;
		PrintError(CommandFileNotExist);	// ERROR
		return;
	}

	char com[30];		//save command
	char* para1;
	char* para2;	
	memset(com, 0, 30);//initialize to 0

	while (comand.getline(com, sizeof(com)))//file read
	{
		strtok(com, " \n\r");				//find command from file
		if (strcmp(com, "LOAD") == 0)		//LOAD command
		{
			para1 = strtok(NULL, "\n\r");	//take value to do
			PrintError(Load(para1));
		}
		else if (strcmp(com, "PRINT") == 0) {
			PrintError(Print());	// PRINT
		}
		else if (strcmp(com, "DIJKSTRA") == 0)	//DIJKSTRA command using set
		{
			para1 = strtok(NULL, " ");			//take first value
			para2 = strtok(NULL, "\n\r");		//and second value
			if (para1 == NULL || para2 == NULL)	//no sub value(error)
			{
				fout << "===== DIJKSTRA =====" << endl << "VertexKeyNotExist" << endl << "================" << endl << endl;
				PrintError(VertexKeyNotExist);//print error num
			}
			else if (!(m_graph.FindVertex(atoi(para1)) && m_graph.FindVertex(atoi(para2))))	//value error
			{
				fout << "===== DIJKSTRA =====" << endl << "InvalidVertexKey" << endl << "================" << endl << endl;
				PrintError(InvalidVertexKey);
			}
			else PrintError(FindShortestPathDijkstraUsingSet(atoi(para1), atoi(para2)));//print error num
		}
		else if (strcmp(com, "DIJKSTRAMIN") == 0)	//DIJKSTRA using minheap command
		{
			para1 = strtok(NULL, " ");			//take first value
			para2 = strtok(NULL, "\n\r");		//take second value
			if (para1 == NULL || para2 == NULL)	//no sub value(error)
			{
				fout << "===== DIJKSTRAMIN =====" << endl << "VertexKeyNotExist" << endl << "================" << endl << endl;
				PrintError(VertexKeyNotExist);//print error num
			}
			else if (!(m_graph.FindVertex(atoi(para1)) && m_graph.FindVertex(atoi(para2))))	//value error
			{
				fout << "===== DIJKSTRAMIN =====" << endl << "InvalidVertexKey" << endl << "================" << endl << endl;
				PrintError(InvalidVertexKey);//print error num
			}
			else PrintError(FindShortestPathDijkstraUsingMinHeap(atoi(para1), atoi(para2)));//print error num
		}
		else if (strcmp(com, "BELLMANFORD") == 0)				//BELLMANFORD command
		{
			para1 = strtok(NULL, " ");//take first value
			para2 = strtok(NULL, "\n\r");//take second value
			if (para1 == NULL || para2 == NULL)	// no sub value (error)
			{
				fout << "===== BELLMANFORD =====" << endl << "VertexKeyNotExist" << endl << "================" << endl << endl;
				PrintError(VertexKeyNotExist);//print error num
			}
			else if (!(m_graph.FindVertex(atoi(para1)) && m_graph.FindVertex(atoi(para2))))	//sub value error
			{
				fout << "===== BELLMANFORD =====" << endl << "InvalidVertexKey" << endl << "================" << endl << endl;
				PrintError(InvalidVertexKey);//print error num
			}
			else PrintError(FindShortestPathBellmanFord(atoi(para1), atoi(para2)));
		}
		else if (strcmp(com, "FLOYD") == 0) PrintError(FindShortestPathFloyd());	//FLOYD command
		else			//no command
		{
			fout << "===== " << com << " =====" << endl << "NonDefinedCommand" << endl << "===============" << endl << endl;
			PrintError(NonDefinedCommand);//error
		}
	}
}
void Manager::PrintError(Result result)
{
    //ferr << "Error code: " << result << std::endl;
	fout << "================" << endl;
	fout << "Error code: " << result << endl;					//print error
	fout << "================" << endl << endl;
}

Result Manager::Load(const char* filepath)
{
    // TODO: implement
	if (strcmp(filepath, "mapdata.txt") != 0)		//file is not exist
	{
		fout << "===== LOAD =====" << endl << "LoadFileNotExist" << endl << "===============" << endl << endl;
		return LoadFileNotExist;//return error
	}

	ifstream data;
	data.open(filepath);			//file open

	char g_size[100];
	memset(g_size, 0, 100);			//give 0 in memory
	data.getline(g_size, sizeof(g_size));//take line
	int n = atoi(g_size);			//size n like int
	char* temp;

	for (int i = 0; i < n; i++) {	//initialize graph vertex
		m_graph.AddVertex(i);
	}
	for (int i = 0; i < n; i++)		//initialize graph edge
	{
		data.getline(g_size, sizeof(g_size));//get line
		for (int j = 0; j < n; j++)
		{
			if (j == 0) { 
				temp = strtok(g_size, " "); 
			}
			else {
				temp = strtok(NULL, " ");
			}
			m_graph.AddEdge(i, j, atoi(temp));
		}
	}

	data.close();				//close file
	fout << "===== LOAD =====" << endl << "Success" << endl << "===============" << endl << endl;
	return Success;
}

Result Manager::Print()
{
    // TODO: implement
	if (m_graph.Size() == 0)		//graph is not exist
	{
		fout << "===== PRINT =====" << endl << "GraphNotExist" << endl << "===============" << endl << endl;
		return GraphNotExist;
	}
	else							//graph is exist
	{
		m_graph.Print(fout);
		return Success;
	}
}

Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    // TODO: implement
	if (m_graph.Size() == 0)		//graph is not exist
	{
		fout << "===== DIJKSTRA =====" << endl << "GraphNotExist" << endl << "===============" << endl << endl;
		return GraphNotExist;
	}
	else if (m_graph.IsNegativeEdge())	//negative edge
	{
		fout << "===== DIJKSTRA =====" << endl << "InvalidAlgorithm" << endl << "===============" << endl << endl;
		return InvalidAlgorithm;
	}
	else								//DIJKSTRA
	{
		vector<int> path = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);		//Call DIJKSTRA
		int i;

		//print using fout
		fout << "===== DIJKSTRA =====" << endl << "shortest path: ";
		for (i = 0; i < path.size() - 1; i++)
			fout << path.at(i) << " ";

		Sort(path, 0, path.size() - 2);
		fout << endl << "sorted nodes: ";
		for (i = 0; i < path.size() - 1; i++)
			fout << path.at(i) << " ";

		fout << endl << "path length: " << path.at(i) << endl << "===============" << endl << endl;
		return Success;
	}
}

Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
    // TODO: implement
	if (m_graph.Size() == 0)			//graph is not exist
	{
		fout << "===== DIJKSTRAMIN =====" << endl << "GraphNotExist" << endl << "===============" << endl << endl;
		return GraphNotExist;
	}
	else if (m_graph.IsNegativeEdge())	//negative edge
	{
		fout << "===== DIJKSTRAMIN =====" << endl << "InvalidAlgorithm" << endl << "===============" << endl << endl;
		return InvalidAlgorithm;
	}
	else								//DIJKSTRA
	{
		vector<int> path = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey);		//call DIJKSTRA
		int i;

		//print using fout
		fout << "===== DIJKSTRAMIN =====" << endl << "shortest path: ";
		for (i = 0; i < path.size() - 1; i++)
			fout << path.at(i) << " ";

		Sort(path, 0, path.size() - 2);
		fout << endl << "sorted nodes: ";
		for (i = 0; i < path.size() - 1; i++)
			fout << path.at(i) << " ";

		fout << endl << "path length: " << path.at(i) << endl << "===============" << endl << endl;
		return Success;
	}
}

Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    // TODO: implement
	if (m_graph.Size() == 0)		//graph is not exist
	{
		fout << "===== BELLMANFORD =====" << endl << "GraphNotExist" << endl << "===============" << endl << endl;
		return GraphNotExist;
	}
	else
	{
		vector<int> path = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey);		//call Bellman func
		const vector<int>::size_type size = path.size();
		if (path.size() == 0)		//negative cycle
		{
			fout << "===== BELLMANFORD =====" << endl << "NegativeCycleDetected" << endl << "===============" << endl << endl;
			return NegativeCycleDetected;
		}
		int i;

		//print using fout
		fout << "===== BELLMANFORD =====" << endl << "shortest path: ";
		for (i = 0; i < path.size() - 1; i++) {
			fout << path.at(i) << " ";
		}
		Sort(path, 0, path.size() - 2);
		fout << endl << "sorted nodes: ";
		for ( i = 0; i < path.size() - 1; i++)
			fout << path.at(i) << " ";
		fout << endl << "path length: " << path.at(i) << endl << "===============" << endl << endl;
		return Success;
	}
}

Result Manager::FindShortestPathFloyd()
{
	if (m_graph.Size() == 0)		//graph is not exist
	{
		fout << "===== FLOYD =====" << endl << "GraphNotExist" << endl << "===============" << endl << endl;
		return GraphNotExist;
	}

	vector<vector<int>> arr = m_graph.FindShortestPathFloyd();	//call Floyd function

	for (int i = 0; i < m_graph.Size(); i++)			//negative cycle
	{
		if (arr.at(i).at(i) != 0)						//check distance is 0
		{
			fout << "===== FLOYD =====" << endl << "NegativeCycleDetected" << endl << "===============" << endl << endl;
			return NegativeCycleDetected;
		}
	}
	// print using fout
	fout << "===== FLOYD =====" << endl;
	for (int i = 0; i < m_graph.Size(); i++)
	{
		for (int j = 0; j < m_graph.Size(); j++)
			fout << arr.at(i).at(j) << " ";

		fout << endl;
	}
	fout << "===============" << endl << endl;
	return Success;
}

void Manager::Sort(vector<int>& path, int start, int end)
{
	if (start < end)
	{
		if (end - start + 1 < 7)
		{
			for (int i = start + 1; i <= end; i++)		//insertion Sort
			{
				for (int j = start; j < i; j++)
				{
					if (path.at(i) < path.at(j))		//swap
					{
						int temp = path.at(i);
						for (int k = j; k >= j; k--)	//move data
							path.at(k + 1) = path.at(k);

						path.at(j) = temp;				//insertion
					}
				}
			}
		}
		else
		{
			int temp, i = start, j = end + 1, pivot = path.at(i);
			do
			{
				do i++; while (path.at(i) < pivot);	//move left
				do j--; while (path.at(j) > pivot);	//move right
				if (i < j)
				{
					temp = path.at(i);				//swap them
					path.at(i) = path.at(j);
					path.at(j) = temp;
				}
			} while (i < j);

			temp = path.at(start);					//swap them
			path.at(start) = path.at(j);
			path.at(j) = temp;

			Sort(path, start, pivot - 1);//recursion
			Sort(path, pivot + 1, end);
		}
	}
}
#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include "Result.h"
#include "Graph.h"
#include <fstream>

class Manager
{
private:
    // the filepath for the result log
    const char* RESULT_LOG_PATH = "log.txt";
    // the filepath for the error log
    

    // the file stream for the result log
    std::ofstream fout;
    // the file stream for the error log
    
    // graph instance to manage the vertics.
    Graph m_graph;

public:
    ~Manager();
    void Run(const char* filepath);
    void PrintError(Result result);

private:
    Result Load(const char* filepath);
    Result Print();
    Result FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey);//dijkstra using set
    Result FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey);//dijkstra using min heap
    Result FindShortestPathBellmanFord(int startVertexKey, int endVertexKey);	//bellmanford
    Result FindShortestPathFloyd();												//floyd
	void Sort(vector<int>& path, int start, int end);//sort to make shortpath
};

#endif

#ifndef RESULT_H
#define RESULT_H

enum Result
{
    Success = 0,				//number that mached error type
    CommandFileNotExist = 100,
    LoadFileNotExist=101,
    VertexKeyNotExist = 200,
    InvalidVertexKey = 201,
    GraphNotExist = 202,
    InvalidAlgorithm=203,
    NegativeCycleDetected=204,
    NonDefinedCommand = 300,
};

#endif

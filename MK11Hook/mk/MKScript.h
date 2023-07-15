#pragma once
#include "..\utils.h"

// from mkoasm
#pragma pack(push, 1)
struct mko_function_header_mk11 {
    char* functionName; // offset to string table in mko
    unsigned int functionHash;
    int field12;
    int function_index;
    unsigned int paramsHash;
    int64 field24;
    int64 functionOffset;
    int64 field40;
    int64 field48;
    int64 field56;
    int   size;
    int   field68;
    int   field72;
    int   field76;
    int   field80;
    unsigned int hash;
    unsigned int hash2;
    int   field92;
    int   field96;
    int   field100;
    int   field104;
    int   field112;
};
#pragma pack(pop)

struct mko_variable_header_mk10 {
    int stack_offset;
    int data;
    unsigned int nameHash;
    int size;
    int stride;
    int pad;
};

class MKScript {
public:
	char pad[76];
    int numFunctions;
	int numVariables;
	char _pad[28];
	int bytecodeSize;
    char __pad[596];

    mko_function_header_mk11** functions;

	int GetFunctionID(int hash);
	int64 GetVar(const char* name);
};

MKScript* GetScript(const char* name);

VALIDATE_OFFSET(MKScript, numFunctions, 76);
VALIDATE_OFFSET(MKScript, numVariables, 80);
VALIDATE_OFFSET(MKScript, bytecodeSize, 112);
VALIDATE_OFFSET(MKScript, functions, 712);
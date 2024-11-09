#pragma once
#include "AES.h"
#include <fstream>
#include <msclr\marshal_cppstd.h>

//==================================================================================================================
string InputFromFile(ifstream& in);
void WriteStateToFile(ofstream& out, BYTE State[ROW][MAXCOL], BYTE& Nb);
//==================================================================================================================
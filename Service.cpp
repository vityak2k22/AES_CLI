#include "Service.h"

//==================================================================================================================
string InputFromFile(ifstream& in) {
    string str;
    int c;
    while ((c = in.get()) != EOF) {
        printf("%02x\n", c);
        str += (char)c;
    }

    return str;
}
//==================================================================================================================
void WriteStateToFile(ofstream& out, BYTE State[ROW][MAXCOL], BYTE& Nb) {
    for (BYTE i = 0; i < Nb; i++)
        for (BYTE j = 0; j < ROW; j++)
            out << State[j][i];
}
//==================================================================================================================
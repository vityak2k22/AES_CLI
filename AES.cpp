#include "AES.h"
#include "AES_tables.h"
#include "Service.h"


#define RotWord(x) (((x) << 8) | ((x) >> 24))
#define SubWord(word) (DWORD)Sbox[(BYTE)((word) >> 24)] << 24 ^ (DWORD)Sbox[BYTE((word) >> 16 & 0xFF)] << 16 ^ \
                        (DWORD)Sbox[(BYTE)((word) >> 8 & 0xFF)] << 8 ^ (DWORD)Sbox[(BYTE)(word)]
#define Mul01(x) (x)
#define Mul02(x) xtime[(x)]
#define Mul03(x) (Mul02(x) ^ (x))

using namespace msclr::interop;

//==================================================================================================================
void AddRoundKey(BYTE state[ROW][MAXCOL], vector<DWORD>& round_key, size_t initial_index, BYTE& Nb);
void ByteSub(BYTE state[ROW][MAXCOL], BYTE& Nb, E_EncryptMode encrypt_mode);
void ShiftRow(BYTE state[ROW][MAXCOL], BYTE& Nb);
void InvShiftRow(BYTE state[ROW][MAXCOL], BYTE& Nb);
void MixColumn(BYTE state[ROW][MAXCOL], BYTE& Nb);
void InvMixColumn(BYTE state[ROW][MAXCOL], BYTE& Nb);
//==================================================================================================================
void AESBlock(E_EncryptMode encrypt_mode, BYTE State[ROW][MAXCOL], vector<DWORD>& round_key, BYTE& Nb, BYTE& Nr) {
    switch (encrypt_mode) {
    case EEM_Encrypt:
        AddRoundKey(State, round_key, 0, Nb);

        for (BYTE i = 1; i <= Nr - 1; i++) {
            ByteSub(State, Nb, EEM_Encrypt);
            ShiftRow(State, Nb);
            MixColumn(State, Nb);
            AddRoundKey(State, round_key, Nb * i, Nb);
        }

        ByteSub(State, Nb, EEM_Encrypt);
        ShiftRow(State, Nb);
        AddRoundKey(State, round_key, Nb * Nr, Nb);
        break;



    case EEM_Decrypt:
        AddRoundKey(State, round_key, Nb * Nr, Nb);

        for (BYTE i = Nr - 1; i >= 1; i--) {
            InvShiftRow(State, Nb);
            ByteSub(State, Nb, EEM_Decrypt);
            AddRoundKey(State, round_key, Nb * i, Nb);
            InvMixColumn(State, Nb);
        }
        InvShiftRow(State, Nb);
        ByteSub(State, Nb, EEM_Decrypt);
        AddRoundKey(State, round_key, 0, Nb);
        break;
    }
}
//==================================================================================================================
void AESProcess(String^ path_initialtext, String^ path_finaltext, String^ key_phrase, E_BlockMode block_mode, E_KeyMode key_mode, E_EncryptMode encrypt_mode) {
    ifstream in((LPCWSTR)Marshal::StringToHGlobalUni(path_initialtext).ToPointer(), ios::binary);
    string initialtext = InputFromFile(in);
    in.close();

    BYTE Nb = (WORD)block_mode / 32;        // number of 32-bit words in block
    BYTE Nk = (WORD)key_mode / 32;          // number of 32-bit words in round key
    BYTE Nr = max(Nb, Nk) + 6;              // round number

    BYTE block_size = block_mode / 8;   // block size in bytes
    size_t length_pt = initialtext.length();
    size_t length_pt_with_zeros = length_pt + (block_size - length_pt % block_size) % block_size;


    string key = marshal_as<std::string>(key_phrase);
    if (key.length() < key_mode / 8)
        key.insert(key.end(), key_mode / 8 - key.length(), 0);
    vector<DWORD> round_key;

    ofstream out((LPCWSTR)Marshal::StringToHGlobalUni(path_finaltext).ToPointer(), ios::binary);
    for (size_t initial_text_index = 0; initial_text_index + block_size <= length_pt_with_zeros; initial_text_index += block_size) {
        BYTE State[ROW][MAXCOL] = {};

        InitBlock(initialtext, State, Nb, initial_text_index);
        round_key = KeyExpansion(key, Nb, Nk, Nr);
        AESBlock(encrypt_mode, State, round_key, Nb, Nr);
        
        WriteStateToFile(out, State, Nb);
    }
    out.close();
}
//==================================================================================================================
void InitBlock(string& text, BYTE State[ROW][MAXCOL], BYTE& Nb, size_t initial_index) {
    BYTE j = 0;
    while (initial_index < text.length() && j < Nb) {
        State[initial_index % ROW][j] = (BYTE)text[initial_index];
        if (initial_index % ROW == 3)
            j++;
        initial_index++;
    }
}
//==================================================================================================================
vector<DWORD> KeyExpansion(string& key, BYTE& Nb, BYTE& Nk, BYTE& Nr) {
    vector<DWORD> w(Nb * (Nr + 1));
    BYTE i = 0;
    
    while (i < Nk) {
        w[i] = ((DWORD)key[4 * i] << 24) ^ ((DWORD)key[4 * i + 1] << 16) ^ ((DWORD)key[4 * i + 2] << 8) ^ (DWORD)key[4 * i + 3];
        i++;
    }
    
    DWORD temp = 0;
    while (i < Nb * (Nr + 1)) {
        temp = w[i-1];
        if (i % Nk == 0)
            temp = SubWord(RotWord(temp)) ^ Rcon[i / Nk];
        else if (Nk > 6 && i % Nk == 4)
            temp = SubWord(temp);
        w[i] = w[i - Nk] ^ temp;
        i++;
    }
    return w;
}
//==================================================================================================================
void AddRoundKey(BYTE state[ROW][MAXCOL], vector<DWORD>& round_key, size_t initial_index, BYTE& Nb) {
    for (size_t i = 0; i < Nb; i++) {
        state[0][i] ^= (BYTE)(round_key[initial_index + i] >> 24);
        state[1][i] ^= (BYTE)(round_key[initial_index + i] >> 16 & 0xFF);
        state[2][i] ^= (BYTE)(round_key[initial_index + i] >> 8 & 0xFF);
        state[3][i] ^= (BYTE)(round_key[initial_index + i] & 0xFF);
    }
}
//==================================================================================================================
void ByteSub(BYTE state[ROW][MAXCOL], BYTE& Nb, E_EncryptMode encrypt_mode) {
    for (size_t i = 0; i < Nb; i++) {
        state[0][i] = encrypt_mode == EEM_Encrypt ? Sbox[state[0][i]] : Inv_Sbox[state[0][i]];
        state[1][i] = encrypt_mode == EEM_Encrypt ? Sbox[state[1][i]] : Inv_Sbox[state[1][i]];
        state[2][i] = encrypt_mode == EEM_Encrypt ? Sbox[state[2][i]] : Inv_Sbox[state[2][i]];
        state[3][i] = encrypt_mode == EEM_Encrypt ? Sbox[state[3][i]] : Inv_Sbox[state[3][i]];
    }
}
//==================================================================================================================
void ShiftRow(BYTE state[ROW][MAXCOL], BYTE& Nb) {
    BYTE temp[ROW - 1] = {};
    BYTE shift = 0;
    for (BYTE i = 1; i < ROW; i++) {
        shift = i;
        if (i > 1 && Nb == 8)
            shift++;

        for (BYTE j = 0; j < shift; j++)
            temp[j] = state[i][j];

        for (BYTE j = 0; j < Nb - shift; j++)
            state[i][j] = state[i][j + shift];

        for (BYTE j = Nb - shift; j < Nb; j++)
            state[i][j] = temp[j - (Nb - shift)];
    }
}
//==================================================================================================================
void InvShiftRow(BYTE state[ROW][MAXCOL], BYTE& Nb) {
    BYTE temp[ROW - 1] = {};
    BYTE shift = 0;
    for (BYTE i = 1; i < ROW; i++) {
        shift = i;
        if (i > 1 && Nb == 8)
            shift++;

        for (BYTE j = 0; j < shift; j++)
            temp[j] = state[i][Nb - 1 - j];

        for (BYTE j = Nb - 1; j >= shift; j--)
            state[i][j] = state[i][j - shift];

        for (BYTE j = 0; j < shift; j++)
            state[i][shift - 1 - j] = temp[j];
    }
}
//==================================================================================================================
void MixColumn(BYTE state[ROW][MAXCOL], BYTE& Nb) {
    /*BYTE temp[ROW] = {};
    for (BYTE i = 0; i < Nb; i++) {
        for (BYTE j = 0; j < ROW; j++)
            temp[j] = state[j][i];
        
        state[0][i] = Mul02(temp[0]) ^ Mul03(temp[1]) ^ Mul01(temp[2]) ^ Mul01(temp[3]);
        state[1][i] = Mul01(temp[0]) ^ Mul02(temp[1]) ^ Mul03(temp[2]) ^ Mul01(temp[3]);
        state[2][i] = Mul01(temp[0]) ^ Mul01(temp[1]) ^ Mul02(temp[2]) ^ Mul03(temp[3]);
        state[3][i] = Mul03(temp[0]) ^ Mul01(temp[1]) ^ Mul01(temp[2]) ^ Mul02(temp[3]);
    }*/

    BYTE t = 0, u = 0, v = 0;
    for (BYTE i = 0; i < Nb; i++) {
        t = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
        u = state[0][i];

        v = xtime[state[0][i] ^ state[1][i]];
        state[0][i] ^= v ^ t;

        v = xtime[state[1][i] ^ state[2][i]];
        state[1][i] ^= v ^ t;

        v = xtime[state[2][i] ^ state[3][i]];
        state[2][i] ^= v ^ t;

        v = xtime[state[3][i] ^ u];
        state[3][i] ^= v ^ t;
    }
}
//==================================================================================================================
void InvMixColumn(BYTE state[ROW][MAXCOL], BYTE& Nb) {
    BYTE t = 0, u = 0, v = 0;
    for (BYTE i = 0; i < Nb; i++) {
        u = xtime[xtime[state[0][i] ^ state[2][i]]];
        v = xtime[xtime[state[1][i] ^ state[3][i]]];
        state[0][i] ^= u;
        state[1][i] ^= v;
        state[2][i] ^= u;
        state[3][i] ^= v;
    }
    MixColumn(state, Nb);
}
//==================================================================================================================
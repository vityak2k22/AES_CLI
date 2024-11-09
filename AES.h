#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include "Config.h"

#define ROW (32/8)
#define MAXCOL (256/32)

using namespace std;

//==================================================================================================================
enum E_EncryptMode {
	EEM_Encrypt,
	EEM_Decrypt
};
//==================================================================================================================
enum E_BlockMode {
	EBM_128 = 128,
	EBM_192 = 192,
	EBM_256 = 256
};
//==================================================================================================================
enum E_KeyMode {
	EKM_128 = 128,
	EKM_192 = 192,
	EKM_256 = 256
};
//==================================================================================================================
void InitBlock(string& text, BYTE block[ROW][MAXCOL], BYTE& Nb, size_t initial_index);
vector<DWORD> KeyExpansion(string& key, BYTE& Nb, BYTE& Nk, BYTE& Nr);
void AESProcess(String^ path_initialtext, String^ path_finaltext, String^ key_phrase, E_BlockMode block_mode, E_KeyMode key_mode, E_EncryptMode encrypt_mode);
//==================================================================================================================

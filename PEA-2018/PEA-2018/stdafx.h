#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <cwchar>
#include <string>
#include <ctime>
#include <conio.h>
#include <stdlib.h>



#define endl std::endl
#define cout std::cout
#define left std::left

#define FLAG_ST_F					"STANDART"
#define FLAG_MAIN					"begin"
#define FLAG_FUN					"fun"
#define FLAG_LIT					"LIT"

#define NAME_STANDART_F_concat		"concat"
#define NAME_STANDART_F_strsub		"strsub"
#define NAME_STANDART_F_lenstr		"lenstr"

#define TYPE_INTEGER				"integer"
#define TYPE_STRING					"string"

#define LEX_ID						'i'
#define LEX_BEGIN					'b'
#define LEX_SIGN					'v'
#define LEX_FUNCTION				'f'
#define LEX_RECOVERY				'r'
#define LEX_OUTPUT					'o'

#define LEX_LITERAL					'l'
#define LEX_STANDART_FUNCTION		's'
#define LEX_PARAMETR				'p'
#define LEX_VARIABLE				'x'

#define LEX_END_PROGRAMM_BLOCK		'}'
#define LEX_START_PROGRAMM_BLOCK	'{'
#define LEX_LEFT_BRACKET			'('
#define LEX_RIGHT_BRACKET			')'
#define LEX_COMMA					','
#define LEX_SEMICOLON				';'
#define LEX_EQUALITY				'='

#define LEX_MULTIPLICATION			'*'
#define LEX_DIFFERENCE				'-'
#define LEX_SUMM					'+'
#define LEX_DIVISION				'/'

#define MAX_KOL_ERRORS_IN_LA 5

#define _CRT_SECURE_NO_WARNINGS
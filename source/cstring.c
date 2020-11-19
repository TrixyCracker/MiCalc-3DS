#include "cstring.h"

int string_to_int(const char * _Str) 
{

    const int lenght = string_lenght(_Str);

    int result = 0;
    for (int i = 0; i < lenght; ++i)
        result = result * 10 + (int)char_to_int(_Str[i]);

    return result;
}

uint8 char_to_int(const char _Char)
{
    
    if (_Char == '0')
        return 0;
    else if (_Char == '1')
        return 1;
    else if (_Char == '2')
        return 2;
    else if (_Char == '3')
        return 3;
    else if (_Char == '4')
        return 4;
    else if (_Char == '5')
        return 5;
    else if (_Char == '6')
        return 6;
    else if (_Char == '7')
        return 7;
    else if (_Char == '8')
        return 8;
    else if (_Char == '9')
        return 9;
    else
        return 0;

}

int string_to_uint8_array(uint8 * _Dest, const char * _Str, int _Size) 
{
    for (int i = 0; i < _Size; ++i)
        _Dest[i] =  char_to_uint8(_Str[i * 2]) * 16 + char_to_uint8(_Str[i * 2 + 1]);

    return 1;
}

uint8 char_to_uint8(const char _Char)
{

	if (_Char == '0')
		return 0x0;
	else if (_Char == '1')
		return 0x1;
	else if (_Char == '2')
		return 0x2;
	else if (_Char == '3')
		return 0x3;
	else if (_Char == '4')
		return 0x4;
	else if (_Char == '5')
		return 0x5;
	else if (_Char == '6')
		return 0x6;
	else if (_Char == '7')
		return 0x7;
	else if (_Char == '8')
		return 0x8;
	else if (_Char == '9')
		return 0x9;
	else if (_Char == 'A' || _Char == 'a')
		return 0xA;
	else if (_Char == 'B' || _Char == 'b')
		return 0xB;
	else if (_Char == 'C' || _Char == 'c')
		return 0xC;
	else if (_Char == 'D' || _Char == 'd')
		return 0xD;
	else if (_Char == 'E' || _Char == 'e')
		return 0xE;
	else if (_Char == 'F' || _Char == 'f')
		return 0xF;
	else
		return 0xFF;

}

void uint8_array_to_string(char * _Dest, const uint8 * _Str, const int _Size)
{
    for (int i = 0; i < _Size; ++i)
    {
        _Dest[i * 2] = uint8_to_char(_Str[i] >> 4);
        _Dest[i * 2 + 1] = uint8_to_char(_Str[i] & 0xF);
    }

    _Dest[_Size * 2] = '\0';
}

char uint8_to_char(const uint8 u8)
{

	if (u8 == 0x0)
		return '0';
	else if (u8 == 0x1)
		return '1';
	else if (u8 == 0x2)
		return '2';
	else if (u8 == 0x3)
		return '3';
	else if (u8 == 0x4)
		return '4';
	else if (u8 == 0x5)
		return '5';
	else if (u8 == 0x6)
		return '6';
	else if (u8 == 0x7)
		return '7';
	else if (u8 == 0x8)
		return '8';
	else if (u8 == 0x9)
		return '9';
	else if (u8 == 0xA)
		return 'A';
	else if (u8 == 0xB)
		return 'B';
	else if (u8 == 0xC)
		return 'C';
	else if (u8 == 0xD)
		return 'D';
	else if (u8 == 0xE)
		return 'E';
	else if (u8 == 0xF)
		return 'F';

    return 0;
}

void memory_copy(void * _Dest, const void * _Src, const int _Size) 
{
    char * dest = _Dest;
    const char * src = _Src;

    for (int i = 0; i < _Size; i++)
        *(dest + i) = *(src + i);

}

int string_lenght(const char * _Str) 
{
    int lenght = 0;

    while(_Str[lenght] != '\0')
        lenght += 1;

    return lenght;
}

void string_set(char * _Str, const int _Size, const int _Value) 
{

    for (int i = 0; i < _Size; i++) 
        _Str[i] = _Value;

}

void string_copy(char * _Dest, const char * _Str) {
    const int strlen = string_lenght(_Str);

    for (int i = 0; i < strlen; i++)
        _Dest[i] = _Str[i];

    _Dest[strlen] = '\0';
}

int string_compare(const char * _Str1, const char * _Str2) {
    const int strlen = string_lenght(_Str1);

    for (int i = 0; i <= strlen; i++) {

        if (_Str1[i] != _Str2[i])
            return 0;

    }

    return 1;
}

void string_addstring(char * _Dest, const char * _Str) {
    const int strlen = string_lenght(_Str);

    for (int i = 0; i <= strlen; i++)
        string_addchar(_Dest, _Str[i]);

}

void string_addchar(char * _Dest, const char _c) {

    const int strlen = string_lenght(_Dest);

    _Dest[strlen] = _c;
    _Dest[strlen + 1] = '\0';

}

void string_removelastchar(char * _Dest)
{
    const int strlen = string_lenght(_Dest);

    _Dest[strlen - 1] = '\0';
}

void string_lowercase(char * _Dest, const char * _Str) {
    const int strlen = string_lenght(_Str);

    for (int i = 0; i < strlen; i++)
        _Dest[i] = char_lowercase(_Str[i]);

    _Dest[strlen] = '\0';
}

void string_uppercase(char * _Dest, const char * _Str) {
    const int strlen = string_lenght(_Str);

    for (int i = 0; i < strlen; i++)
        _Dest[i] = char_uppercase(_Str[i]);

    _Dest[strlen] = '\0';
}

char char_lowercase(const char _Char) {
    const char lower[27] = "abcdefghijklmnopqrstuvwxyz";
    const char upper[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < 27; i++) {

        if (_Char == upper[i]) 
            return lower[i];

    }

    return _Char;
}

char char_uppercase(const char _Char) {
    const char lower[27] = "abcdefghijklmnopqrstuvwxyz";
    const char upper[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < 27; i++) {

        if (_Char == lower[i]) 
            return upper[i];

    }

    return _Char;
}
#pragma once

#include <stdint.h>

void mizip_calculate_allkeys(uint8_t _Dest[10][6], const uint8_t _UID[4]);
void mizip_calculate_key(uint8_t _Dest[6], const uint8_t _UID[4], const uint8_t _Block, const char _Type);
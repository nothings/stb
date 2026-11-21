#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"
#include <windows.h>
#include <stdio.h>

unsigned short cols[9] = {
	0x93, 0x3b, 0xb2, 0x2a, 0xa6, 0x6c, 0xc4, 0x40
};

int main(void){
	int x, y;
	for(y = 0; y < 16; y++){
		for(x = 0; x < 32; x++){
			float n = stb_perlin_fbm_noise3_seed(x * 0.1f, y * 0.1f, 0.0f, 2.0f, 0.5f, 6, 68);
            HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hOutput, cols[(int)(n*4.0f+4.0f)]);
            putchar(" .:ioVM@"[(int)(fmod(n + 1.0f, 0.25f) * 32.0f)]);
		}
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOutput, 0x00);
        putchar('#');
        putchar('\n');
	}
}


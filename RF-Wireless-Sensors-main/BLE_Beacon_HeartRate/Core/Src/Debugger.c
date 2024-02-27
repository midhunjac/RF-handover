#include "../Inc/Debugger.h"

void printRegBin(uint32_t value)
{
	int j= 0;
	for (int i = 31; i >= 0; i--)
    {
		if (j == 8)
		{
			printf(" ");
		    j = 0;
		}
		uint8_t bitValue = (value >> i) & 1;
        printf("%d", bitValue);
        j++;
    }

    printf("\r\n");
    return;
}

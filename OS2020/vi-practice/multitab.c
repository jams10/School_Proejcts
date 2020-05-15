#include <stdio.h>

int main()
{
	int row=1, col=1;
	for(; row<=9; ++row)
	{
		for(; col<=9; ++col)
		{
			printf("%d*%d=%-4d",col,row,col*row);
		}
		printf("\n");
		col=1;
	}
}

#include <stdio.h>

int data = 888;
int global_un;
const int con = 15;

int main()
{
	int j = 67;
	double k = j / 8.0;

	j = (j + 7) & -8;

	k = j / 8.0;
	printf("j = %d, Divided = %lf\n", j, k);

	return 0;
}

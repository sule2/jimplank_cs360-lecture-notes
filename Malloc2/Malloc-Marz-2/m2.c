//Demonstrate how to align data

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int val;
	int d;
	int alignment;

	if (argc >= 2) {
		d = atoi(argv[1]);
	}
	else {
		d = 12345;
	}

	//Align using arithmetic:
	val = d;
	alignment = val % 8;
	printf("Arithmetic round up\n");
	printf("val before alignment %d (%d / 8.0) = %lf\n", val, val, (val / 8.0));
	//If alignment == 0, we're already aligned
	if (alignment > 0) {
		val += 8 - alignment;
	}
	printf("val after  alignment %d (%d / 8.0) = %lf [adjusted by %d]\n", val, val, (val / 8.0), 8 - alignment);

	val = d;
	printf("\n\nArithmetic round down\n");
	printf("val before alignment %d (%d / 8.0) = %lf\n", val, val, (val / 8.0));
	//If alignment == 0, we're already aligned
	if (alignment > 0) {
		val -= alignment;
	}
	printf("val after  alignment %d (%d / 8.0) = %lf [adjusted by %d]\n", val, val, (val / 8.0), -alignment);


	return 0;
}

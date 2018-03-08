//Demonstrate how to align data

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int val;
	int d;

	if (argc >= 2) {
		d = atoi(argv[1]);
	}
	else {
		d = 12345;
	}

	printf("Alignment factor 0x%x\n", -8);
	val = d;
	printf("Logical round up\n");
	printf("val before alignment %d (%d / 8.0) = %lf\n", val, val, (val / 8.0));

	//This will round up
	val = (val+7) & -8;

	printf("val after  alignment %d (%d / 8.0) = %lf\n", val, val, (val / 8.0));

	val = d;
	printf("\n\nLogical round down\n");
	printf("val before alignment %d (%d / 8.0) = %lf\n", val, val, (val / 8.0));
	//This will round down
	val = val & -8;
	printf("val after  alignment %d (%d / 8.0) = %lf\n", val, val, (val / 8.0));



	return 0;
}

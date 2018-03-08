#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct me {
	char c;
	int i;
};//__attribute__((packed));

int main()
{
	//Why is this 8 and not 5? ALIGNMENT!
	printf("Sizeof me is %d\n", sizeof(struct me));

	return 0;
}

CC=gcc

CFLAGS=-Wall -g -m32

SOURCES_C = $(wildcard *.c)
OBJS_C = $(patsubst %.c,%,$(SOURCES_C))

all: $(OBJS_C)

%:%.c Makefile
	@#echo "C file = " $<
	@#echo "output file = " $@
	$(CC) $(CFLAGS) -o $@ $<


clean:
	@rm -f $(OBJS_C)

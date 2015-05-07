CFLAGS=-Wall -Wextra
LIBS=-lm

blctl: blctl.o
	cc -o $@ $^ $(LIBS)

all: blctl

clean:
	rm -f *.o
	rm -f blctl

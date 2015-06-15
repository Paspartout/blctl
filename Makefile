CFLAGS=-Os -Wall -Wextra
#CFLAGS=-O0 -g -ggdb -Wall -Wextra
LIBS=-lm

TARGET=blctl

$(TARGET): blctl.o config.h
	cc -o $@ $^ $(LIBS)

install: $(TARGET)
	cp $(TARGET) ${DESTDIR}${PREFIX}/bin/

clean:
	rm -f *.o
	rm -f blctl

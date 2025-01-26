CC=cc
CFLAGS=-Wall -O2

all: raid diar

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f raid diar a.out *.part? *.2

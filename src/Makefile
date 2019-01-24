CFLAGS:=-O2 -Wall -std=c11 -D_POSIX_C_SOURCE=200809 -D_BSD_SOURCE -D_DEFAULT_SOURCE
%.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
main: main.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) main.o

CFLAGS:=-O2 -Wall -std=c11 -D_XOPEN_SOURCE=600
%.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
main: main.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) main.o

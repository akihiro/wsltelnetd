CFLAGS:=-O2 -Wall
%.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
main: main.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) main.o

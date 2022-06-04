shell:  shell.o print.o tools.o config.o filecmd.o advanced.o toolcmd.o main.o 
	g++  $^ -o shell 
.c.o:
	g++ -c $<
clean:
	rm -f *.o
cleanfile:
	rm .history


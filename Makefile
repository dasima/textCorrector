.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=server
OBJS=main_dic.o string_utils.o text_corrector.o get_config.o 
OTHER=-std=c++0x
LINKS=-lecho -lpthread
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LINKS)
%.o:%.cc
	$(CC) $(CFLAGS) -c $< -o $@ $(OTHER)
clean:
	rm -f *.o $(BIN)

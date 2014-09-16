.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=server
OBJS=main_server.o text_corrector.o string_utils.o cache.o index.o log.o query_server.o get_config.o cache_manager.o
OTHER=-std=c++0x
LINKS=-lecho -lpthread
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LINKS)
%.o:%.cc
	$(CC) $(CFLAGS) -c $< -o $@ $(OTHER)
clean:
	rm -f *.o $(BIN)

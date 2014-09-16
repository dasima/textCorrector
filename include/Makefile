.PHONY:clean install
CC=g++
CFLAGS=-Wall -g
BIN=libecho.a
INCLUDE=echo
SRC=src
OBJS=socket.o rio.o tcp_connection.o poll_poller.o tcp_server.o thread.o condition.o thread_pool.o exception.o timer.o timer_thread.o
STARD=-std=c++0x -rdynamic
$(BIN):$(OBJS)
	ar -crv $@ -o $^
	chmod 0777 $@
	rm -f *.o
	rm -rf $(INCLUDE)
	mkdir $(INCLUDE)
	cp src/*.h $(INCLUDE)/
%.o:$(SRC)/%.cc
	$(CC) $(CFLAGS) -c $< -o $@ $(STARD)
install:
	sudo cp $(BIN) /usr/lib/
	sudo cp $(INCLUDE) /usr/include/ -r
clean:
	rm -rf *.o $(BIN) echo



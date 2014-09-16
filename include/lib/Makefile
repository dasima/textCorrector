.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=libecho.a
OBJS=socket.o rio.o tcp_connection.o poll_poller.o tcp_server.o thread.o condition.o exception.o thread_pool.o timer.o timer_thread.o
STARD=-std=c++0x -rdynamic
LINKS=-lpthread
$(BIN):$(OBJS)
	ar -crv $@ -o $^
	chmod +x $@
	rm -f *.o
	mkdir echo
	cp *.h echo/
%.o:%.cc
	$(CC) $(CFLAGS) -c $< -o $@ $(STARD)
clean:
	rm -rf *.o $(BIN) echo

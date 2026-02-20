CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lpthread

OBJS = fetch/grab.o fetch/network.o fetch/utils.o fetch/http.o fetch/fetch.o fetch/timer.o concurrency/task_queue.o concurrency/thread_pool.o

.PHONY: all clean

all: clean grab

grab: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

fetch/grab.o: fetch/grab.c fetch/grab.h fetch/fetch.h fetch/timer.h
	$(CC) $(CFLAGS) -c fetch/grab.c -o fetch/grab.o

fetch/network.o: fetch/network.c fetch/network.h
	$(CC) $(CFLAGS) -c fetch/network.c -o fetch/network.o

fetch/utils.o: fetch/utils.c fetch/utils.h
	$(CC) $(CFLAGS) -c fetch/utils.c -o fetch/utils.o

fetch/http.o: fetch/http.c fetch/http.h fetch/grab.h fetch/utils.h
	$(CC) $(CFLAGS) -c fetch/http.c -o fetch/http.o

fetch/fetch.o: fetch/fetch.c fetch/fetch.h fetch/http.h fetch/network.h fetch/utils.h concurrency/thread_pool.h
	$(CC) $(CFLAGS) -c fetch/fetch.c -o fetch/fetch.o

fetch/timer.o: fetch/timer.c fetch/timer.h
	$(CC) $(CFLAGS) -c fetch/timer.c -o fetch/timer.o

concurrency/task_queue.o: concurrency/task_queue.c concurrency/task_queue.h
	$(CC) $(CFLAGS) -c concurrency/task_queue.c -o concurrency/task_queue.o

concurrency/thread_pool.o: concurrency/thread_pool.c concurrency/thread_pool.h concurrency/task_queue.h
	$(CC) $(CFLAGS) -c concurrency/thread_pool.c -o concurrency/thread_pool.o

clean:
	rm -f fetch/*.o concurrency/*.o grab
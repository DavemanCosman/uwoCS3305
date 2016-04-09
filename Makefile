dcosmanAsn4:
	gcc -o simulator dcosmanAsn4.c

run:
	./simulator 4 trace LRU

cleanup:
	rm simulator

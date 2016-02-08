all:
	dcosmanShell
	run
	cleanup

run:
	./dcosmanShell

dcosmanShell: *.c
	gcc -o dcosmanShell *.c

cleanup:
	rm dcosmanShell

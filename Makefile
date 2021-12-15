all:
	gcc listdir.c -o listdir
	gcc listdir.c -o listdir-fs -D FILE_SIZE


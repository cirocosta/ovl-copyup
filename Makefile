build:
	gcc -O2 -static ./main.c

setup:
	mkdir ./merged ./work ./upper ./lower
	dd if=/dev/zero of=./lower/a bs=$$((1 << 12)) count=$$((1 << 18))
	sudo mount \
		-t overlay \
		overlay \
		-o lowerdir=./lower,upperdir=./upper,workdir=./work \
		./merged

teardown:
	sudo umount ./merged
	rm -rf ./lower ./upper ./merged ./work


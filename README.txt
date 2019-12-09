create an overlay-based directory tree with a large file in the lower dir


	mkdir ./merged ./work ./upper ./lower

	dd if=/dev/zero of=./lower/a bs=$((1 << 12)) count=$((1 << 18))
	262144+0 records in
	262144+0 records out
	1073741824 bytes (1.1 GB, 1.0 GiB) copied, 0.804386 s, 1.3 GB/s


	sudo mount \
		-t overlay \
		overlay \
		-o lowerdir=./lower,upperdir=./upper,workdir=./work \
		./merged

	tree
	.
	├── lower
	│   └── a
	├── merged
	│   └── a
	└── upper



		(this can be done with `make setup`)


run the tracer, and then perform a `chown(2)` in `merged/a` to see the cost of a
copy up


	sudo ./trace.bt
	PID      COMM             NAME             LEN(B)           ELAPSED (ms)
	12752    a.out            ./merged/a       1073741824       780
	

		(for an example `chown(2)`ing thing, see `./main.c`)





LICENSE - MIT

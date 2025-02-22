all: bin bin/add bin/sub bin/mul

bin/add: src/add/add.c | bin
	gcc $< -o $@

bin/sub: src/sub/sub.c | bin
	gcc $< -o $@

bin/mul: src/mul/mul.c | bin
	gcc $< -o $@

bin:
	mkdir -p bin

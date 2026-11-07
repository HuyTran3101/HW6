all: rbt-tests

rbt-tests: RedBlackTree.cpp RedBlackTree.h RedBlackTreeTests.cpp
	g++ RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-tests

test: rbt-tests
	./rbt-tests

run: test

valgrind: rbt-tests
	valgrind --leak-check=full ./rbt-tests

clean:
	rm -f rbt-tests

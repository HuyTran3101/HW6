# HW6 — Red-Black Tree, Part 1

Implements integer insertion, search, minimum/maximum, size, deep copying,
and recursive infix/prefix/postfix traversals. Duplicate insertion and querying
an empty tree's minimum or maximum throw `std::invalid_argument`.

## Build and run

Requires GNU Make and a C++11 compiler (`g++` by default).

```sh
make test       # build and run the consolidated test program
make valgrind   # run it with full leak/error checking
make clean      # remove generated executables
```

`make` builds the test program; `make run` also runs it.

## Files and rubric coverage

| Requirement | Implementation or verification |
| --- | --- |
| Valid program and Makefile | [Makefile](./Makefile), `make test` |
| Group 1: constructors, one node, traversals | [RedBlackTreeTests.cpp](./RedBlackTreeTests.cpp) |
| Group 2: two/three nodes | [RedBlackTreeTests.cpp](./RedBlackTreeTests.cpp), including all four rotation cases |
| Group 3: four or more nodes | [RedBlackTreeTests.cpp](./RedBlackTreeTests.cpp), including large-tree and edge-case coverage |
| Edge cases | Empty trees, duplicates, negative values, zero, `INT_MIN`, `INT_MAX`, absent values |
| Large trees | 2,000 values in ascending, descending, and reproducibly shuffled order |
| Red-black properties | Tests check strict BST ordering, black root, no adjacent red nodes, equal black heights, size, and membership |
| Copy constructor | Shape, colors, traversals, size, independent changes to both trees, empty and large copies |
| Contains/GetMin/GetMax | Compared with `std::set` throughout the consolidated tests |
| Memory | Destructor, exception-safe recursive copying, safe copy assignment; `make valgrind` |
The provided tests and the added edge-case/large-tree coverage are consolidated
in [RedBlackTreeTests.cpp](./RedBlackTreeTests.cpp). The read-only attachments
were not edited.

[RedBlackTree.h](./RedBlackTree.h) defines the public API and private node type.
[RedBlackTree.cpp](./RedBlackTree.cpp) implements the algorithms. 
`Remove()` is
reserved for Part 2. The existing destructor is retained to release owned nodes.
AI assistance is acknowledged in source comments.




## Score: 0/0 (0.00%)


### ✗ - [0/0] - Output from `make`

- **Points**: 0 / 0

```
test.cpp:185:1: fatal error: error writing to /tmp/cc9DG21L.s: No space left on device
  185 | }
      | ^
compilation terminated.
make: *** [test] Error 1

```
```
gcc -I. -W -Wall -g -pthread msort.c -o msort
gcc -I. -W -Wall -g gen.c -o gen
g++-9 test.cpp -o test
Makefile:19: recipe for target 'test' failed

```


---

This report was generated for **kjzhou2** using **7300922af9b0bbf0c81b6beadb068bf59c262c1a** (from **March 9th 2021, 2:00:00 am**)

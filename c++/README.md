## How to

To compile the code, please use the `makefile` included in the `src/` folder.

#### Testing

```
make
```

will compile `test.cc`, creating the executable `test.x`. Here the functionalities of the implemented class are tested.

#### Benchmark

```
make benchmark
```

will compile `benchmark.cc`, creating the executable `benchmark.x` used to test the performance of the implemented class and compare it against `std::map`.

**Note**: the `makefile` provided uses a target-specific variable to set the value of the flag `D_FLAG`. This flag regulates the output of the code, so that `benchmark.x` does not print messages like _Emptying your tree_. These kind of messages are useful to test functionalities, but a cleaner output is desirable for benchmark purposes.

----

#### Documentation

The code documentation can be generated using the `Doxyfile` located in the `doc/` folder:

```
doxygen Doxyfle
```




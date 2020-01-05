## Info

* Link: http://www.cse.psu.edu/~kxm85/software/GTgraph/ 
* By default, compile with `gcc`, see [Makefile.var](Makefile.var)

## Build

```
mkdir build & cd build
cmake ..
make -j
```

## Cmake-Build

* we build `set(SPRNG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/sprng2.0-lite/lib/libsprng.a)` first, 
and then the other three executables
* `add_custom_command`, `add_custom_target`, `add_dependencies` are used to integrate the existing makefile project for the 
`sprng2.0-lite/lib/libsprng.a` 

## Usage 

see [old_readme.md](old_readme.md)

## References

* D. Chakrabarti, Y. Zhan and C. Faloutsos, R-MAT: A Recursive Model for Graph Mining, Proc. SIAM Intl. Conf. on Data Mining, 2004


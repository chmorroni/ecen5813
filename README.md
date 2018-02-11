# ECEN 5813 Projects

Christopher Morroni and Matthew Haney

### Building

```
make [TARGET] [OVERRIDES]
```

Build Targets:

* \<FILE>.o - Builds \<FILE>.o object file
* build - Builds and links all source files
* compile-all - Compiles to object files, but stops before linking
* clean - Removes all generated files
* redo - cleans then rebuilds

Overrides:

* PLATFORM - Platform for build (HOST, BBB, KL25Z)
* VERBOSE - Include extra print statements (TRUE, assumes false)

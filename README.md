# Table of Content
## Rebuilding TOC

```bash
## In Vim:
:read !markdown-toc-wrap.sh %
```


- [Table of Content](#table-of-content)
  * [Rebuilding TOC](#rebuilding-toc)
- [Intro](#intro)
  * [Build & test](#build--test)
  * [Other builds](#other-builds)
  * [Coverage build(s)](#coverage-builds)
  * [Tools version(s)](#tools-versions)
  * [Compiler warnings](#compiler-warnings)
- [Source code](#source-code)
  * [Main library](#main-library)
  * [`cmake-scripts`](#cmake-scripts)
  * [`clang-tidy`](#clang-tidy)
- [Development](#development)
  * [Directory structure](#directory-structure)
  * [Code documentation](#code-documentation)
    + [Example of code documentation](#example-of-code-documentation)
      - [Header file: `clazz.hh`](#header-file-clazzhh)
      - [Implementation file: `clazz.cc`](#implementation-file-clazzcc)
      - [Testing file: `clazz.test.cc`](#testing-file-clazztestcc)
    + [Example of using `doxygen` snippets](#example-of-using-doxygen-snippets)
  * [Fuzzing](#fuzzing)
  * [CI/CD (Jenkins)](#cicd-jenkins)

# Intro
This mini-"library's" goal is to provide an overview of C++ familiarity
during hiring / interviewing process. Some parts are over engineered on
purpose, and some are not-optimised for clarity. Originally, it was
written with `C++17` in mind and only recently was (partially) ported to
`C++26`. It contains mainly simple CS concepts, e.g.:
- graphs,
- linked lists,
- example of simple problems solved with dynamic programming (see
  `hof/dynamic_programming/dynamic_programming.test.cc`),
- etc...

## Build & test
```bash
mkdir -p build
cd build
cmake -C ../cmake-scripts/local.cmake ..
make -j
test/alltests-hof
## or
test/alltests-hof-static
```

## Other builds
```bash
## Benchmarking
## Currently (as of 2025.03.01) benchmarking code only contains
## benchmark of Mersenne Twister.
cmake -C ../cmake-scripts/local-bench.cmake ..
benchmark/bench-hof
##
##
## `clang` builds
cmake -C ../cmake-scripts/local-clang.cmake ..
##
##
## `clang-tidy` builds
## Note that `clang-tidy` builds does build tests! Its merely for
## warnings hunting. This is because there are too many false-positives
## warnings from Google Test framework.
cmake -C ../cmake-scripts/local-clang-tidy-all.cmake ..
```

## Coverage build(s)
```bash
cmake -C ../cmake-scripts/local-coverage.cmake .. && make -j
##
## Then run the following remote testing script with localhost as remote
##
## "Protip": using static build allows simple testing on remote machines,
## especially when the underlying library was changed and and hasn't
## been yet deployed to the remote machine / board / computer. :)
##
## "Protip": `remote-coverage.sh` is an in-house script that
## performs all the neccessary work to produce `LCOV` code coverage
## report in HTML.
##
remote-coverage.sh \
    --scp-only-options '-O' \
    --user "${USER}" \
    --machine localhost \
    --test-prog test/alltests-hof-static \
    --output-dir cov \
    --lcov-install-dir /usr/bin \
    --gcov-tool /usr/bin/gcov \
    --extra-lcov-remove "\
        *.fuzz.cc\
        :*.test.cc\
        :*.bench.cc\
        :*apps/*.cc\
        :*app/*.cc\
        :*examples/*.cc\
        :*example/*.cc\
        :*cross/apps/*.cc\
        :*cross/app/*.cc\
        :*cross/examples/*.cc\
        :*cross/example/*.cc\
        "
```

## Tools version(s)
```bash
$ read !g++ --version
g++ (Gentoo 14.2.1_p20241221 p7) 14.2.1 20241221
Copyright (C) 2024 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ read !clang++ --version
clang version 19.1.7
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/lib/llvm/19/bin
Configuration file: /etc/clang/x86_64-pc-linux-gnu-clang++.cfg

$ read !clang-tidy --version
LLVM (http://llvm.org/):
  LLVM version 19.1.7
  Optimized build.

$ read !cmake --version
cmake version 3.30.6
CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

## Compiler warnings
- Warnings can be found in `cxx_warnings.cmake`, there are ~300 (sic!)
  of them turned on for `gcc`/`g++`.
- For `clang` `-Weverything` is used despite official documentation not
  recommending it (sic!); some warnings are explicitly disabled, e.g.,
  `-Wno-c++98-compat`.


# Source code

## Main library
```
read !tree hof/
hof/
├── CMakeLists.txt
├── concepts
│   └── visitable
│       ├── visitable.cc
│       ├── visitable.hh
│       └── visitable.test.cc
├── dynamic_programming
│   └── dynamic_programming.test.cc
├── graph
│   ├── graph.cc
│   ├── graph.hh
│   └── graph.test.cc
├── hof-config.cmake.in
├── lambda_wrapper
│   ├── lambda_wrapper.cc
│   ├── lambda_wrapper.hh
│   └── lambda_wrapper.test.cc
└── linked_list
    ├── linked_list.cc
    ├── linked_list.hh
    └── linked_list.test.cc
7 directories, 15 files
```

## `cmake-scripts`
```
read !tree cmake-scripts/
cmake-scripts/
├── clang-tidy-all.cmake                ## deprecated (an old CMake script that uses custom clang)
├── cross.cmake                         ## deprecated (CMake script for cross compilation)
├── cross-tidy.cmake                    ## deprecated (clang-tidy for cross compilation)
├── local-bench.cmake                   ## local (non-cross) benchmak
├── local-clang.cmake                   ## local clang-based build
├── local-clang-tidy-all.cmake          ## local `clang-tidy` build
├── local-clang-tidy-with-tests.cmake   ## local `clang-tidy` build with tests
├── local.cmake                         ## local build -- use this to run natively
├── local-coverage.cmake                ## local coverage build
├── local.g++13.2.0.cmake               ## local build with forced GCC 13.2.0 -- deprecated
└── local-tidy.cmake                    ## local `clang-tidy` build -- deprecated
1 directory, 10 files
```

## `clang-tidy`
```
read !tree clang-tidy/
clang-tidy/
├── all.yaml                ## used for local `clang-tidy` build
├── fix-headers-only.yaml   ## unused!
└── tests.yaml              ## used for local `clang-tidy` build with tests
1 directory, 3 files
```


# Development

## Directory structure
- `benchmark` - benchmarking code (not much at this point).
- `clang-tidy` - `clang-tidy`'s configuration, see, for example,
  `clang-tidy/all.yaml`.
- `cmake-modules` - `FindXXX.cmake` scripts.
- `cmake-script` - cmake scripts with pre-defined build profiles.
- `cross` - libraries and applications that makes sense to cross-compile
  and run only on target machines / architectures, typically due to the
  using some "exotic" hardware, e.g., 5G-ready RF front end(s);
  (definitely not in this mini-project :)).
  - `cross/apps` - applications to be run on the target architecture.
  - `cross/examples` - examples/standalone tests.
- `git-hooks` - contains only one Git hook that can be used to check
  whether Eclipse's configuration files has been copied to the `ide-
  configuration/${USER}` before making a commit. It does not force
  one to commit those files in current or future commits; it just
  ensures that `ide-configuration/${USER}` **always** contains the
  most recent files.
- `ide-configuration` - configuration of one's IDE, grouped by the user
  name or tag. Because you **can** store IDE configuration in CVS as
  long as it is separated for each user.
- `include-wrappers` - useful wrappers for external include files.
   ```
   include-wrappers/
   ├── gflags-wrapper.hh
   └── gtest-wrapper.hh

   1 directory, 2 files

- `hof` - main "library".
  - Ideally, each module (**not necessarily** `class`) should be placed
    in a separate directory together with `\*.test.cc` file that is
    picked up automatically by the testing `CMake` script(s) (see
    `hof/CMakeLists.txt` or `test/CMakeLists.txt`).
  - Here, `file(GLOB_RECURSE ...)` is used only for convenience.
    Typically, each source code file should be listed manually to ensure
    automatic rebuilds in the downstream.
- `scripts` - scripts used during build.
- `test` - self explanatory - main unit tests directory.


## Code documentation
- Code is documented using `doxygen` tags / comments / snippets.
- Why `doxygen` snippets?
- The answer is simple. Typically, code examples tend to de-sync from
  the implementation. Using exact code from the tests ensures that:
  - the code in the example / snippets compiles, and
  - does what it supposed to.



### Example of code documentation

#### Header file: `clazz.hh`

```cpp
/** @brief Brief description
 *
 *
 * Usage example:
 * @snippet{lineno} clazz.test.cc doxygen_example_tag
 *
 */
class Clazz {
public:
    /**
     * @brief Short function description
     *
     * A more detailed one...
     *
     */
    static int foo(
    /**
     * Long parameter description
     * Multiple lines are merged into one in HTML documentation.
     * As of `doxygen` 1.8 markdown tags, like `code` **bold** does not
     * work in parameter description, so use <b>for bold</b>
     * or <tt>for fixed width font</tt>
     */
     std::shared<std::tuple<int, char, std::string>> const* long_param,
     int short_param /**< Short param description */,
     char x
};
```

#### Implementation file: `clazz.cc`
```cpp
int Clazz::foo(/* ... */) {
    // Implementation...
    return 42;
}
```

#### Testing file: `clazz.test.cc`
```cpp
//! [doxygen_example_tag]
// Some example of how to use an instance of Clazz...
//! [doxygen_example_tag]
```

### Example of using `doxygen` snippets
In documentation file add reference to the snippet:
```cpp
/** @brief ...
 *
 * @snippet{lineno} file.test.cc doxygen_snippet_tag
 *
 */
```

In testing file (`file.test.cc`) add:
```cpp
//! [doxygen_snippet_tag]
// Snippet content
TEST_F(module_name_in_docs_compiled_test, fixture_self_test) {
    Clazz clazz = std::make_shared<Clazz>(10, "Hello");
    // ...
}
//! [doxygen_snippet_tag]
```

## Fuzzing
- TBD...

## CI/CD (Jenkins)
- TBD...

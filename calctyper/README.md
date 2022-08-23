# CalcTyper

Font data generator for libcalctype.

## Table of contents

* [CalcTyper](#calctyper)
    * [Table of contents](#table-of-contents)
    * [Requirements](#requirements)
    * [Usage](#usage)
    * [Building](#building)
        * [Additional requirements](#additional-requirements)
        * [Standalone](#standalone)
        * [VS Code](#vs-code)
    * [Installation](#installation)
        * [Additional requirements](#additional-requirements-1)
        * [Uninstallation](#uninstallation)
    * [Code structure](#code-structure)
    * [Debugging](#debugging)
        * [Additional requirements](#additional-requirements-2)
        * [Standalone](#standalone-1)
        * [VS Code](#vs-code-1)
    * [Internationalization](#internationalization)
        * [Generating the POT template file](#generating-the-pot-template-file)
        * [Generating PO files](#generating-po-files)
        * [Updating existing PO files](#updating-existing-po-files)
        * [Generating MO files](#generating-mo-files)

## Requirements

* `boost` >= 1.79.0
* `gettext`

## Usage

See output of:

```shell
calctyper --help
```

## Building

### Additional requirements

* C++17-compatible compiler with POSIX-compliant standard library (`clang` >= 5)
* `cmake` >= 3.10

### Standalone

Targets:
* Debug:
    ```shell
    (mkdir -p build/debug && cd build/debug && cmake ../.. -DCMAKE_BUILD_TYPE=Debug && make)
    ```
    * Output: `build/debug/calctyper`
* Release:
    ```shell
    (mkdir -p build/release && cd build/release && cmake ../.. && make)
    ```
    * Output: `build/release/calctyper`

### VS Code

Targets:
* Debug:
    * Run Build Task (`(Debug) Build CalcTyper`)
        * Default keybind: `shift + ctrl/cmd + b`
        * Output: `build/debug/calctyper`
* Release:
    * Run task `(Release) Build CalcTyper`
        * Output: `build/release/calctyper`

## Installation

Ensure you have built the program for the release target.

### Additional requirements

* `sudo`


```shell
(cd build/release && sudo make install)
```

### Uninstallation

```shell
(cd build/release && sudo make uninstall)
```

## Code structure

* Written in C++
* Built using [CMake](https://cmake.org)
* Source code is located in `src/`
* C++ source files have the suffix `.cc`
* C++ header files have the suffix `.h`
* Indented with hard tabs of 8 characters in width
* Lines are no longer than 80 characters, unless readability is affected
* Uses [Doxygen](https://doxygen.nl/index.html) comments

## Debugging

Ensure you have built the program for the debug target.

### Additional requirements

* `gdb`

### Standalone

```shell
gdb build/debug/calctyper
```

### VS Code

Requires the [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
extension from the VS Code Marketplace.

* Open a source file
    * Run the default launch task (`(Debug) (gdb) Launch CalcTyper`)
        * Default keybind: `F5`

## Internationalization

Ensure you have built the program for the release target.

### Generating the POT template file

```shell
(cd build/release && make pot-update)
```

This will generate `locale/calctyper.pot`.

### Generating PO files

```shell
msginit -i locale/gelcube.pot -o locale/<LANG>.po -l <LOCALE>
```

Edit `locale/<LANG>.po` as required.

### Updating existing PO files

```shell
(cd build/release && make pot-merge)
```

### Generating MO files

```shell
(cd build/release && make po-compile)
```

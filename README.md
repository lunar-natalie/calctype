# CalcType

**Note: This repo is currently incomplete.**

Typeface and imaging library and tools for color graphic calculators, using
sub-pixel rendering concepts.

Originally created by [tswilliamson](https://github.com/tswilliamson)
([repo](https://github.com/tswilliamson/calctype)). The original project was
forked and extended by [Peter Marheine](https://github.com/tari)
([repo](https://github.com/tari/calctype)). This repo is a re-organised
amalgamation of both, with the original tools ported to a C++ CLI.

## Table of contents

* [CalcType](#calctype)
    * [Table of contents](#table-of-contents)
    * [Documentation](#documentation)
    * [Building](#building)
        * [Requirements](#requirements)
        * [Configuration](#configuration)
        * [Standalone](#standalone)
        * [VS Code](#vs-code)
    * [Installation](#installation)
        * [Additional requirements](#additional-requirements)
        * [Configuration](#configuration-1)
        * [Install](#install)
            * [Standalone](#standalone-1)
            * [VS Code](#vs-code-1)
        * [Uninstall](#uninstall)
            * [Standalone](#standalone-2)
            * [VS Code](#vs-code-2)
    * [Other build commands](#other-build-commands)
        * [Clean](#clean)
            * [Standalone](#standalone-3)
            * [VS Code](#vs-code-3)
    * [Code structure](#code-structure)
    * [Version control](#version-control)
    * [License](#license)

## Documentation

* POSIX shell commands to be run as user are denoted by shell code blocks
* Text to be substituted in shell commands is capitalised and encapsulated in
angle brackets
* 'Visual Studio Code' and 'Code - OSS' are abbreviated to VS Code

## Building

### Requirements

* [`libfxcg`](https://github.com/lunar-natalie/libfxcg)
* `make`
* `sh3eb-elf-binutils`
* `sh3eb-elf-gcc` with C17 support

### Configuration

* Add the following to `.env.mk`:

    ```Makefile
    FXCGSDK=<PATH_TO_SDK>
    ```

### Standalone

```Shell
make
```
* Output: `libcalctype.a`

### VS Code

* Run Build Task (`Build library`)
    * Default keybind: `shift + ctrl/cmd + b`
    * Output: `libcalctype.a`

## Installation

### Additional requirements

* `coreutils`
* `sudo`

### Configuration

* Add the following to `.env.mk`:

    ```Makefile
    INSTALL_PREFIX=<PATH>
    ```

* Common install prefixes include `/usr` and `/usr/local`

### Install

#### Standalone

```Shell
sudo make install
```

#### VS Code

* Run Task `Install library`

### Uninstall

#### Standalone

```Shell
sudo make uninstall
```

#### VS Code

* Run Task `Uninstall library`

## Other build commands

### Clean

#### Standalone

```Shell
make clean
```

#### VS Code

* Run Task `Clean build environment`

## Code structure

* Library written in C
* Tools written in C++
* Built with `make`
* Source code is located in `src/`
* Indented with hard tabs of 8 characters in width
* Lines are no longer than 80 characters, unless readability is affected
* Uses [Doxygen](https://doxygen.nl/index.html) comments

## Version control

Commit messages should follow [this convention](https://www.conventionalcommits.org/)
for readability, and for any tools we may use in the future which depend on it.

## License

Copyright (c) 2022 The CalcType Authors.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.

Written by tswilliamson, Peter Marheine, and Natalie Wiggins.

See `LICENSE` and `AUTHORS` for more information.

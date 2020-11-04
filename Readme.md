[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/ezalos/malloc">
    <img src="https://upload.wikimedia.org/wikipedia/commons/8/8d/42_Logo.svg" alt="Logo" width="200" height="200">
  </a>

  <h1 align="center">malloc<br />realloc<br />calloc<br />free</h1>

  <br />

  <p align="center">
    A C dynamic memory allocation implementation from @ezalos, @rkirszba and @arobion
    <br />
    <br />
    <br />
    ·
    <a href="https://github.com/ezalos/malloc/issues">Report Bug</a>
    ·
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Architecture](#architecture)
* [Resources](#resources)
* [License](#license)



<!-- ABOUT THE PROJECT -->
## About The Project

As part of our learning at 42 we decided to re-implement malloc, realloc, calloc and free.

```c
void	*malloc(size_t size);
```
```c
void	*realloc(void *ptr, size_t size);
```
```c
void	*calloc(size_t count, size_t size);
```
```c
void	free(void *ptr);
```

[:book:Subject:book:](Subject/fr.subject.pdf)

 C dynamic memory allocation refers to performing manual memory management for dynamic memory allocation in the C programming language via a group of functions in the C standard library, namely malloc, realloc, calloc and free.

Here's why we are proud of our work:
* :rocket: This implementation focus on having good performances in speed of execution.

* :computer: Our implementation is multi-threading compatible!

* :seedling: We have very little depedencies, almost everything has been recoded from scratch. Here's the full list of the function we didn't coded ourselves in this project:
  * mmap
  * munmap
  * write
  * And, for the multi-threading compatibility, the functions of lib pthread


<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

For this project you need to have installed on your computer
* `git`
* `gcc`
* `make`

### Installation

1. Clone the repo
	```sh
	git clone https://github.com/ezalos/malloc.git
	cd malloc
	```
2. Build the dynamic library
	```sh
	make
	```
3. Run the testings
	```sh
	make tests
	```

<!-- USAGE EXAMPLES -->
## Usage

As this program create a dynamic library, we need to ask the Operating System to use our work instead of the implementation in libc.
For doing so, we give instructions during the loading of the program.

* ### Linux:
	```sh
	LD_PRELOAD="libft_malloc.so" HUGETLB_MORECORE=yes your_program.out
	```
* ### MacOS:
  ```sh
	DYLD_LIBRARY_PATH=. DYLD_INSERT_LIBRARIES="libft_malloc.so" DYLD_FORCE_FLAT_NAMESPACE=1 your_program.out
	```
	With the last security update on MacOS, you might need to follow [this](https://osxdaily.com/2015/10/05/disable-rootless-system-integrity-protection-mac-os-x/) setup.


<!-- ARCHITECTURE -->
## Architecture

See the [open issues](https://github.com/ezalos/malloc/issues) for a list of proposed features (and known issues).


<!-- RESOURCES -->
## Resources
* man pages
  * mmap and munmap: [:link:](https://man7.org/linux/man-pages/man2/mmap.2.html)
  * malloc, realloc, calloc and free: [:link:](https://man7.org/linux/man-pages/man3/malloc.3.html)
* A detailled architecture of malloc libc: [:link:](https://sourceware.org/glibc/wiki/MallocInternals)
*


<!-- LICENSE -->
## License

Distributed under the [`WTFPL LICENSE`![](https://upload.wikimedia.org/wikipedia/commons/thumb/0/05/WTFPL_logo.svg/140px-WTFPL_logo.svg.png =20x20)](https://en.wikipedia.org/wiki/WTFPL). See [`LICENSE`](LICENSE) for more information.



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/ezalos/malloc.svg?style=flat-square
[contributors-url]: https://github.com/ezalos/malloc/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/ezalos/malloc.svg?style=flat-square
[forks-url]: https://github.com/ezalos/malloc/network/members
[stars-shield]: https://img.shields.io/github/stars/ezalos/malloc.svg?style=flat-square
[stars-url]: https://github.com/ezalos/malloc/stargazers
[issues-shield]: https://img.shields.io/github/issues/ezalos/malloc.svg?style=flat-square
[issues-url]: https://github.com/ezalos/malloc/issues
[license-shield]: https://img.shields.io/github/license/ezalos/malloc.svg?style=flat-square
[license-url]: https://github.com/ezalos/malloc/blob/master/LICENSE

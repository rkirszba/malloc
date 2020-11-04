[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

![](assets/malloc.gif)

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
  * [Structures](#structures)
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

[:book: Subject :book:](Subject/fr.subject.pdf)

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

### Low level Structures
There is different levels of memory used in this project, from the smallest unit, to the largest:
 * #### allocation:

   It's the memory delivered to the user.

   Each allocation given by malloc is preceded by an header:
   ```c
   typedef	struct				s_alloc_header
   {
    /*custom structure for a node of red black tree*/
   	t_rbt					rbt;
	/*size of the memory following this header*/
   	uint32_t				size;
	/*size of the preceding memory*/
   	uint32_t				size_prev;
	/*see below*/
   	uint8_t					flags;
   }							t_alloc_header;
   ```
   This `flags` variable contains multiple informations encoded:
    * Position
	  * Is it the first allocation of zone
	  * Is it the last allocation of zone
    * Availability
	  * Is this allocation available to use
    * Zone type
	  * Is this allocation in a large zone
	  * Is this allocation in a small zone
	  * Is this allocation in a tiny zone

   Each allocation is followed by `size` octets

 * #### Zones:

   Zones are large chunks of continuous memory delivered by mmap.
   Inside a zone, we find a succession allocation header, followed by the corresponding `size` of dedicated memory.

   Each zone is preceded by an header:
   ```c
   typedef	struct				s_zone_header
   {
   	struct s_zone			*next_zone;
   	struct s_zone			*prev_zone;
   	size_t					size;
   }							t_zone_header;
   ```
   Zones are linked together by mem_type inside a double linked list.

   Here is a representation of a zone:

  <span style="color:blue">[header_zone]</span><span style="color:yellow">[header_alloc]</span><span style="color:red">[xxxxxxxxxxxxxxxxxxxxxxx]</span><span style="color:yellow">[header_alloc]</span><span style="color:red">[xxxxxxxxx<br />
  xxxxxxxxxxxxxxxxxxxx]</span><span style="color:yellow">[header_alloc]</span><span style="color:green">[oooooooooooooooooooooooooooooooooooo<br />
  ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo<br />
  ooooooooooooooooooooo]</span><span style="color:yellow">[header_alloc]</span><span style="color:red">[xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<br />
  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<br />
  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<br />
  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<br />
  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<br />
  xxxxxxx]</span><span style="color:yellow">[header_alloc]</span><span style="color:green">[ooooooooooooooooooooooooooooooooooooooooooooooooo<br />
  ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo<br />
  ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo<br />
  ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo<br />
  ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo<br />
  ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo<br />
  ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo<br />
  ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo<br />
  ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo<br />
  oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo]</span>

 * Legend:
   * with `t_zone_header` -> <span style="color:blue">[header_zone]</span>
   * with `t_alloc_header` -> <span style="color:yellow">[header_alloc]</span>
   * with used memory -> <span style="color:red">[x]</span>
   * with free memory -> <span style="color:green">[o]</span>

 * #### mem_type:

 mem_types are a collection of zones, which are grouped inside a double linked list.

 We make the difference between three types of mem_types, depending of the size of allocation asked by user.

     * **Tiny**

    	It's allocations sizes ranges from 0 octets to 1024 octets.

		They have a resolution of 16 octets.
		resolution means that we complete them to be a multiple of 16, as in the libc implementation of malloc.

     * **Small**

	   It's allocations sizes ranges from 1024 octets to 16MB.

	   They have a resolution of 512 octets.


     * **Large**

	   It's allocations sizes ranges from 0 octets to 1024 octets.

	   They have a resolution of 4096 octets.





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

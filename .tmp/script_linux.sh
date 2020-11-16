#!/bin/sh
# export DYLD_LIBRARY_PATH=. DYLD_INSERT_LIBRARIES="libft_malloc.so" DYLD_FORCE_FLAT_NAMESPACE=1
export LD_PRELOAD="./libft_malloc.so"

export HUGETLB_MORECORE=yes

$@

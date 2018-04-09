# Project 3 Statistics

#### KL25Z Cycles per Memory Operation (averaged over 100 tests)
Function       | 10 bytes | 100 bytes | 1000 bytes | 5000 bytes
-------------- | -------- | --------- | ---------- | ----------
memmove        | 129      | 863       | 8063       | 40063
my_memmove     | 383      | 2723      | 26123      | 130123
my_memmove_opt | 157      | 967       | 9067       | 45067
memmove_dma    | 1358     | 1538      | 3338       | 11338
memset         | 104      | 180       | 864        | 3864
my_memset      | 283      | 2263      | 22063      | 110063
my_memset_opt  | 103      | 733       | 7033       | 35033
memset_dma     | 1353     | 1533      | 3333       | 11333

#### BBB Cycles per Memory Operation (averaged over 100 tests)
Function       | 10 bytes | 100 bytes | 1000 bytes | 5000 bytes
-------------- | -------- | --------- | ---------- | ----------
memmove        | 3        | 3         | 3          | 6
my_memmove     | 3        | 5         | 20         | 89
my_memmove_opt | 3        | 3         | 7          | 23
memset         | 3        | 3         | 3          | 4
my_memset      | 4        | 4         | 16         | 68
my_memset_opt  | 3        | 3         | 3          | 6

---

The above cycle counts are all using 8-bit transfers, which is not necessarily the fastest method for these transfers.
With a 32-bit transfer size, the measured cycle counts could decrease by up to a factor of 4.

The DMA memmove is significantly faster than the other options at or above 1000 bytes. Below that, the DMA has too much
overhead to top the other functions, except the un-optimized version of my_memmove, where the transition point is 100 bytes.
The DMA memset, however, only comes out ahead of our memset functions, and not the standard library.

On the BeagleBone, the O3-optimized version of my_memset keeps pace with the standard library memset, but the optimized version of
my_memmove does not. Both are faster than their non-optimized counterparts, especially for larger blocks. The cycle counts
here are quite small, though, which prevents us from comparing further.

---

KL25Z Stack Utilization = 150 words

# Project 3 Statistics

#### KL25Z Cycles per Memory Operation (averaged over 100 tests)
Function       | 10 bytes | 100 bytes | 1000 bytes | 5000 bytes
-------------- | -------- | --------- | ---------- | ----------
memmove        | 129      | 863       | 8063       | 40063
my_memmove     | 383      | 2723      | 26123      | 130123
my_memmove_opt | 157      | 967       | 9067       | 45067
memmove_dma    | 1358     | 1538      | 3338       | 11338
               |          |           |            | 
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
               |          |           |            | 
memset         | 3        | 3         | 3          | 4
my_memset      | 4        | 4         | 16         | 68
my_memset_opt  | 3        | 3         | 3          | 6

---

KL25Z Stack Utilization = 150 words

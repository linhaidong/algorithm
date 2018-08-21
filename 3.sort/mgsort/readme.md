1.基本思想
归并排序的基本此略是归并，即把两个有序序列合并为一个大的有序序列。
为了构造出有序序列，需要先递归到序列中只有一个元素，然后在递归回归的时候进行归并。

2.调试过程：
Breakpoint 1, merge (array=0x7fffffffdd50, low=0, mid=0, higt=1) at mgsort.c:13
13	    int num = higt - low + 1;
(gdb) p *array@7
$1 = {3, 6, 4, 9, 7, 5, 8}
(gdb) c
Continuing.

Breakpoint 2, merge (array=0x7fffffffdd50, low=0, mid=0, higt=1) at mgsort.c:32
32	    return 0;
(gdb) p *array@7
$2 = {6, 3, 4, 9, 7, 5, 8}
(gdb) c
Continuing.

Breakpoint 1, merge (array=0x7fffffffdd50, low=2, mid=2, higt=3) at mgsort.c:13
13	    int num = higt - low + 1;
(gdb) p *array@7
$3 = {6, 3, 4, 9, 7, 5, 8}
(gdb) c
Continuing.

Breakpoint 2, merge (array=0x7fffffffdd50, low=2, mid=2, higt=3) at mgsort.c:32
32	    return 0;
(gdb) p *array@7
$4 = {6, 3, 9, 4, 7, 5, 8}
(gdb) c
Continuing.

Breakpoint 1, merge (array=0x7fffffffdd50, low=0, mid=1, higt=3) at mgsort.c:13
13	    int num = higt - low + 1;
(gdb) p *array@7
$5 = {6, 3, 9, 4, 7, 5, 8}
(gdb) c
Continuing.

Breakpoint 2, merge (array=0x7fffffffdd50, low=0, mid=1, higt=3) at mgsort.c:32
32	    return 0;
(gdb) p *array@7
$6 = {9, 6, 4, 3, 7, 5, 8}
(gdb) c
Continuing.

Breakpoint 1, merge (array=0x7fffffffdd50, low=4, mid=4, higt=5) at mgsort.c:13
13	    int num = higt - low + 1;
(gdb) p *array@7
$7 = {9, 6, 4, 3, 7, 5, 8}
(gdb) c
Continuing.

Breakpoint 2, merge (array=0x7fffffffdd50, low=4, mid=4, higt=5) at mgsort.c:32
32	    return 0;
(gdb) p *array@7
$8 = {9, 6, 4, 3, 7, 5, 8}
(gdb) c
Continuing.

Breakpoint 1, merge (array=0x7fffffffdd50, low=4, mid=5, higt=6) at mgsort.c:13
13	    int num = higt - low + 1;
(gdb) p *array@7
$9 = {9, 6, 4, 3, 7, 5, 8}
(gdb) c
Continuing.

Breakpoint 2, merge (array=0x7fffffffdd50, low=4, mid=5, higt=6) at mgsort.c:32
32	    return 0;
(gdb) p *array@7
$10 = {9, 6, 4, 3, 8, 7, 5}
(gdb) c
Continuing.

Breakpoint 1, merge (array=0x7fffffffdd50, low=0, mid=3, higt=6) at mgsort.c:13
13	    int num = higt - low + 1;
(gdb) p *array@7
$11 = {9, 6, 4, 3, 8, 7, 5}
(gdb) c
Continuing.

Breakpoint 2, merge (array=0x7fffffffdd50, low=0, mid=3, higt=6) at mgsort.c:32
32	    return 0;
(gdb) p *array@7
$12 = {9, 8, 7, 6, 5, 4, 3}

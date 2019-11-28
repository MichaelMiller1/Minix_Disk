Fall 19 (1) CIS 340 Systems Programming Section 1:  Project 4

group11:	Miller	 Michael		m.miller89@vikes.csuohio.edu
		Trem	 Bryce			b.trem@vikes.csuohio.edu

Contribution: %50/%50

Compile Instructions:  
1.  In terminal, navigate to assignment folder: "group11".
3.  Type './minix' to run.

Sample Outputs:

Minix Command: help
The available minix commands are:
    help                    - show the commands list.
    minimount argument      - mount a local minix disk
    miniumount              - umount the mounted minix disk
    showsuper               - to list the information of the super block
    traverse [-l]           - list the content in the root directory. Optional -l flag gives a long listing of the root directory.
    showzone [zone number]  - show the ASCII content of the specified zone number
    showfile                - show the content of the target file in the hex dump

Minix Command: showsuper
Number of inodes: 3424
Number of zones: 10240
Number of imap_blocks: 1
Number of zmap_blocks: 2
First data zone: 112
Log zone size: 0
Max size: 268966912
Magic: 5007
State: 0
Zones: 0

Minix Command: traverse
A.cla
Aloop1.cla
Aloop1.jav
Aloop2.cla
Aloop2.jav
Aloop3.cla
Aloop3.jav
B.cla
Condit.cla
Condit.jav
D.cla
Demo.cla
Demo.jav
dir1
PolyTest.cla
PolyTest.jav
some.cla
some.java

Minix Command: traverse -l
-rw-rw-r--      1000    670     Sep 20 2012     A.cla
-rw-r--r--      1000    763     Dec 14 2010     Aloop1.cla
-rw-r--r--      1000    333     Dec 14 2010     Aloop1.jav
-rw-r--r--      1000    786     Dec 14 2010     Aloop2.cla
-rw-r--r--      1000    404     Dec 14 2010     Aloop2.jav
-rw-r--r--      1000    786     Dec 14 2010     Aloop3.cla
-rw-r--r--      1000    408     Dec 14 2010     Aloop3.jav
-rw-rw-r--      1000    358     Sep 20 2012     B.cla
-rw-r--r--      1000    1067    Dec 14 2010     Condit.cla
-rw-r--r--      1000    444     Dec 14 2010     Condit.jav
-rw-rw-r--      1000    508     Sep 20 2012     D.cla
-rw-r--r--      1000    967     Dec 14 2010     Demo.cla
-rw-r--r--      1000    648     Dec 14 2010     Demo.jav
drwx------      1000    128     Oct 27 2014     dir1
-rw-rw-r--      1000    630     Sep 20 2012     PolyTest.cla
-rw-rw-r--      1000    1063    Sep 20 2012     PolyTest.jav
-rw-r--r--      1000    226     Dec 14 2010     some.cla
-rw-r--r--      1000    278     Dec 14 2010     some.java

Minix Command: showzone 112
        0 1 2 3 4 5 6 7 8 9 a b c d e f
0           .
10
20          . .
30
40          A . c l a
50
60          A l o o p 1 . c l a
70
80          A l o o p 1 . j a v
90
a0          A l o o p 2 . c l a
b0
c0          A l o o p 2 . j a v
d0
e0          A l o o p 3 . c l a
f0
100         A l o o p 3 . j a v
110
120         B . c l a
130
140         C o n d i t . c l a
150
160         C o n d i t . j a v
170
180         D . c l a
190
1a0         D e m o . c l a
1b0
1c0         D e m o . j a v
1d0
1e0         d i r 1
1f0
200         P o l y T e s t . c l a
210
220         P o l y T e s t . j a v
230
240         s o m e . c l a
250
260         s o m e . j a v a
270
280
290
2a0
2b0
2c0
2d0
2e0
2f0
300
310
320
330
340
350
360
370
380
390
3a0
3b0
3c0
3d0
3e0
3f0

Minix Command: showfile Aloop1.jav
File name: Aloop1.jav
 70  75  62  6c  69  63  20  63  6c  61  73  73  20  41  6c  6f
 6f  70  31  20  7b  0a  20  20  20  20  70  75  62  6c  69  63
 20  73  74  61  74  69  63  20  76  6f  69  64  20  6d  61  69
 6e  28  53  74  72  69  6e  67  5b  5d  20  61  72  67  73  29
 20  7b  0a  09  0a  09  53  74  72  69  6e  67  5b  5d  20  72
 61  6e  6b  20  3d  20  7b  22  44  45  55  43  45  22  2c  20
 22  54  48  52  45  45  22  2c  20  22  46  4f  55  52  22  2c
 20  22  46  49  56  45  22  2c  20  22  53  49  58  22  2c  20
 22  53  45  56  45  4e  22  2c  0a  09  09  09  20  22  45  49
 47  48  54  22  2c  20  22  4e  49  4e  45  22  2c  20  22  54
 45  4e  22  2c  20  22  4a  41  43  4b  22  2c  20  22  51  55
 45  45  4e  22  2c  20  22  4b  49  4e  47  22  2c  20  22  41
 43  45  22  7d  3b  0a  09  0a  09  69  6e  74  20  69  20  3d
 20  30  3b  0a  09  69  6e  74  20  63  6f  75  6e  74  65  72
 20  3d  20  30  3b  0a  09  77  68  69  6c  65  20  28  21  72
 61  6e  6b  5b  69  5d  2e  65  71  75  61  6c  73  28  22  53
 49  58  22  29  29  20  7b  0a  09  20  20  20  20  69  2b  2b
 3b  0a  09  20  20  20  20  63  6f  75  6e  74  65  72  2b  2b
 3b  0a  09  7d  0a  09  53  79  73  74  65  6d  2e  6f  75  74
 2e  70  72  69  6e  74  6c  6e  28  63  6f  75  6e  74  65  72
 29  3b  0a  0a  20  20  20  20  7d  0a  7d  0a  0a  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
 00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00

Current Errors:
N/A
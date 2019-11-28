Develop a Minix Disk program that allows users to access a Minix disk locally mounted on a computer. You are expected to use C programming language. In your program, all file I/O related operations should use the system calls discussed in our lectures, including open(), read(), write(), lseek(), close(), and you should not use those library functions like fopen() and fread(). Your implementation must work on Linux machine.
                      
Required Modules:                
Client Environment (a minix console): the console (interface) allows users to access the minix disk by using the following commands:                      
help: show the commands supported in the minix console.                      
minimount argument: mount a local minix disk, where "argument" is a iminix image file, e.g., imagefile.img.              
miniumount: umount the mounted minix disk.             
showsuper: to list the information of the super block. For example:                     
minix: showsuper                 
                             
number of inodes:         3424                                                   
number of zones:          10240                 
number of imap_blocks: 	    1                     
number of zmap_blocks: 	    2                     
first data zone:    	112                   
log zone size: 	    	0                     
max size: 		    268966912   
magic: 			    5007    
state: 		    	0   
zones: 		    	0   
traverse [-l]: list the content in the root directory. Note that you don't have to show the entries of "." and "..". For example:
minix: traverse   
    
    
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
    
    
When switch -l is turned on (long list), all detailed information is shown, including the file type, 9 permission bits, user ID, file size (in bytes), last modified date (with year), and the file/path name. For example:   
minix: traverse -l    
    
-rw-rw-r-- 1000 670 Sep 20  2012 A.cla    
-rw-r--r-- 1000 763 Dec 14  2010 Aloop1.cla   
-rw-r--r-- 1000 333 Dec 14  2010 Aloop1.jav   
-rw-r--r-- 1000 786 Dec 14  2010 Aloop2.cla   
-rw-r--r-- 1000 404 Dec 14  2010 Aloop2.jav   
-rw-r--r-- 1000 786 Dec 14  2010 Aloop3.cla   
-rw-r--r-- 1000 408 Dec 14  2010 Aloop3.jav   
-rw-rw-r-- 1000 358 Sep 20  2012 B.cla    
-rw-r--r-- 1000 1067 Dec 14  2010 Condit.cla    
-rw-r--r-- 1000 444 Dec 14  2010 Condit.jav   
-rw-rw-r-- 1000 508 Sep 20  2012 D.cla    
-rw-r--r-- 1000 967 Dec 14  2010 Demo.cla   
-rw-r--r-- 1000 648 Dec 14  2010 Demo.jav   
drwx------ 1000 128 Oct 27  2014 dir1   
-rw-rw-r-- 1000 630 Sep 20  2012 PolyTest.cla   
-rw-rw-r-- 1000 1063 Sep 20  2012 PolyTest.jav    
-rw-r--r-- 1000 226 Dec 14  2010 some.cla   
-rw-r--r-- 1000 278 Dec 14  2010 some.java    
    
    
    
        
Hint: the mode field (a 2-byte unsigned integer) in inode struct uses the following flags:    
    
           S_IFMT     0170000   bit mask for the file type bit fields       
           S_IFSOCK   0140000   socket        
           S_IFLNK    0120000   symbolic link       
           S_IFREG    0100000   regular file        
           S_IFBLK    0060000   block device        
           S_IFDIR    0040000   directory       
           S_IFCHR    0020000   character device        
           S_IFIFO    0010000   FIFO        
           S_ISUID    0004000   set-user-ID bit      
           S_ISGID    0002000   set-group-ID bit (see below)        
           S_ISVTX    0001000   sticky bit (see below)        
           S_IRWXU    00700     mask for file owner permissions   
           S_IRUSR    00400     owner has read permission   
           S_IWUSR    00200     owner has write permission    
           S_IXUSR    00100     owner has execute permission    
           S_IRWXG    00070     mask for group permissions    
           S_IRGRP    00040     group has read permission   
           S_IWGRP    00020     group has write permission    
           S_IXGRP    00010     group has execute permission    
           S_IRWXO    00007     mask for permissions for others  (not in group)   
           S_IROTH    00004     others have read permission   
           S_IWOTH    00002     others have write permission    
           S_IXOTH    00001     others have execute permission  
              
[showzone [zone number]: show the ASCII content of the specified zone number (1024 bytes for each zone). If the value is not ASCII, just print the spaces instead. Tip: the library function isprint() can be used to determine whether the given byte is an ASCII. Obviously, this command is actually a very useful debugging tool. For example:    
    
minix: showzone 112   
    
        
showfile [filename]: show the content of the target file (in the hex dump) located in the root directory. You may assume the file size is less than 7 KB. If the filename cannot be found, appropriate error information should be printed on the screen and the program should be ready for the next command.    
    
minix: showfile Aloop1.jav    
    

      70   75   62   6c   69   63   20   63   6c   61   73   73   20   41   6c   6f    
      6f   70   31   20   7b    a   20   20   20   20   70   75   62   6c   69   63    
      20   73   74   61   74   69   63   20   76   6f   69   64   20   6d   61   69    
      6e   28   53   74   72   69   6e   67   5b   5d   20   61   72   67   73   29    
      20   7b    a    9    a    9   53   74   72   69   6e   67   5b   5d   20   72    
   61   6e   6b   20   3d   20   7b   22   44   45   55   43   45   22   2c   20    
   22   54   48   52   45   45   22   2c   20   22   46   4f   55   52   22   2c    
   20   22   46   49   56   45   22   2c   20   22   53   49   58   22   2c   20    
   22   53   45   56   45   4e   22   2c    a    9    9    9   20   22   45   49
   47   48   54   22   2c   20   22   4e   49   4e   45   22   2c   20   22   54
   45   4e   22   2c   20   22   4a   41   43   4b   22   2c   20   22   51   55
   45   45   4e   22   2c   20   22   4b   49   4e   47   22   2c   20   22   41
   43   45   22   7d   3b    a    9    a    9   69   6e   74   20   69   20   3d
   20   30   3b    a    9   69   6e   74   20   63   6f   75   6e   74   65   72
   20   3d   20   30   3b    a    9   77   68   69   6c   65   20   28   21   72
   61   6e   6b   5b   69   5d   2e   65   71   75   61   6c   73   28   22   53
   49   58   22   29   29   20   7b    a    9   20   20   20   20   69   2b   2b
   3b    a    9   20   20   20   20   63   6f   75   6e   74   65   72   2b   2b
   3b    a    9   7d    a    9   53   79   73   74   65   6d   2e   6f   75   74
   2e   70   72   69   6e   74   6c   6e   28   63   6f   75   6e   74   65   72
   29   3b    a    a   20   20   20   20   7d    a   7d    a    a    0    0    0
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

quit: quit the minix shell.
Provide a Makefile so make command would produce the executable.

For your convenience, we provide an example minix image:  imagefile.img . 

The Linux "ls -l" on this mounted image produces the following. Your Minix program would output the similar information with the exception of username, name, etc.
-rw-r--r-- 1 mike mike 1154 Nov  3 13:07 con_new.tex
etc.

You may also create your own minix image by following instructions (on your own computers only):
Create an empty minix image: (here 1.44MB)
 $ dd bs=1024 count=1440 if=/dev/zero of=./imagefile.img
Format it:
 $ mkfs.minix ./imagefile.img 

Once an image is ready, you can simply open the image file in your program to access the minix disk:
 $ sudo mkdir /media/minix/ 
 $ sudo mount ./imagefile.img /media/minix/

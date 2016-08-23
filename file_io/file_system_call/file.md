文件描述符
====

对内核而言，所有打开文件都由文件描述符引用。文件描述符是一个非负整数。当打开一个现存文件或创建一个新文件时，内核向进程返回一个文件描述符。当写一个文件时，用open或create返回的文件描述符标识该文件，将其作为参数传送给read或write。

在POSIX应用程序中，整数0、1、2应被代换成符号常数：

STDIN_FILENO(标准输入，默认是键盘)
STDOUT_FILENO(标准输出，默认是屏幕)
STDERR_FILENO(标准错误输出，默认是屏幕)
这些常数都定义在头文件<unistd.h>中，文件描述符的范围是0～OPEN_MAX。早期的UNIX版本采用的上限值是19（允许每个进程打开20个文件）， 现在很多系统则将其增加至256。

可用的文件I\O函数很多，包括：打开文件，读文件，写文件等。大多数Linux文件I\O只需要用到5个函数：open，read，write，lseek以及close。
这5个函数是不带缓冲的I/O,

unbuffered I/O
不带缓冲的I/O指每个read和write都调用内核中的一个系统调用


open
====
```
int open(const str * pathname, int oflag, [..., mode_t mode])
```

功能：打开文件 返回值：成功则返回文件描述符，出错返回-1 参数


read
====

```
<unistd.h>

size_t read(int fd, void * buf, size_t count);
```
功能：从打开的文件中读取数据。 
返回值：实际读到的字节数；
已读到文件尾返回0，出错的话返回-1，
ssize_t是系统头文件中用typedef定义的数据类型相当于signed int 参数： 

fd：要读取的文件的描述符 
buf：得到的数据在内存中的位置的首地址 
count：期望本次能读取到的最大字节数。


write
====

```
<unistd.h>

ssize_t write(int fd, const void * buf, size_t count)
```

类似read函数


close
====
函数原型：int close(int filedes) 功能：关闭一个打开的文件 参数：需要关闭文件的文件描述符


lseek
====
```
<unistd.h>

off_t lseek(int filesdes, off_t offset, int whence)
```

功能：设置文件内容读写位置 

返回值：成功返回新的文件位移，出错返回-1；同样off_t是系统头文件定义的数据类型，相当于signed int 参数

whence是SEEK_SET, 那么该文件的位移量设置为距文件开始处offset个字节
whence是SEEK_CUR, 那么该文件的位移量设置为当前值加offset。offset可为正或负
whence是SEEK_END, 那么该文件的位移量设置为文件长度加offset。offset可为正或负


read函数可以监控一个文件描述符(eg：键盘)是否有输入，当键盘没有输入，read将会阻塞，直到用户从键盘输入为止。
用相同的方法可以监控鼠标是否有输入。
但想同时监控鼠标和键盘是否有输入，这个方法就不行的了。


```
// /dev/input/mice 是鼠标的设备文件
fd = open("/dev/input/mice", O_RDONLY);
read(0, buf, 100);
read(fd, buf, 100);

```

在上面的程序中，当read键盘的时候，若无键盘输入则程序阻塞在第2行，此时即使鼠标有输入，程序也没有机会执行第3行获得鼠标的输入。
这种情况就需要select同时监控多个文件描述符。

---


```
<sys/select.h> 
int select(int maxfdp, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout); 
```
返回值：失败返回-1，成功返回readset，writeset，exceptset中所有，有指定变化的文件描述符的数目(若超时返回0)




## 学习目标

### 1.0 当程序执行时，main函数如何被调用

```
int main (int argc, char *argv[]);
```
main函数启动前：

* C程序由内核执行，通过系统调用exec；

* main函数调用前，执行指定的启动路径（start-up routine）；

* 可执行文件认为此地址为程序的启动地址，该地址由链接器指定；

* 启动路径从内核获取参数列表和环境变量，使得main函数可以在稍后被调用时可以获取这些变量。

---

### 2. 命令行参数如何传给新程序的

调用exec的进程可以讲命令行参数传递给新的进程
---

### 3. 典型的存储空间布局是什么样的

高地址到低地址,依次如下

命令行参数 和 环境变量
栈
...(如 共享库，内存映射段)
堆
未初始化的数据（bss）（initialized to zero by exec）
初始化的数据(data) (read from program file by exec)
正文(text)

---


### 4. 如何分配另外的存储空间

### 5. 进程如何使用环境变量

每个程序会接受一个环境变量列表，该列表是一个数组，由一个数组指针指向，该数组指针类型为：
```
extern char **environ;
```

由C程序内存布局图中可以看到，环境变量列表（保存指向环境变量字符串的一组指针）保存在栈的上方内存中。

在该内存中，删除一个字符串很简单。我们只需要找到该指针，删除该指针和该指针指向的字符串。

但是增加或修改一个环境变量困难得多。因为环境变量列表所在的内存往往在进程的内存空间顶部，下面是栈。所以该内存空间无法被向上或者向下扩展。

所以修改环境变量列表的过程如下所述：

如果我们修改一个已经存在的name：
	如果新的value的大小比已经存在的value小或者相当，直接覆盖旧的value；
	如果新的value的大小比已经存在的value大，则我们必须为新的value malloc一个新的内存空间，拷贝新value到该内存中，替换指向旧value的指针为指向新value的指针。

如果我们新增一个环境变量：
	首先我们需要调用malloc为字符串name=value分配空间，拷贝该字符串到目标内存中；
	如果这是我们第一次添加环境变量，我们需要调用malloc分配一个新的空间，拷贝老的环境量列表到新的内存中，并在列表后新增目标环境变量。然后我们设置environ指向新的环境变量列表。
如果这不是我们第一次新增环境变量，则我们只需要realloc多分配一个环境变量的空间，新增的环境变量保存在列表尾部，列表最后仍然是一个null指针。


---

### 6. 进程的各种不同终止方式
进程的终止：进程的5种正常终止方式:
(1)从main()函数返回;
(2)调用exit;
(3)调用_exit或_Exit;
(4)最后一个线程从其启动例程返回；
(5)最后一个线程调用pthread_exit;

异常终止的3种方式：(6)调用abort
(7)接到一个信号并终止
(8)最后一个线程对取消请求做出响应。
有3个函数用于正常终止一个程序：exit(int),_exit(),_Exit()。
exit()终止程序时会执行一些清理程序，然后调用_exit(int)或_Exit(int)进入内核，而后两个函数则是直接进入内核。
main函数返回一个整数值与调用exit函数是等价的。
进程可以通过atexit函数注册清理函数(exithandler)，注册的函数由exit自动调用。
内核使程序执行的唯一方法是调用一个exec函数。
进程自愿终止的唯一方法是显示或隐式（通过exit）的调用_exit或_Exit函数

```
#include <stdlib.h>
void exit(int status);
void _Exit(int status);

#include <unistd.h>
void _exit(int status);
```

---

7. longjmp和setjmp函数以及他们与栈的交互作用

8. 查看进程的资源限制
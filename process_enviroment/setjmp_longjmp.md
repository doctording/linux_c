// http://blog.csdn.net/wykwdy007/article/details/6535322

非局部跳转语句---setjmp和longjmp函数。
非局部指的是，这不是由普通C语言goto，语句在一个函数内实施的跳转，而是在栈上跳过若干调用帧，返回到当前函数调用路径上的某一个函数中。
#include <setjmp.h>
int setjmp(jmp_buf  env);
  返回值：若直接调用则返回0，若从longjmp调用返回则返回非0值

void longjmp(jmp_buf env,int val);
  在希望返回到的位置调用setjmp，此位置在main函数中，因为直接调用该函数，所以其返回值为0.setjmp参数evn的类型是一个特殊的类型jmp_buf，这一数据类型是某种形式的数组，其中存放在调用longjmp时能用来恢复栈状态的所有信息。因为需要在另一个函数中引用env变量，所以规范的处理方式是将env变量定义为全局变量。
   
  当检查到一个错误时,则以两个参数调用longjmp函数，第一个就是在调用setjmp时所用的env，第二个参数是具有非0值的val，它将成为从setjmp处返回的值。使用第二个参数的原因是对于一个setjmp可以有多个longjmp。


使用setjmp和longjmp要注意以下几点：

1、setjmp与longjmp结合使用时，它们必须有严格的先后执行顺序，也即先调用setjmp函数，之后再调用longjmp函数，以恢复到先前被保存的“程序执行点”。否则，如果在setjmp调用之前，执行longjmp函数，将导致程序的执行流变的不可预测，很容易导致程序崩溃而退出

2、不要假设寄存器类型的变量将总会保持不变。在调用longjmp之后，通过setjmp所返回的控制流中，程序中寄存器类型的变量将不会被恢复。寄存器类型的变量，是指为了提高程序的运行效率，变量不被保存在内存中，而是直接被保存在寄存器中。寄存器类型的变量一般都是临时变量，在C语言中，通过register定义，或直接嵌入汇编代码的程序。这种类型的变量。
   
   longjmp必须在setjmp调用之后，而且longjmp必须在setjmp的作用域之内。具体来说，在一个函数中使用setjmp来初始化一个全局标号，然后只要该函数未曾返回，那么在其它任何地方都可以通过longjmp调用来跳转到 setjmp的下一条语句执行。实际上setjmp函数将发生调用处的局部环境保存在了一个jmp_buf的结构当中，只要主调函数中对应的内存未曾释放 （函数返回时局部内存就失效了），那么在调用longjmp的时候就可以根据已保存的jmp_buf参数恢复到setjmp的地方执行。

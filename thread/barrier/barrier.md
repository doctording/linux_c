
屏障是Linux中协调多个线程并行工作的同步机制，
屏障允许每个线程等待直到所有的合作线程到达某一点，然后继续从该点执行，
pthread_join是一种屏障但只允许一个线程等待，pthread_barrier允许任意数量的线程等待！

pthread_barrier_init(pthread_barrier_t *屏障，属性，unsigned int 屏障计数值)；

pthread_barrier_wait(pthread_barrier_t *屏障)：在每个线程中调用则计数值加一并将当前线程阻塞在这里，直到计数值达到初始化时设定的值；

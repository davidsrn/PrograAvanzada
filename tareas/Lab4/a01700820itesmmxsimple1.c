#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

struct task_struct *task;

int simple_init(void){
  for_each_process(task){
    printk(KERN_INFO "Process: %s\nPID: %d\nState: %ld", task->comm, task->pid, task->state);
  }
  return 0;
}

void simple_exit(void){
	printk(KERN_INFO "Removing Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Laboratorio 4 - Sistemas Operativos - ITESM CQ");
MODULE_AUTHOR("CRR - A01700820");

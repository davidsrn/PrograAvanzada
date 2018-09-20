/*
    Juan Arturo Cruz Cardona - A01701804
    Laboratorio 4.1 - Clase Sistemas Operativos
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

/* This function is called when the module is loaded. */
int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");
    struct task_struct *task;
    for_each_process(task){
        printk(KERN_INFO "Name: %s \n ID: %d \n State: %ld", task->comm, task->pid, task->state);
    }

	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

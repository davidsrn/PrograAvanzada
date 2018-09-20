/*
    Juan Arturo Cruz Cardona - A01701804
    Laboratorio 4.2 - Clase Sistemas Operativos
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

/* Exercise 3 and 3.1 */
void recursiveFunction(struct task_struct *newTask){
    struct task_struct *task;
    struct list_head *list;
    list_for_each(list, &newTask->children){
        task = list_entry(list, struct task_struct, sibling);
        printk(KERN_INFO "Name: %s \n ID: %d \n State: %ld", task->comm, task->pid, task->state);
        recursiveFunction(task);
    }
}
/* This function is called when the module is loaded. */
int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");
    // Call the function
    recursiveFunction(&init_task);
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

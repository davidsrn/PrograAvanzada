/*
Laboratorio 4 - parte2
Joaquin Herrera Ramos
A01207504
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

void DFS(struct task_struct *initTask){
	struct task_struct *task;
	struct list_head *list;
	printk(KERN_INFO "Process name: %s [%i]",initTask->comm,initTask->pid);
	list_for_each(list, &initTask->children){
		task= list_entry(list, struct task_struct, sibling);
		/* task points to the next child in the list*/
		DFS(task);
	}
}

/* This function is called when the module is loaded. */
int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");
	DFS(&init_task);
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

/*

	Creado por: Manuel Garcia Huerta
	Matricula: A01701414
	Universidad: ITESM Qro.
	Clase: Sistemas Operativos
	Fecha 29/08/18
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

/* This function is called when the module is loaded. */
void recursion(struct task_struct *task){
	struct task_struct *child;
	struct list_head *list; 

	list_for_each (list, &task->children){
		child = list_entry(list,struct task_struct,sibling);
			printk(KERN_INFO "%-20s  [%d]  [%d] \n",child->comm, child->pid,  child->parent->pid);

		recursion(child);
	}
	
	
}

int simple_init(void) {
	
	printk(KERN_INFO "Loading Module\n");	
	recursion(&init_task);

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


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

//Funcion process info
void proc_prnt(struct task_struct* parent){
	//Definiendo estructuras
	struct task_struct *task;
	struct list_head *list;
	list_for_each(list, &parent->children){
		task=list_entry(list,struct task_struct,sibling);
		printk("%s %ld [%d] - ppid=%d\n",task->comm,task->state,task->pid,task->parent->pid);
		proc_prnt(task);
	}
}

/* This function is called when the module is loaded. */
int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");
	proc_prnt(&init_task);
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

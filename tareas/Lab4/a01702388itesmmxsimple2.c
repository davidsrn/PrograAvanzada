#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>




struct task_struct *task;


void list_processes(struct task_struct *task){
	struct task_struct *child;
	struct list_head *list;

	list_for_each(list, &task->children){
		child = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "%s-[%i] parent pid[%i]",child->comm, child->pid, child->parent->pid);
		list_processes(child);
	}

}

/* This function is called when the module is loaded. */
int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");

	task=&init_task;
//	task=next_task(task);		// en caso de que no entre al proceso uno
	list_processes(task);		//global, no afecta modificarla aquí
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

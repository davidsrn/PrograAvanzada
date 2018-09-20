#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
struct task_struct *task;
struct list_head *list;

void recursive_tasks(struct task_struct * task){
	printk(KERN_INFO "Task %s - %ld - %d\n",task->comm,task->state,task->pid);
	list_for_each(list,&task->children){
		task = list_entry(list,struct task_struct, sibling);
		recursive_tasks(task);
	}
}

/* This function is called when the module is loaded. */
int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");
	recursive_tasks(&init_task);
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

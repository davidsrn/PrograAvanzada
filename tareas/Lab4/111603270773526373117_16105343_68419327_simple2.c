#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

void print_info(struct task_struct *task){
	struct task_struct *next_task;
	struct list_head *list;

	printk("Name = %s, id = %d \n", task->comm, task->pid);

	list_for_each(list, &task->children){
		next_task = list_entry(list, struct task_struct, sibling);
		print_info(next_task);
	}

}

/* This function is called when the module is loaded. */
int simple_init(void) {

	printk(KERN_INFO "Loading Module\n");
	print_info(&init_task);

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

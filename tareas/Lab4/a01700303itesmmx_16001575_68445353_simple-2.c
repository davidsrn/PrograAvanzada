#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

void tree_process(struct task_struct *task){

	struct task_struct *next_task;
	struct list_head *list;

	printk("(process_id = %d) %s\n", task_pid_nr(task), task->comm);

	list_for_each(list, &task->children){
		next_task = list_entry(list, struct task_struct, sibling);
		//Recursive function
		tree_process(next_task);
	}

}

int simple_init(void) {
	tree_process(&init_task);
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
MODULE_DESCRIPTION("Tree Recursive Processes");
MODULE_AUTHOR("MHS");

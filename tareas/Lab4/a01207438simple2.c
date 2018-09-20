#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
struct task_struct *task;
/* This function is called when the module is loaded. */

void check_process(struct task_struct *task){
	printk(KERN_INFO "[%i]		%s\n",task->pid,task->comm);

	struct task_struct *ts;
	struct list_head *list;
	list_for_each(list,&(task->children)){
		ts = list_entry(list,struct task_struct, sibling);

		printk(KERN_INFO "[%i]			%s\n",ts->pid,ts->comm);
		check_process(ts);

	}
//	check_process(ts);

}

int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");

	task=&init_task;
	task=next_task(task);
	check_process(task);


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

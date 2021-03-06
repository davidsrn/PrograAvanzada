#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

void print_task(struct task_struct *task) {

struct list_head *list;
struct task_struct *other_task;

printk("(PID = %d) %s\n", task->pid, task->comm);

list_for_each(list, &task->children) {
    other_task = list_entry(list, struct task_struct, sibling);
    print_task(other_task);
 }
}

/* This function is called when the module is loaded. */
int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");
	
	print_task(&init_task);

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

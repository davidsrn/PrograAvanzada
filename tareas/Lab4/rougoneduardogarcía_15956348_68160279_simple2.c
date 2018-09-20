// Eduardo García Rougon   A01207519
// Sistemas Operativos
// Prof. Pedro Óscar Pérez Murueta

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

struct task_struct *task;

void explore_processes(struct task_struct *task){
	struct task_struct *child;
	struct list_head *list;
	list_for_each(list, &task->children){
		child = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "%s [%i] parent pid [%i]", child->comm, child->pid, child->parent->pid);
		explore_processes(child);
	}
}

/* This function is called when the module is loaded. */
int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");

	task = &init_task;
	explore_processes(task);

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

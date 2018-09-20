#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

void profundidad(struct task_struct *init){
	struct task_struct *task;
	struct list_head *list;
	//printk(KERN_INFO "Nombre: %-20s \t estado: %ld \t pid: [%d] \t ppid: [%d] \t", init->comm, init->state, init->pid, task_ppid_nr(init));
	list_for_each(list, &init->children){
		task = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "Nombre: %-20s \t estado: %ld \t pid: [%d] \t ppid: [%d] \t", task->comm, task->state, task->pid, task_ppid_nr(task));
		profundidad(task);	
	}
}


/* This function is called when the module is loaded. */
int simple_init(void) {
	struct task_struct *init;
	printk(KERN_INFO "Loading Module\n");
	init = &init_task;
	printk(KERN_INFO "Nombre: %-20s \t estado: %ld \t pid: [%d] \t ppid: [%d] \t", init->comm, init->state, init->pid, task_ppid_nr(init));
	profundidad(init);
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

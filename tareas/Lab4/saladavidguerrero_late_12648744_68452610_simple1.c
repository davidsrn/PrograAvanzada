#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

/* This function is called when the module is loaded. */
struct task_struct *task_list;

void proc_info(void){
    for_each_process(task_list)
	{
		printk("Nom_Proc: %s ID: [%d] Estado: %li\n", task_list->comm, task_list->pid, task_list->state);
	}
}

/* This function is called when the module is loaded. */
int simple_init(void){
	printk(KERN_INFO "Loading Module\n");
	//Calling print function
	proc_info();
	return 0;
}

This function is called when the module is removed.* /
void simple_exit(void){
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
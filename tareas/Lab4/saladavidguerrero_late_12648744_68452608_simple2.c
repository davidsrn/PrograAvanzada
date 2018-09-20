#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/sched/signal.h>

void process_dfs(struct task_struct *task)
{
	struct task_struct *child;
	struct list_head *list;
    
	
	list_for_each(list, &task->children)
	{
		child = list_entry(list, struct task_struct, sibling);
        printk("Proc_N: %s, ID: [%d], Estado: %li\n", task->comm, task->pid, task->state);
		process_dfs(child);
	}
}

/* This function is called when the module is loaded. */
int simple_init(void){
	printk(KERN_INFO "Loading Module\n");
	//Calling print function
	proc_info();
	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void){
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
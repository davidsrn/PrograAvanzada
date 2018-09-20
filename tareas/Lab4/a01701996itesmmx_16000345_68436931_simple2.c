#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>
#include <linux/list.h>

//struct task_struct *task;
//struct list_head *list;

/* This function is called when the module is loaded. */

void recursive_function(struct task_struct *s){

struct task_struct *task;
struct list_head *list;

	

		list_for_each(list, &s->children){
	
				task =list_entry(list, struct task_struct, sibling);

				printk("%s %ld %d", task->comm, task->state, task->pid);
		
				recursive_function(task);
		}
	

	
	
}

int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");

	recursive_function(&init_task);

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

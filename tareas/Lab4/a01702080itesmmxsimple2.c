#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

void holicanoli(struct task_struct *task){
		
		struct task_struct *baby;
		struct list_head *list;

	list_for_each(list, &task->children){

		baby = list_entry(list, struct task_struct, sibling);
		printk("Name: %s Process ID: %d State: %ld \n", baby->comm, baby->pid, baby->state);
		holicanoli(baby);

	}
}

/* This function is called when the module is loaded. */
int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");
	
	holicanoli(&init_task);

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

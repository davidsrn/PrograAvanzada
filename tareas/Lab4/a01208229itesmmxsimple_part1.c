#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

/* This function is called when the module is loaded. */
int init_module(void) {
    struct task_struct* task_list;
	printk(KERN_INFO "Loading Module\n");
    for_each_process(task_list){
        printk("Process: %s, Id: [%d], State: %li\n", task_list->comm, task_list->pid, task_list->state);
    }
	return 0;
}

/* This function is called when the module is removed. */
void cleanup_module(void) {
	printk(KERN_INFO "Removing Module\n");
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

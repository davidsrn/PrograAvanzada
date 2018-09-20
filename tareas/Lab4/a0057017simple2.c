#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>
#include <linux/list.h>
/*
void dfsa(struct list_head *list, struct task_struct *task){
    if(list_empty(&task->children)){
        printk("%s - %d - %ld\n", task->comm, task-> pid, task->state);
        return;
    }
    list_for_each(list, &init_task.children){
        task = list_entry(list, struct task_struct, sibling);
        dfsa(list, task);
    }
    return;
}
*/

void dfsa(struct task_struct *task){
    struct list_head *list;
    struct task_struct *child;
    if(list_empty(&task->children)){
        printk("name: %s - pid: %d - state: %ld\n", task->comm, task-> pid, task->state);
        return;
    }
    list_for_each(list, &task->children){
        child = list_entry(list, struct task_struct, sibling);
        dfsa(child);
    }
}

/* This function is called when the module is loaded. */
int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");

    //struct task_struct *task;
    //struct list_head *list;
    

    dfsa(&init_task);

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

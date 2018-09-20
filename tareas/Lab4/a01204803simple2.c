#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

size_t process_counter = 0;

//DFS
void DFS(struct task_struct *task)
{   
    struct task_struct *child;
    struct list_head *list;
    

    printk("name: %s, pid: [%d], state: %li\n", task->comm, task->pid, task->state);
    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);
        ++process_counter;
        DFS(child);
    }


}

/* This function is called when the module is loaded. */
int simple_init(void) {
	
	printk(KERN_INFO "Loading Task Lister Module...\n");
    DFS(&init_task);
    printk(KERN_INFO "== Number of process: %zu\n", process_counter);
    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Task Lister Module...\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

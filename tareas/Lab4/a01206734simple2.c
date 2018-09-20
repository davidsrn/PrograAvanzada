#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int task_lister_init(void){ 
    extern struct task_struct init_task;
    printk(KERN_INFO "Loading Task Lister Module...\n");
    DFS(&init_task);
    return 0;
}


void task_lister_exit(void){
    printk(KERN_INFO "Removing Task Lister Module...\n");
}

void DFS(struct task_struct *task){
    struct task_struct *child;
    struct list_head *list;

    printk("name: %s, pid: [%d], state: %li\n", task->comm, task->pid, task->state);
    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);
        DFS(child);
    }
}
// Macros for registering module entry and exit points.
module_init(task_lister_init);
module_exit(task_lister_exit);

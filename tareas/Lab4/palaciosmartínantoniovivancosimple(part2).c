#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

/* This function is called when the module is loaded. */
void listar(struct task_struct *task){
	struct list_head *list;
	struct task_struct *chil_task;
	list_for_each(list , &task->children){
		chil_task = list_entry(list , struct task_struct , sibling);/* task points to the next child in the list */
		printk("%s  state: %ld pid: %d \n", task->comm, task->state, task->pid);
		listar(chil_task);
	}
}
int simple_init(void) {
	listar(&init_task);
	printk("fin del listado");
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

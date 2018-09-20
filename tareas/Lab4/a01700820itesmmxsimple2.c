#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

void recorrer_procesos(struct task_struct *task){

	struct task_struct *next_task;
	struct list_head *list;

	printk(KERN_INFO "Process: %s\nPID: %d\nStatus: %ld\n", task->comm, task->pid, task->state);

	list_for_each(list, &task->children){
		next_task = list_entry(list, struct task_struct, sibling);
		recorrer_procesos(next_task);
	}

}

int simple_init(void) {
	recorrer_procesos(&init_task);
	return 0;
}

void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Laboratorio 4 - Sistemas Operativos - ITESM CQ");
MODULE_AUTHOR("CRR - A01700820");

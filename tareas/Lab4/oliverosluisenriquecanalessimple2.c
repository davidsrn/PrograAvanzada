#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

void busquedaArbol(struct task_struct *task){
	struct task_struct *child;//puntero del siguiente hijo
	struct list_head *list; //hijos

	//imprime al hijo, donde empieza con el primero que es con el puntero task
	printk(KERN_INFO "nombre: %-20s estado: %ld\tProcess Id: %d\n", task->comm, task-> state, task->pid);
list_for_each(list, &task->children){//loop de los hijos
		//aqui se obtiene al hijo
		child = list_entry(list, struct task_struct, sibling);
		//apunta al siguiente hijo
		busquedaArbol(child);
	}

}

/* This function is called when the module is loaded. */
int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");
	busquedaArbol(&init_task);
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

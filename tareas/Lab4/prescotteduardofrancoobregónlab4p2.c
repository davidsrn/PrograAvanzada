/*
Eduardo Franco Obregón Prescott - A01701206
Sistemas Operativos
	Laboratorio 4 Parte 2 - Listado de procesos
Septiembre 2018
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

void proc_prnt(struct task_struct* parent){
	
    // Definir las estructurass que contendran los datos
	struct task_struct *task;
	struct list_head *list;

	list_for_each(list, &parent->children){
		task = list_entry ( list, struct task_struct, sibling);
		printk("Task: %s   State: %ld   PID: %d   PPID: %d\n", task->comm, task->state, task->pid, task->parent->pid); //Imprimir los procesos; tarea, estado, identificaciOn del proceso e ppid
		proc_prnt(task);
	}
}

/* This function is called when the module is loaded. */
int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");
	proc_prnt(&init_task);
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

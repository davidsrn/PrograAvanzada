/*
Eduardo Franco Obregón Prescott - A01701206
Sistemas Operativos
	Laboratorio 4 Parte 1 - Listado de Procesos
Septiembre 2018
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

// Define la estructura
struct task_struct *task;

void proc_info(void)
{
	for_each_process(task)
	{
		printk("Task: %s   State: %ld   PID: %d\n", task->comm, task->state, task->pid); //Imprimir los procesos, estado e id del proceso
	}
}

/* This function is called when the module is loaded. */
int simple_init(void){
	printk(KERN_INFO "Loading Module\n");
	//Calling print function
	proc_info();
	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void){
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

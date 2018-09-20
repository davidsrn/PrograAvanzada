#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>


/* This function is called when the module is loaded. */
int simple_init(void) {
	struct task_struct *task; //puntero a la tarea,  que ayuda  a lo que se va a imprimir

	printk(KERN_INFO "Loading Module\n");
	for_each_process(task){
		printk(KERN_INFO "Nombre: %-20s Estado: %ld\tProcess Id: %d\n", task->comm, task->state, task->pid);
	//task->comm es el nombre
	//task->state el estado 
	//el terceo es el id del proceso
	}
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

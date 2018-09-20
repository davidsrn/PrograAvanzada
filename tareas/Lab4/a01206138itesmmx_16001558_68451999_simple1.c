// Valter Núñez - A01206138

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>

int simple_init(void) {
	printk(KERN_INFO "Cargando Modulo de Kernel\n");
    struct task_struct *task;
    for_each_process(task){
        printk(KERN_INFO "Nombre: %s\n ID: %d\n Estado: %ld", task->comm, task->pid, task->state);
    }
	return 0;
}

//para eliminar modulo
void simple_exit(void) {
	printk(KERN_INFO "Removiendo Modulo\n");
}

//Puntos de entrada y salida
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

// Valter Núñez -- A01206138

#include <linux/sched/signal.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

void recursiveFunction(struct task_struct *newTask){
    struct task_struct *task;
    struct list_head *list;
    list_for_each(list, &newTask->children){
        task = list_entry(list, struct task_struct, sibling);
        printk(KERN_INFO "Nombre: %s\n ID: %d\n Estado: %ld", task->comm, task->pid, task->state);
        recursiveFunction(task);
    }
}

//Para cargar modulo
int simple_init(void) {
	printk(KERN_INFO "Cargando Modulo de Kernel\n");
    recursiveFunction(&init_task);
	return 0;
}

//Para eliminar modulo
void simple_exit(void) {
	printk(KERN_INFO "Removiendo Modulo de Kernel\n");
}

//Puntos de entrada y salida
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

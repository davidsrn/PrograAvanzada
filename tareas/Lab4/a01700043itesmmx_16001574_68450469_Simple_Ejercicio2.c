#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>

void DFS(struct task_struct *task)
{
    struct task_struct *child;
    struct list_head *list;

    printk("Nombre: %s, Proceso: [%d], Estado: %li\n", task->comm, task->pid, task->state);
    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);
        DFS(child);
    }
}

int task_lister_init(void)
{ extern struct task_struct init_task;
    printk(KERN_INFO "Cargando Modulo...\n");
    DFS(&init_task);

    return 0;
}

void task_lister_exit(void)
{
    printk(KERN_INFO "Borrando Modulo...\n");
}

module_init(task_lister_init);
module_exit(task_lister_exit);

/*MODULE_LICENSE("Laboratorio 4");
MODULE_DESCRIPTION("Laboratorio 4");
MODULE_AUTHOR("Cristhian Michelle Estrada Quiroz");*/

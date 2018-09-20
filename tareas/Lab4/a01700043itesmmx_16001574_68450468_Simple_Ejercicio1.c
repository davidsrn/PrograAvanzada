#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>


int lab4_lista_linear_init(void)
{
  printk(KERN_INFO "Cargando Modulo...\n");

  struct task_struct *task;
  for_each_process(task)
  {
    printk(KERN_INFO "Id Proceso: %d | Nombre Proceso: %s | Estado proceso: %ld\n", task->pid, task->comm, task->state);
  }

  printk(KERN_INFO "Modulo Cargado.\n");
  return 0;
}

void lab4_lista_linear_exit(void)
{
  printk(KERN_INFO "Modulo Borrado.\n");
}

module_init(lab4_lista_linear_init);
module_exit(lab4_lista_linear_exit);

/*MODULE_LICENSE("Laboratorio 4");
MODULE_DESCRIPTION("Laboratorio 4");
MODULE_AUTHOR("Cristhian Michelle Estrada Quiroz");*/

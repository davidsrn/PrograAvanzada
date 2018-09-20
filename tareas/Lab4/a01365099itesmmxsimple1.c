#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

int simple_init (void)
{
	printk ( KERN_INFO "Loading Module \n");

 	struct task_struct* task;

 	for_each_process(task)
 	{
 		printk("Task: %s , PID: [%d] \n" task->comm, task->pid);

 	}

}
void simple_exit (void)
{
	 printk ( KERN_INFO "Removing Module \n");
}
/* Macros for registering module entry and exit points . */
module_init (simple_init);
module_exit (simple_exit);
MODULE_LICENSE ("GPL");
MODULE_DESCRIPTION ("Simple Module");
MODULE_AUTHOR ("SGG");
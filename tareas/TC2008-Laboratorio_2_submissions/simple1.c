/*
Por: Manuel Garcia Huerta 
Universidad: ITESM Qro.
Matricula: A01701414
Fecha: 16 - 08 -18 
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>


struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};
static LIST_HEAD(birthday_list);



/* This function is called when the module is loaded. */
int simple_init(void)
{
		
       	printk(KERN_INFO "Loading Module\n");
       	struct birthday* person, * aPerson;
       	int i;
       	for (i = 0; i <= 5; ++i)
       	{
			person = kmalloc(sizeof(*person), GFP_KERNEL);
			person->day = 5+i;
			person->month = 8+i;
			person->year = 1998+i;
			INIT_LIST_HEAD(&person->list);
			list_add_tail(&(person->list),&(birthday_list));
		}

		

		printk(KERN_INFO "Travelling in list");

		list_for_each_entry(aPerson, &birthday_list, list){
			printk(KERN_INFO "Day : %i \n Year: %i", aPerson->day,aPerson->year);
		}
/*	
*/
       return 0;
}


/* This function is called when the module is removed. */
void simple_exit(void) {
	struct birthday *aPerson, *tmp;
	int node=0;
	printk(KERN_INFO "Removing Module\n");
	printk(KERN_INFO "Deleting list");
	list_for_each_entry_safe(aPerson,tmp,&birthday_list,list){
		printk(KERN_INFO "Freeing node %i",node);
		list_del(&aPerson->list);
		kfree(aPerson);
		node++;
	}
	
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


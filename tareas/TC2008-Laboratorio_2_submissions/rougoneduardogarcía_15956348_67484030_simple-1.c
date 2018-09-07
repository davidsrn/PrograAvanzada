//Eduardo García Rougon  A01207519
//Sistemas Operativos  Laboratorio 2

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

       struct birthday *person1, *person2, *person3, *person4, *person5, *ptr;

       person1 = kmalloc(sizeof(*person1),GFP_KERNEL);
       person1->day = 8;
       person1->month = 11;
       person1->year = 1994;
       INIT_LIST_HEAD(&person1->list);

       person2 = kmalloc(sizeof(*person2),GFP_KERNEL);
       person2->day = 31;
       person2->month = 3;
       person2->year = 1993;
       INIT_LIST_HEAD(&person2->list);

       person3 = kmalloc(sizeof(*person3),GFP_KERNEL);
       person3->day = 23;
       person3->month = 8;
       person3->year = 1997;
       INIT_LIST_HEAD(&person3->list);

       person4 = kmalloc(sizeof(*person4),GFP_KERNEL);
       person4->day = 21;
       person4->month = 9;
       person4->year = 1965;
       INIT_LIST_HEAD(&person4->list);

       person5 = kmalloc(sizeof(*person5),GFP_KERNEL);
       person5->day = 12;
       person5->month = 5;
       person5->year = 1965;
       INIT_LIST_HEAD(&person5->list);

       list_add_tail(&person1->list, &birthday_list);
       list_add_tail(&person2->list, &birthday_list);
       list_add_tail(&person3->list, &birthday_list);
       list_add_tail(&person4->list, &birthday_list);
       list_add_tail(&person5->list, &birthday_list);

       list_for_each_entry(ptr, &birthday_list, list) {
              /* en cada iteración, ptr indica cual es el nodo actual de la lista */
              printk(KERN_INFO "%i/%i/%i\n", ptr->day, ptr->month, ptr->year);
       }

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {

	printk(KERN_INFO "Removing Module\n");

	struct birthday *ptr, *next;

	list_for_each_entry_safe(ptr, next, &birthday_list, list) {
		/* ptr apunta al nodo actual de la lista */
		list_del(&ptr->list);
		kfree(ptr);
	}

}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


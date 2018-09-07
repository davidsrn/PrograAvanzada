/*
Joaquin Herrera Ramos A01207504
19 de agosto de 2018
Laboratorio 2
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

static LIST_HEAD(birthday_list);
struct birthday
{
	int day;
	int month;
	int year;
	struct list_head list;
};

/* This function is called when the module is loaded. */
int simple_init(void)
{
	struct birthday *person;
	struct birthday *ptr;
	int i;
	printk(KERN_INFO "Loading Module\n");
	//creacion de 5 cumpleanos
	for(i=0;i<5;++i){
		person = kmalloc(sizeof(*person),GFP_KERNEL);
		person->day=2+i;
		person->month=8-i;
		//solo para hacerlo no lineal
		if(i%2==0){
			person->year = 1995+i;
		}else{
			person->year = 1995-i;
		}
		INIT_LIST_HEAD(&person->list);
		list_add_tail(&person->list,&birthday_list);
	}
	i=0;
	//recorre la lista
	list_for_each_entry(ptr,&birthday_list,list){
		printk(KERN_INFO "%i Person's birthday: %i/%i/%i",++i,ptr->day,ptr->month,ptr->year);
	}
	printk(KERN_INFO "Module loaded\n");
	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	struct birthday *ptr, *next;
	printk(KERN_INFO "Removing Module\n");
	//elimina de la lista
	list_for_each_entry_safe(ptr,next,&birthday_list,list){
		list_del(&ptr->list);
		kfree(ptr);
	}
	//marca el final
	printk(KERN_INFO "Module removed\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


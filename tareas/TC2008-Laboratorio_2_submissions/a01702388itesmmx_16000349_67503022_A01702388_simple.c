#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>


struct birthday{
	int day;
	int month;
	int year;
	struct list_head list;
};


static LIST_HEAD(birthday_list);


struct birthday *ptr1, *next1;


/* This function is called when the module is loaded */
int simple_init(void){

	printk(KERN_INFO "Loading Module\n");

/*--------------------------------------INSTANCIAS-------------------------------------*/


	struct birthday *person;

	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 2;
	person->month = 8;
	person->year = 1995;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);


	struct birthday *person1;
	person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
	person1->day = 4;
	person1->month = 2;
	person1->year = 1998;
	INIT_LIST_HEAD(&person1->list);
	list_add_tail(&person1->list, &birthday_list);


	struct birthday *person2;
	person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
	person2->day = 14;
	person2->month = 2;
	person2->year = 1998;
	INIT_LIST_HEAD(&person2->list);
	list_add_tail(&person2->list, &birthday_list);


	struct birthday *person3;
	person3= kmalloc(sizeof(*person3), GFP_KERNEL);
	person3->day = 15;
	person3->month = 2;
	person3->year = 1998;
	INIT_LIST_HEAD(&person3->list);
	list_add_tail(&person3->list, &birthday_list);

	struct birthday *person4;
	person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
	person4->day = 16;
	person4->month = 2;
	person4->year = 1998;
	INIT_LIST_HEAD(&person4->list);
	list_add_tail(&person4->list, &birthday_list);

	struct birthday *person5;
	person5= kmalloc(sizeof(*person5), GFP_KERNEL);
	person5->day=17;
	person5->month = 2;
	person5->year= 1998;
	INIT_LIST_HEAD(&person5->list);
	list_add_tail(&person5->list, &birthday_list);

/*------------------------------------------------------------------------------------*/
	list_for_each_entry(ptr1, &birthday_list, list){
		printk(KERN_INFO "%i/%i/%i \n", ptr1->day, ptr1->month, ptr1->year);
	}
	printk(KERN_INFO "End of list\n");
	return 0;
}


/* This function is called when the module is removed. */
void simple_exit(void) {

	printk(KERN_INFO "Removing Module\n");
	list_for_each_entry_safe(ptr1, next1, &birthday_list, list){
		list_del(&ptr1->list);
		kfree(ptr1);
	}
	printk(KERN_INFO "The list has been deleted successfully\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

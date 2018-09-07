#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
	
	struct birthday{
	int day;
	int month;
	int year;
	struct list_head list;
	}
	static LIST_HEAD(birthday_list);

	static birthday *person1;
	person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
	person1->day = 17;
	person1->month = 3;
	person1->year = 1998;
	INIT_LIST_HEAD(&person1->list);
	list_add_tail(&person1->list, &birthday_list);

	static birthday *person2;
	person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
	person2->day = 11;
	person2->month = 5;
	person2->year = 1997;
	INIT_LIST_HEAD(&person2->list);
	list_add_tail(&person2->list, &birthday_list);

	static birthday *person3;
	person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
	person3->day = 2;
	person3->month = 6;
	person3->year = 1985;
	INIT_LIST_HEAD(&person3->list);
	list_add_tail(&person3->list, &birthday_list);


	static birthday *person4;
	person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
	person4->day = 1;
	person4->month = 12;
	person4->year = 1965;
	INIT_LIST_HEAD(&person4->list);
	list_add_tail(&person4->list, &birthday_list);


	static birthday *person5;
	person5 = kmalloc(sizeof(*person5), GFP_KERNEL);
	person5->day = 10;
	person5->month = 1;
	person5->year = 1969;
	INIT_LIST_HEAD(&person5->list);
	list_add_tail(&person5->list, &birthday_list);

	struct birthday *ptr;
	list_for_each_entry(ptr, &birthday_list, list){
	printk(ptr);
	}
       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
	struct birthday *ptr, *next;
	list_for_each_entry_safe(ptr, next, &birthday_list, list){
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


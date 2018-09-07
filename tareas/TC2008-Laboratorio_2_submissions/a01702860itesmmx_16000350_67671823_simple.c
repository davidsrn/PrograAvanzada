#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

static LIST_HEAD(birthday_list);

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

/* This function is called when the module is loaded. */
int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");

    struct birthday *person;
    person = kmalloc(sizeof(*person),GFP_KERNEL);
    person->day = 2;
    person->month = 8;
    person->year = 1995;
    INIT_LIST_HEAD(&person->list);
    list_add_tail(&person->list, &birthday_list);

    struct birthday *person1;
    person1 = kmalloc(sizeof(*person1),GFP_KERNEL);
    person1->day = 30;
    person1->month = 8;
    person1->year = 1997;
    INIT_LIST_HEAD(&person1->list);
    list_add_tail(&person1->list, &birthday_list);

    struct birthday *person2;
    person2 = kmalloc(sizeof(*person2),GFP_KERNEL);
    person2->day = 1;
    person2->month = 5;
    person2->year = 1998;
    INIT_LIST_HEAD(&person2->list);
    list_add_tail(&person2->list, &birthday_list);

    struct birthday *person3;
    person3 = kmalloc(sizeof(*person3),GFP_KERNEL);
    person3->day = 18;
    person3->month = 12;
    person3->year = 1997;
    INIT_LIST_HEAD(&person3->list);
    list_add_tail(&person3->list, &birthday_list);

    struct birthday *person4;
    person4 = kmalloc(sizeof(*person4),GFP_KERNEL);
    person4->day = 1;
    person4->month = 5;
    person4->year = 1998;
    INIT_LIST_HEAD(&person4->list);
    list_add_tail(&person4->list, &birthday_list);


    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list)
    {
        printk(KERN_INFO "Cumpleanios: %i / %i / %i\n", ptr->day, ptr->month, ptr->year);
    }

    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	struct birthday *ptr, *next;
	list_for_each_entry_safe(ptr, next, &birthday_list, list) {
		printk(KERN_INFO "Borrando lista");
		list_del(&ptr->list);
		kfree(ptr);
	}

	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


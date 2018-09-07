#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>



struct birthday {
    int day ;
    int month ;
    int year ;
    struct list_head list ;
};

static LIST_HEAD(birthday_list);
struct birthday *cur, *next;
struct birthday *birthdays[5];

int i = 0;


/* This function is called when the module is loaded. */

int simple_init(void){
    
    printk(KERN_INFO "Loading Module\n");

    for(i = 0; i < 5; i++){
        birthdays[i] = kmalloc(sizeof(*birthdays[i]), GFP_KERNEL);
        birthdays[i]->day = i+10;
        birthdays[i]->month = i+7;
        birthdays[i]->year = i*10+1950;
        INIT_LIST_HEAD (&birthdays[i]->list );
        list_add_tail(&birthdays[i]->list, &birthday_list);
    }

    list_for_each_entry_safe(cur, next, &birthday_list, list){
        printk("born %i/%i/%i\n", cur->day, cur->month, cur->year);
    }

    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {

    list_for_each_entry_safe(cur, next, &birthday_list, list){
        printk("deleted list element");
        list_del(&cur->list);
        kfree(cur);
    }

	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


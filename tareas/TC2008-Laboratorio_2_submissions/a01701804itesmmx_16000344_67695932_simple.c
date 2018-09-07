/*
    Juan Arturo Cruz Cardona - A01701804
    Laboratorio 2 - Clase Sistemas Operativos
*/
/* Libraries */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
/* This macro defines and initilize the variable "birthday_list" that has the type of "struct list_head" */
static LIST_HEAD(birthday_list);

/* Structure that contains the variables of the elements to add in the linked list*/
struct birthday{
    int day;
    int month;
    int year;
    struct list_head list;
};

/* This function is called when the module is loaded. */
int simple_init(void){
    printk(KERN_INFO "Loading Module\n");
    /* Create 5 instances of the structure*/
    struct birthday *person;
    person = kmalloc(sizeof(*person), GFP_KERNEL);
    person-> day = 22;
    person-> month = 8;
    person-> year = 2018;
    INIT_LIST_HEAD(&person->list);
    list_add_tail(&person->list, &birthday_list);

    struct birthday *person1;
    person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
    person1-> day = 17;
    person1-> month = 6;
    person1-> year = 2006;
    INIT_LIST_HEAD(&person1->list);
    list_add_tail(&person1->list, &birthday_list);

    struct birthday *person2;
    person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
    person2-> day = 2;
    person2-> month = 12;
    person2-> year = 1990;
    INIT_LIST_HEAD(&person2->list);
    list_add_tail(&person2->list, &birthday_list);

    struct birthday *person3;
    person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
    person3-> day = 27;
    person3-> month = 10;
    person3-> year = 1955;
    INIT_LIST_HEAD(&person3->list);
    list_add_tail(&person3->list, &birthday_list);

    struct birthday *person4;
    person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
    person4-> day = 22;
    person4-> month = 2;
    person4-> year = 2000;
    INIT_LIST_HEAD(&person4->list);
    list_add_tail(&person4->list, &birthday_list);

    /* loop to print the info of each element of the list */
    struct birthday *prt;
    list_for_each_entry(prt, &birthday_list, list){
        printk(KERN_INFO "Cumple: %i - %i - %i\n", prt->day, prt->month, prt->year);
    }
    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
    struct birthday *ptr, *next;
    /* Delete elements of the linked list */
    list_for_each_entry_safe(ptr, next, &birthday_list, list){
        /* ptr points to the actual node of linked list */
        printk(KERN_INFO "Removing Module\n");
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

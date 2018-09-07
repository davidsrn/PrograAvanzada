#include <linux/list.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/kernel.h>

/*  LAB 2
    By Victor Hugo Torres Rivera */

/* Linked List for birthdays */
struct birthday{
  int day;
  int month;
  int year;
  struct list_head list;
};

/* Macro to declare the header of the list */
static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
int simple_init(void){
  /* Create a declare struct birthday */
  struct birthday *pointer, *person1, *person2, *person3, *person4, *person5;

  printk(KERN_INFO "Loading Module\n");

  person1  = kmalloc(sizeof(*person1), GFP_KERNEL);
  person1 -> day = 2;
  person1 -> month = 8;
  person1 -> year = 1995;
  INIT_LIST_HEAD(&person1 -> list);

  /* Add instance to the end of the list. */
  list_add_tail(&person1 -> list, &birthday_list);

  person2  = kmalloc(sizeof(*person2), GFP_KERNEL);
  person2 -> day = 3;
  person2 -> month = 8;
  person2 -> year = 1998;
  INIT_LIST_HEAD(&person2 -> list);

  /* Add instance to the end of the list. */
  list_add_tail(&person2 -> list, &birthday_list);

  person3  = kmalloc(sizeof(*person3), GFP_KERNEL);
  person3 -> day = 22;
  person3 -> month = 10;
  person3 -> year = 1978;
  INIT_LIST_HEAD(&person3 -> list);

  /* Add instance to the end of the list. */
  list_add_tail(&person3 -> list, &birthday_list);

  person4  = kmalloc(sizeof(*person4), GFP_KERNEL);
  person4 -> day = 4;
  person4 -> month = 2;
  person4 -> year = 1996;
  INIT_LIST_HEAD(&person4 -> list);

  /* Add instance to the end of the list. */
  list_add_tail(&person4 -> list, &birthday_list);

  person5  = kmalloc(sizeof(*person5), GFP_KERNEL);
  person5 -> day = 2;
  person5 -> month = 12;
  person5 -> year = 1993;
  INIT_LIST_HEAD(&person5 -> list);

  /* Add instance to the end of the list. */
  list_add_tail(&person5 -> list, &birthday_list);

  /* Print birthdays */
  list_for_each_entry(pointer, &birthday_list, list){
    printk(KERN_INFO "Year of a person %i", pointer->year);
  }


  return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
  struct birthday *pointer, *next;
	printk(KERN_INFO "Removing Module\n");
  list_for_each_entry_safe(pointer, next, &birthday_list, list){
    list_del(&pointer->list);
    kfree(pointer);
  }

}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

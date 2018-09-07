/*
  LAB2

  Valter Núñez
  A01206138

*/

/*Imports*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

static LIST_HEAD (birthday_list);

struct birthday {
    int day ;
    int month ;
    int year ;
    struct list_head list ;
};

/* This function is called when the module is loaded. */
int simple_init(void){

       printk(KERN_INFO "Loading Module\n");
  /* declaracion de variables */
       struct birthday *person1;
       struct birthday *person2;
       struct birthday *person3;
       struct birthday *person4;
       struct birthday *person5;

       person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
       person1 -> day = 19;
       person1 -> month = 10;
       person1 -> year = 1996;
       INIT_LIST_HEAD(&person1->list);
      /* agrega a la lista */
       list_add_tail(&person1->list, &birthday_list);


       person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
       person2 -> day = 6;
       person2 -> month = 10;
       person2 -> year = 1966;
       INIT_LIST_HEAD(&person2->list);
      /* agrega a la lista */
       list_add_tail(&person2->list, &birthday_list);

       person5 = kmalloc(sizeof(*person5), GFP_KERNEL);
       person5 -> day = 1;
       person5 -> month = 1;
       person5 -> year = 1900;
       INIT_LIST_HEAD(&person5->list);
      /* agrega a la lista */
       list_add_tail(&person5->list, &birthday_list);


       person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
       person3 -> day = 10;
       person3 -> month = 1;
       person3 -> year = 1965;
       INIT_LIST_HEAD(&person3->list);
      /* agrega a la lista */
       list_add_tail(&person3->list, &birthday_list);


       person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
       person4 -> day = 12;
       person4 -> month = 1;
       person4 -> year = 1960;
       INIT_LIST_HEAD(&person4->list);
      /* agrega a la lista */
       list_add_tail(&person4->list, &birthday_list);

       /* declaracion pointer*/
       struct birthday *ptr;
       /*recorre lista*/
       list_for_each_entry(ptr, &birthday_list, list) {
           printk(KERN_INFO "Birthday: %i / %i / %i \n", ptr->month, ptr->day, ptr->year);
       }
       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
  struct birthday *ptr, *next;
      list_for_each_entry_safe(ptr, next, &birthday_list, list) {
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

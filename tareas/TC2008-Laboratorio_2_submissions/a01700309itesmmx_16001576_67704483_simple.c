/*--------------------------------------------
  A01700309
  Rodolfo Martínez Guevara
  ISC
  22 de agosto del 2018
----------------------------------------------*/

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
       //Variables
       struct birthday *person1;
       struct birthday *person2;
       struct birthday *person3;
       struct birthday *person4;
       struct birthday *person5;
       struct birthday *ptr;

       printk(KERN_INFO "Loading Module\n");

       person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
       person1 -> day = 31;
       person1 -> month = 03;
       person1 -> year = 1997;
       INIT_LIST_HEAD(&person1->list);
       //Añade a structura
       list_add_tail(&person1->list, &birthday_list);

       person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
       person2 -> day = 15;
       person2 -> month = 12;
       person2 -> year = 2000;
       INIT_LIST_HEAD(&person2->list);
       list_add_tail(&person2->list, &birthday_list);

       person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
       person3 -> day = 15;
       person3 -> month = 11;
       person3 -> year = 1967;
       INIT_LIST_HEAD(&person3->list);
       list_add_tail(&person3->list, &birthday_list);

       person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
       person4 -> day = 24;
       person4 -> month = 4;
       person4 -> year = 1997;
       INIT_LIST_HEAD(&person4->list);
       list_add_tail(&person4->list, &birthday_list);

       person5 = kmalloc(sizeof(*person5), GFP_KERNEL);
       person5 -> day = 27;
       person5 -> month = 12;
       person5 -> year = 1967;
       INIT_LIST_HEAD(&person5->list);
       list_add_tail(&person5->list, &birthday_list);

       //Recorre la lista he imprime cada localidad
       list_for_each_entry(ptr, &birthday_list, list) {
           printk(KERN_INFO "%i / %i / %i \n", ptr->month, ptr->day, ptr->year);
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

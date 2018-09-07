#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/types.h>

struct birthday {
  int day ;
  int month ;
  int year ;
  int person;
  struct list_head list ;
};

/* This function is called when the module is loaded. */
int simple_init(void){
  //
  static LIST_HEAD ( birthday_list ) ;

  struct birthday *person1 ;
  person1 = kmalloc ( sizeof (*person1 ) , GFP_KERNEL ) ;
  person1 -> person = 1;
  person1 -> day = 23;
  person1 -> month = 11;
  person1 -> year = 1996;
  INIT_LIST_HEAD (& person1 -> list ) ;
  list_add_tail (& person1 -> list , & birthday_list ) ;

  struct birthday *person2 ;
  person2 = kmalloc ( sizeof (*person2 ) , GFP_KERNEL ) ;
  person2 -> person = 2;
  person2 -> day = 2;
  person2 -> month = 7;
  person2 -> year = 1993;
  INIT_LIST_HEAD (& person2 -> list ) ;
  list_add_tail (& person2 -> list , & birthday_list ) ;

  struct birthday *person3 ;
  person3 = kmalloc ( sizeof (*person3 ) , GFP_KERNEL ) ;
  person3 -> person = 3;
  person3 -> day = 3;
  person3 -> month = 2;
  person3 -> year = 1999;
  INIT_LIST_HEAD (& person3 -> list ) ;
  list_add_tail (& person3 -> list , & birthday_list ) ;

  struct birthday *person4 ;
  person4 = kmalloc ( sizeof (*person4 ) , GFP_KERNEL ) ;
  person4 -> person = 4;
  person4 -> day = 9;
  person4 -> month = 9;
  person4 -> year = 1967;
  INIT_LIST_HEAD (& person4 -> list ) ;
  list_add_tail (& person4 -> list , & birthday_list ) ;

  struct birthday *person5 ;
  person5 = kmalloc ( sizeof (*person5 ) , GFP_KERNEL ) ;
  person5 -> person = 5;
  person5 -> day = 9;
  person5 -> month = 4;
  person5 -> year = 1965;
  INIT_LIST_HEAD (& person5 -> list ) ;
  list_add_tail (& person5 -> list , & birthday_list ) ;

  struct birthday *ptr ;

  list_for_each_entry ( ptr , & birthday_list , list ) {
  /* en cada iteraciOn , ptr indica cuAl es */
    printk("persona%i: %i/%i/%i \n", ptr -> person, ptr -> day, ptr -> month, ptr -> year);
  /* el nodo actual de la lista */
  }

  return 0;

}

/* This function is called when the module is removed. */
void simple_exit(void) {
  struct birthday *ptr , *next ;
  list_for_each_entry_safe ( ptr , next , & birthday_list , list ) {
  /* prt apunta al nodo actual de la lista */
    list_del (&ptr->list) ;
    kfree ( ptr ) ;
  }
  printk(KERN_INFO "Personas eliminadas\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday Module");
MODULE_AUTHOR("MHS");

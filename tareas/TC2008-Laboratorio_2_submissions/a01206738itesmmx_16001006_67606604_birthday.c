/*
  Santiago Valencia A01206738
  LAB2 Sistemas Operativos
*/

#include <linux/list.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

struct birthday {
  int day;
  int month;
  int year;
  struct list_head list;
};

static LIST_HEAD(birthday_list);

int simple_init(void){
  struct birthday *ptr;
  int i;

  struct birthday *person1, *person2, *person3, *person4, *person5;

  person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
  person1 ->day = 2;
  person1 ->month = 9;
  person1 ->year = 1995;
  INIT_LIST_HEAD(&person1->list);
  list_add_tail(&person1->list, &birthday_list);

  person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
  person2 ->day = 3;
  person2 ->month = 9;
  person2 ->year = 1996;
  INIT_LIST_HEAD(&person2->list);
  list_add_tail(&person2->list, &birthday_list);

  person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
  person3 ->day = 8;
  person3 ->month = 8;
  person3 ->year = 1997;
  INIT_LIST_HEAD(&person3->list);
  list_add_tail(&person3->list, &birthday_list);

  person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
  person4 ->day = 10;
  person4 ->month = 3;
  person4 ->year = 1998;
  INIT_LIST_HEAD(&person4->list);
  list_add_tail(&person4->list, &birthday_list);

  person5 = kmalloc(sizeof(*person5), GFP_KERNEL);
  person5 ->day = 12;
  person5 ->month = 1;
  person5 ->year = 1999;
  INIT_LIST_HEAD(&person5->list);
  list_add_tail(&person5->list, &birthday_list);

  printk(KERN_INFO "Loading Module\n");
  i = 0;

  list_for_each_entry(ptr, &birthday_list, list) {
    /* en cada iteraciOn, ptr indica cuAl es */
    /* el nodo actual de la lista */
    i++;
    printk(KERN_INFO "Person %i: %d, %d %d", i, ptr->month, ptr->day, ptr->year);
  }

  return 0;

}

void simple_exit(void){
    struct birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        /* prt apunta al nodo actual de la lista */
        list_del(&ptr->list);
        kfree(ptr);
    }
    printk(KERN_INFO "Removing Module\n");
}

module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LAB2 Module");
MODULE_AUTHOR("Santi");

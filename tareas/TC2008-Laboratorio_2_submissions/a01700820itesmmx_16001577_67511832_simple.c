#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

/*
  Carlos Román Rivera
  A01700820
  Laboratorio 2
  Sistemas Operativos
  Fecha: 19/08/2018
*/

struct birthday{
  int day;
  int month;
  int year;
  struct list_head list;
};

static LIST_HEAD(birthday_list);

int simple_init(void){
  struct birthday *person1, *person2, *person3, *person4, *person5;
  struct birthday *ptr;
  int i;

  printk(KERN_INFO "Loading Module\n");

  person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
  person1->day = 4;
  person1->month = 11;
  person1->year = 1966;
  INIT_LIST_HEAD(&person1->list);
  list_add_tail(&person1->list, &birthday_list);

  person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
  person2->day = 14;
  person2->month = 2;
  person2->year = 1968;
  INIT_LIST_HEAD(&person2->list);
  list_add_tail(&person2->list, &birthday_list);

  person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
  person3->day = 9;
  person3->month = 7;
  person3->year = 1996;
  INIT_LIST_HEAD(&person3->list);
  list_add_tail(&person3->list, &birthday_list);

  person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
  person4->day = 18;
  person4->month = 3;
  person4->year = 1998;
  INIT_LIST_HEAD(&person4->list);
  list_add_tail(&person4->list, &birthday_list);

  person5 = kmalloc(sizeof(*person5), GFP_KERNEL);
  person5->day = 3;
  person5->month = 12;
  person5->year = 1999;
  INIT_LIST_HEAD(&person5->list);
  list_add_tail(&person5->list, &birthday_list);

  i = 0;
  list_for_each_entry(ptr, &birthday_list, list){
    i++;
    printk(KERN_INFO "Node %d: %d/%d/%d\n", i, ptr->day, ptr->month, ptr->year);
  }

  return 0;
}

void simple_exit(void){
  struct birthday *ptr, *next;
  int i;

  i = 0;
  list_for_each_entry_safe(ptr, next, &birthday_list, list){
    i++;
    list_del(&ptr->list);
    kfree(ptr);
    printk(KERN_INFO "Node %d Deleted.", i);
  }

  printk(KERN_INFO "Module Removed and Information Deleted\n");
}

// Macros para cargar y salir del módulo.
// Init debe recibir un 0 si se cargo con éxito.
// Exit no espera nada como respuesta.
module_init(simple_init);
module_exit(simple_exit);

// La siguiente información es opcional.
// Incluirla es una buena práctica al desarrollar módulos de kernel.
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("CRR");

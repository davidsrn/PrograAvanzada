#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

MODULE_LICENSE("A01700043");
MODULE_DESCRIPTION("Lista Laboratiorio2");
MODULE_AUTHOR("Cristhian Quiroz A01700043");

struct Person {
    char name[30];
    unsigned int day;
    unsigned int month;
    unsigned int year;
    struct list_head list; /* Estructura de lista kernel*/
};

struct Person personList;

int init_module() {
    struct Person *aNewPerson, *aPerson;
    unsigned int i;

    printk(KERN_INFO "initialize kernel modulen");
    INIT_LIST_HEAD(&personList.list);    //or LIST_HEAD(mylist);

    /* llena la lista mylist */
    for(i=0; i<5; ++i){
        aNewPerson = kmalloc(sizeof(*aNewPerson), GFP_KERNEL);
        strcpy(aNewPerson->name, "alumno itesm");
        aNewPerson->day = 1*i;
        aNewPerson->month = 2*i;
        aNewPerson->year = 1985+i;
        INIT_LIST_HEAD(&aNewPerson->list);
        /* agrega un nuevo nodo a mylist */
        list_add_tail(&(aNewPerson->list), &(personList.list));
    }
    printk(KERN_INFO "Recorre la lista para cada elemento m");
    list_for_each_entry(aPerson, &personList.list, list) {
        //access the member from aPerson
        printk(KERN_INFO "Persona: %s; dia: %d; mes: %d; ano: %d", aPerson->name, aPerson->day, aPerson->month, aPerson->year);
    }
    printk(KERN_INFO "n");

    return 0;
}

void cleanup_module() {
    struct Person *aPerson, *tmp;
    printk(KERN_INFO "kernel module unloaded.n");
    printk(KERN_INFO "deleting the list using list_for_each_entry_safe()n");
    list_for_each_entry_safe(aPerson, tmp, &personList.list, list){
         printk(KERN_INFO "freeing node %sn", aPerson->name);
         list_del(&aPerson->list);
         kfree(aPerson);
    }
}

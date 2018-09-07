#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Laboratorio2ListasLigadas");
MODULE_AUTHOR("LuisEscobar/A01206734");

struct birthday {
    int day;
    int month;
    int year;
    char name[30];
    unsigned char gender;
    struct list_head list;

};

struct birthday personList;

int init_module() {
    struct birthday *aNewPerson, *person;
    unsigned int i;

    printk(KERN_INFO "Inicializar el modulo kernel");
    INIT_LIST_HEAD(&personList.list);    //or LIST_HEAD(mylist);

    /* adding elements to mylist */
    for(i=0; i<8; ++i){
        aNewPerson = kmalloc(sizeof(*aNewPerson), GFP_KERNEL);
	if(i%2 == 0 ){
		 strcpy(aNewPerson->name, "Luis Escobar");
	}
	else{
		strcpy(aNewPerson->name, "Jorge Hernandez");
	}
        
        aNewPerson->day = 1*i;
        aNewPerson->month = 9;
        aNewPerson->year= 1994 + i;
        aNewPerson->gender = 1;
        INIT_LIST_HEAD(&aNewPerson->list);
        /* add the new node to mylist */
        list_add_tail(&(aNewPerson->list), &(personList.list));
    }
    printk(KERN_INFO "Moviendose de la lista a traves de list_for_each_entry()n");
    list_for_each_entry(person, &personList.list, list) {
        //access the member from person
        printk(KERN_INFO "Persona: %s; dia: %d; mes:%d; anio:%d; genero: %s", person->name, person->day,person->month,person->year, person->gender==0?"Female":"Hombre");
    }
    //printk(KERN_INFO "n");

    return 0;
}

void cleanup_module() {
    struct birthday *person, *tmp;
    printk(KERN_INFO "Modulo del kernel no cargado.n");
    printk(KERN_INFO "Borrando la lista usando list_for_each_entry_safe()n");
    list_for_each_entry_safe(person, tmp, &personList.list, list){
         printk(KERN_INFO "Liberando nodo %sn", person->name);
         list_del(&person->list);
         kfree(person);
    }
}

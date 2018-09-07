#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

/* This function is called when the module is loaded. */
	static LIST_HEAD(birthday_list);
		struct birthday{
		int day;
		int month;
		int year;
		struct list_head list;//referencia al encabezado de la lista usadno el macro LIST_HEAD();
	};

	int simple_init(void){



	struct birthday *person[5];
	int i;

	for (i = 0; i < 5 ; i++){
		person[i] = kmalloc(sizeof(*person), GFP_KERNEL);//GFP_KERNEL indica la asignación rutinaria de memoria del kernel
		person[i]->day = 20+i;
		person[i]->month = 5+i;
		person[i]->year = 1995*(i+1);
		INIT_LIST_HEAD(&person[i]->list);//inicializa el campo lista en la estructura birthday 
		list_add_tail(&person[i]->list, &birthday_list);//agrega la instancia final a la lista del kernel		
	}
	struct birthday *ptr;
		
	list_for_each_entry(ptr, &birthday_list, list){//recorre la lista recibe (apuntador a la estructura que se recorre, apuntador al inicio de la lista que se recorre, variable que contiene a la estructura list_head)
		printk(KERN_INFO"Birthday mm/dd/yyyy:  %i %i %i\n", ptr->month, ptr->day, ptr->year);
	    printk(KERN_INFO "Loading Module\n");
	}
    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {

	struct birthday *ptr, *next;

	list_for_each_entry_safe(ptr, next, &birthday_list, list){
		
		list_del(&ptr->list);
		printk(KERN_INFO "Removing Module jiji\n");
		kfree(ptr);

	}
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


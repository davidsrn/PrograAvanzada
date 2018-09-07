#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/printk.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

static LIST_HEAD(birthday_list);


int birth_init(void)
{
	printk( KERN_INFO "Entrada de Birthday \n");

	struct birthday *person, *alonso, *beto, *carlos, *daniel, *efren;
	struct birthday *ptr;

	person = kmalloc(sizeof(*person),GFP_KERNEL);
	alonso = kmalloc(sizeof(*alonso),GFP_KERNEL);
	beto = kmalloc(sizeof(*beto),GFP_KERNEL);
	carlos = kmalloc(sizeof(*carlos),GFP_KERNEL);
	daniel = kmalloc(sizeof(*daniel), GFP_KERNEL);
	efren = kmalloc(sizeof(*efren), GFP_KERNEL);


	person->day=2;
	alonso -> day = 5;
	beto -> day = 26;
	carlos -> day = 4;
	daniel -> day = 22;
	efren -> day = 17;

	person->month=8;
	alonso -> month = 12;
	beto -> month = 7;
	carlos -> month = 2;
	daniel -> month = 10;
	efren -> month = 5;

	person->year=1995;
	alonso -> year = 1996;
	beto -> year = 1998;
	carlos -> year = 1975;
	daniel -> year = 1965;
	efren -> year = 1999;

	INIT_LIST_HEAD(&person->list);
	INIT_LIST_HEAD(&alonso->list);
	INIT_LIST_HEAD(&beto->list);
	INIT_LIST_HEAD(&carlos->list);
	INIT_LIST_HEAD(&daniel->list);
	INIT_LIST_HEAD(&efren->list);

	list_add_tail(&person->list,&birthday_list);
	list_add_tail(&alonso->list,&birthday_list);
	list_add_tail(&beto->list,&birthday_list);
	list_add_tail(&carlos->list,&birthday_list);
	list_add_tail(&daniel->list,&birthday_list);
	list_add_tail(&efren->list,&birthday_list);

	list_for_each_entry(ptr, &birthday_list,list)
	{
		printk( KERN_INFO "%i - %i - %i \n",ptr ->day, ptr-> month, ptr-> year);
	}

	printk( KERN_INFO "Fin de la lista\n");

	return 0;
}

void birth_exit(void){

	printk(KERN_INFO "Salida de  Birthday \n");

	struct birthday *ptr;
	struct birthday *next;

	list_for_each_entry_safe(ptr, next, &birthday_list,list)
	{
		list_del( &ptr ->list);
		kfree(ptr);
	}
}

module_init( birth_init );
module_exit( birth_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday list Module");
MODULE_AUTHOR("SGG");

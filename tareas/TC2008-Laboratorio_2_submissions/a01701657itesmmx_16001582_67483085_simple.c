#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Jose Pablo Prado Ayala A01701657");

struct birthday {
	int day ;
	int month ;
	int year ;
	struct list_head list ;
};

static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
int simple_init(void)
{
	int i,j;

	struct birthday *person, *nextPerson;

	for(i=0;i<5;i++){
		nextPerson = vmalloc(sizeof(*nextPerson));
		nextPerson->day = (i*1234)%30;
		nextPerson->month =(i*14)%12;
		nextPerson->year = (2018-i);
		INIT_LIST_HEAD(&nextPerson->list);
		list_add_tail(&(nextPerson->list), &birthday_list);
	}
	j=1;
	list_for_each_entry(person, &birthday_list, list) {
        	printk(KERN_INFO "name: person%i day: %i; month: %i; year: %i\n", j, person->day, person->month, person->year);
		j++;
    	}
	
	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	struct birthday *person, *tmp;
	int i=1;
	list_for_each_entry_safe(person, tmp, &birthday_list, list){
		printk(KERN_INFO "deleting person%i", i);
		list_del(&person->list);
		vfree(person);
		i++;
    	}
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );







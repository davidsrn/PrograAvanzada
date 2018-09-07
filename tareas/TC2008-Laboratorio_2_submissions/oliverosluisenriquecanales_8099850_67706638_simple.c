#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h> 

static LIST_HEAD(birthday_list);


struct birthday{
int day;
int month;
int year;
struct list_head list;
};

/*This function is called when the module is loaded*/
int simple_init(void){
	struct birthday *person,*person2,*person3,*person4,*person5, *ptr;

	person = vmalloc(sizeof(*person),GFP_KERNEL);
	person -> day = 2;
	person -> month =8;
	person -> year = 1995;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

	person2 = vmalloc(sizeof(*person2),GFP_KERNEL);
	person2 -> day=3;
	person2 -> month=9;
	person2 -> year=1994;
	list_add_tail(&person2->list,&birthday_list);

	person3 = vmalloc(sizeof(*person3),GFP_KERNEL);
	person3 -> day =4;
	person3 -> month = 9;
	person3 -> year = 1993;
	list_add_tail(&person3 -> list, &birthday_list);

	person4 = vmalloc(sizeof(*person4),GFP_KERNEL);
	person4 -> day =5;
	person4 -> month = 10;
	person4 -> year = 1992;
	list_add_tail(&person4 -> list, &birthday_list);

	person5 = vmalloc(sizeof(*person5),GFP_KERNEL);
	person5 -> day =6;
	person5 -> month = 11;
	person5 -> year = 1991;
	list_add_tail(&person5 -> list, &birthday_list);

	list_for_each_entry(ptr, &birthday_list,list){
		printk(KERN_INFO "%i%i%i",ptr->day,ptr->month,ptr->year);
	}

 printk(KERN_INFO "Loading Module\n");
       return 0;



}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");


struct birthday *ptr,*next;

list_for_each_entry_safe(ptr,next,&birthday_list, list){
	list_del(&ptr->list);
	vfree(ptr);
}
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


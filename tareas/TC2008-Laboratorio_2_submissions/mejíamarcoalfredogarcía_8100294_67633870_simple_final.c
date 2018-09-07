#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

//Definition of birthday structure
struct birthday{
int day;
int month;
int year;
struct list_head list;
};
//Declaration of birthday structure object
static LIST_HEAD(birthday_list);


/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
	//Definition of instances
	struct birthday *person,*person2,*person3,*person4,*person5;
	//Creation of birthday_list instances
	person =  kmalloc(sizeof(*person),GFP_KERNEL);
	person->day=2;
	person->month=8;
	person->year=1995;
	INIT_LIST_HEAD(&person->list);

	person2=kmalloc(sizeof(*person2),GFP_KERNEL);
	person2->day=3;
	person2->month=8;
	person2->year=1996;
	INIT_LIST_HEAD(&person2->list);

	person3=kmalloc(sizeof(*person3),GFP_KERNEL);
	person3->day=4;
	person3->month=9;
	person3->year=1996;
	INIT_LIST_HEAD(&person3->list);

	person4=kmalloc(sizeof(*person4),GFP_KERNEL);
	person4->day=5;
	person4->month=10;
	person4->year=1997;
	INIT_LIST_HEAD(&person4->list);

	person5=kmalloc(sizeof(*person5),GFP_KERNEL);
	person5->day=6;
	person5->month=11;
	person5->year=1998;
	INIT_LIST_HEAD(&person5->list);

	//Adding instances to the list
	list_add_tail(&person->list,&birthday_list);
	list_add_tail(&person2->list,&birthday_list);
	list_add_tail(&person3->list,&birthday_list);
	list_add_tail(&person4->list,&birthday_list);
	list_add_tail(&person5->list,&birthday_list);

	//Going through the list
	struct birthday *ptr;

	list_for_each_entry(ptr,&birthday_list,list){
		printk("person %d %d %d\n", ptr->day,ptr->month,ptr->year); 
	}
       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");

	//Deleting structure element
	struct birthday *ptr,*next;
	list_for_each_entry_safe(ptr,next,&birthday_list,list){
	lista_del(&ptr->list);
	kfree(ptr);
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


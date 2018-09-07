#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>

struct birthday { 
    int day; 
    int month; 
    int year; 
    struct list_head list; 
}

static LIST_HEAD(birthday_list);
struct birthday *person;
struct birthday *person1;
struct birthday *person2;
struct birthday *person3;
struct birthday *person4;

void createPerson(struct birthday *person){
    person = kmalloc(sizeof(*person), GFP_KERNEL); 
    person ->day = 2; 
    person ->month = 8; 
    person ->year = 1995; 
}
/* This function is called when the module is loaded. */
int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");
    createPerson(person);
    INIT_LIST_HEAD(&person ->list);
    createPerson(person1);
    createPerson(person2);
    createPerson(person3);
    createPerson(person4);
    list_add_tail(&person1 ->list , &birthday_list);
    list_add_tail(&person2 ->list , &birthday_list);
    list_add_tail(&person3 ->list , &birthday_list);
    list_add_tail(&person4 ->list , &birthday_list);
    printk("%i %i %i\n", person -> day, person -> month, person -> year);
    printk("%i %i %i\n", person1 -> day, person1 -> month, person1 -> year);
    printk("%i %i %i\n", person2 -> day, person2 -> month, person2 -> year);
    printk("%i %i %i\n", person3 -> day, person3 -> month, person3 -> year);
    printk("%i %i %i\n", person4 -> day, person4 -> month, person4 -> year);
   

    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
    list_del(person);
    list_del(person1);
    list_del(person2);
    list_del(person3);
    list_del(person4);
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


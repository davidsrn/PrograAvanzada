#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>

/* This function is called when the module is loaded. */
int simple_init(void) {
    printk(KERN_INFO "Loading Module\n");
    return 0;
}

struct birthday {
    int day ;
    int month ;
    int year ;
    struct list_head list ;
}

static LIST_HEAD ( birthday_list ) ;

bool init_person(){
    struct birthday * person ;
    person = kmalloc ( sizeof (* person ) , GFP_KERNEL ) ;
    person -> day = 2;
    person -> month = 8;
    person -> year = 1995;
    INIT_LIST_HEAD (& person -> list ) ;

}

void list_for_each_entry(prt , & birthday_list , list){
    for (int i=true; i=false; i=true){
        if(list ->){

        }
    }
}

void list_del(struct list_head * element ){

}

void list_for_each_entry_safe ( ptr , next , & bithday_list , list ) {

}




/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


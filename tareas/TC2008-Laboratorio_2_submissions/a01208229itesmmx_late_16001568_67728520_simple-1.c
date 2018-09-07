#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include<linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linked list");
MODULE_AUTHOR("Alejandro Ochoa Garcia A01208229");

struct birthday{
    unsigned int day;
    unsigned int month;
    unsigned int year;
    struct list_head list; /* kernel's list structure */
};

struct birthday birthdayList;

/* This function is called when the module is loaded. */
int init_module(){

    struct birthday *aNewBirthday, *aBirthday;

    unsigned int i;

    printk(KERN_INFO "Initialize kernel module");

    INIT_LIST_HEAD(&birthdayList.list);; /*or LIST_HEAD(birthdayList); */

    /* adding elements to mylist */
    for(i=0;i<5;i++){

        aNewBirthday = kmalloc(sizeof(*aNewBirthday), GFP_KERNEL);
        aNewBirthday->day = 12;
        aNewBirthday->month = 4;
        aNewBirthday->year = 1998+i;

        INIT_LIST_HEAD(&aNewBirthday->list);

        /* add the new node to mylist */
        list_add_tail(&(aNewBirthday->list), &(birthdayList.list));

    }

    printk(KERN_INFO "Traversing the list using list_for_each_entry()n");

    list_for_each_entry(aBirthday, &birthdayList.list, list){

        /*access the member from aBirthday*/
        printk(KERN_INFO "Birthday: %d; month: %d; year: %d", aBirthday->day, aBirthday->month, aBirthday->year);

    }

    printk(KERN_INFO "n");

    return 0;

}

/* This function is called when the module is removed. */
void cleanup_module() {

	struct birthday *aBirthday, *tmp;

	printk(KERN_INFO "Kernel module unloaded");
    printk(KERN_INFO "Deleting the list using list_for_each_entry_safe()");

    list_for_each_entry_safe(aBirthday, tmp, &birthdayList.list, list){
         printk(KERN_INFO "Freeing node %d", aBirthday->year);
         list_del(&aBirthday->list);
         kfree(aBirthday);
    }


}

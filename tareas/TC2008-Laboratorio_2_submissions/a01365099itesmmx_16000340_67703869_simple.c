# include < linux / init .h >
# include < linux / module .h >
# include < linux / kernel .h >
/* This function is called when the module is loaded . */
int simple_init ( void )
{
 printk ( KERN_INFO " Loading Module \ n " ) ;
 
 static LIST_HEAD ( birthday_list ) ;

 struct birthday {
  int day ;
  int month ;
  int year ;
  struct list_head list ;
 }

 struct birthday * person ;
 for(i=0;i<5; i++){
  person = kmalloc ( sizeof (* person ) , GFP_KERNEL ) ;
  person -> day = 2;
  person -> month = 8;
  person -> year = 1995;
  INIT_LIST_HEAD (& person -> list ) ;

  list_add_tail (& person - > list , & birthday_list ) ;
 }

 struct birthday * ptr ;
 list_for_each_entry ( prt , & birthday_list , list ) {
  printk(KERN_INFO "Birthday: day: %d; month: %d"; year: %d, ptr->day, ptr->month, ptr->year);

  /* en cada iteraciOn , ptr indica cuAl es */
  /* el nodo actual de la lista */
 }

 list_del ( struct list_head * element ) ;

 struct birthday * ptr , * next ;

 list_for_each_entry_safe ( ptr , next , & bithday_list , list ) {
  /* prt apunta al nodo actual de la lista */
 
  list_del (& prt -> list ) ;
  kfree ( ptr ) ;
 } 
 return 0;
}

/* This function is called when the module is removed . */
void simple_exit ( void ) {
 printk ( KERN_INFO " Removing Module \ n " ) ;
}
/* Macros for registering module entry and exit points . */
module_init ( simple_init ) ;
module_exit ( simple_exit ) ;
MODULE_LICENSE ( " GPL " ) ;
MODULE_DESCRIPTION ( " Simple Module " ) ;
MODULE_AUTHOR ( " SGG " ) ;
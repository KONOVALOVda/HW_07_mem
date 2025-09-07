#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/ktime.h>

#define ALLOC_SIZE 1024 * 1024 // 1 MB

static void *kmem_ptr;

static int __init kmalloc_init(void)
{
    ktime_t start, end;
    printk(KERN_INFO "kmalloc: Запуск модуля\n");
    
    start = ktime_get();
    kmem_ptr = kmalloc(ALLOC_SIZE, GFP_KERNEL);
    end = ktime_get();

    if (!kmem_ptr) {
        printk(KERN_ERR "kmalloc: FAIL\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "kmalloc: SUCCESS\n");
    printk(KERN_INFO "kmalloc: %d byte, %lld ns, type: физическая\n", ALLOC_SIZE, ktime_to_ns(ktime_sub(end, start)));

    return 0;
}

static void __exit kmalloc_exit(void)
{
    kfree(kmem_ptr);
    printk(KERN_INFO "kmalloc: Модуль выгружен, память освобождена\n");
}

module_init(kmalloc_init);
module_exit(kmalloc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Пример kmalloc");

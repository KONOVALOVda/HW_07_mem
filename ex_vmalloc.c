#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/vmalloc.h>
#include <linux/ktime.h>

#define ALLOC_SIZE 16*1024*1024 // 16 MB

static void *vmem_ptr;

static int __init vmalloc_init(void)
{
    ktime_t start, end;
    printk(KERN_INFO "vmalloc: Запуск модуля\n");

    start = ktime_get();
    vmem_ptr = vmalloc(ALLOC_SIZE);
    end = ktime_get();

    if (!vmem_ptr) {
        printk(KERN_ERR "vmalloc: FAIL\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "vmalloc: SUCCESS\n");
    printk(KERN_INFO "vmalloc: %d byte, %lld ns, type: виртуальная\n", ALLOC_SIZE, ktime_to_ns(ktime_sub(end, start)));

    return 0;
}

static void __exit vmalloc_exit(void)
{
    vfree(vmem_ptr);
    printk(KERN_INFO "vmalloc: Модуль выгружен, память освобождена\n");
}

module_init(vmalloc_init);
module_exit(vmalloc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Пример vmalloc");

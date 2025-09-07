#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/ktime.h>

static struct page *pg;

static int __init get_page_init(void)
{
    ktime_t start, end;
    printk(KERN_INFO "get_page: Запуск модуля\n");

    start = ktime_get();
    pg = alloc_page(GFP_KERNEL);
    end = ktime_get();

    if (!pg) {
        printk(KERN_ERR "get_page: FAIL\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "get_page: SUCCESS, %lld ns, type: физическая\n", ktime_to_ns(ktime_sub(end, start)));

    return 0;
}

static void __exit get_page_exit(void)
{
    __free_page(pg);
    printk(KERN_INFO "get_page: Модуль выгружен, память освобождена\n");
}

module_init(get_page_init);
module_exit(get_page_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Пример get_page");

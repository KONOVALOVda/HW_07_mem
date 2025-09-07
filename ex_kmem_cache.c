#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/ktime.h>

struct my_obj {
    int a;
    int b;
    char buf[64];
};

static struct kmem_cache *my_cache;
static struct my_obj *obj;

static int __init kmem_cache_init(void)
{
    ktime_t start, end;
    printk(KERN_INFO "kmem_cache: Запуск модуля\n");

    my_cache = kmem_cache_create("my_cache", sizeof(struct my_obj), 0, SLAB_HWCACHE_ALIGN, NULL);
    if (!my_cache) {
        printk(KERN_ERR "kmem_cache: FAIL\n");
        return -ENOMEM;
    }

    start = ktime_get();
    obj = kmem_cache_alloc(my_cache, GFP_KERNEL);
    end = ktime_get();

    if (!obj) {
        printk(KERN_ERR "kmem_cache: FAIL при выделении объекта\n");
        kmem_cache_destroy(my_cache);
        return -ENOMEM;
    }

    printk(KERN_INFO "kmem_cache: SUCCESS\n");
    printk(KERN_INFO "kmem_cache: %zu byte, %lld ns, type: физическая\n", sizeof(struct my_obj), ktime_to_ns(ktime_sub(end, start)));

    return 0;
}

static void __exit kmem_cache_exit(void)
{
    kmem_cache_free(my_cache, obj);
    kmem_cache_destroy(my_cache);
    printk(KERN_INFO "kmem_cache: Модуль выгружен, память освобождена\n");
}

module_init(kmem_cache_init);
module_exit(kmem_cache_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Пример kmem_cache");

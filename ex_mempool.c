#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mempool.h>
#include <linux/slab.h>
#include <linux/ktime.h>

#define POOL_SIZE 10

static mempool_t *my_pool;
static void *objs[POOL_SIZE];

static int __init mempool_init(void)
{
    int i;
    ktime_t start, end;
    printk(KERN_INFO "mempool: Запуск модуля\n");

    my_pool = mempool_create(POOL_SIZE, kmalloc, kfree);
    if (!my_pool) {
        printk(KERN_ERR "mempool: FAIL при создании пула\n");
        return -ENOMEM;
    }

    for (i = 0; i < POOL_SIZE; i++) {
        start = ktime_get();
        objs[i] = mempool_alloc(my_pool, GFP_KERNEL);
        end = ktime_get();
        if (!objs[i]) {
            printk(KERN_ERR "mempool: FAIL при аллокации %d\n", i);
        } else {
            printk(KERN_INFO "mempool: SUCCESS %d, %lld ns\n", i, ktime_to_ns(ktime_sub(end, start)));
        }
    }

    return 0;
}

static void __exit mempool_exit(void)
{
    int i;
    for (i = 0; i < POOL_SIZE; i++) {
        if (objs[i])
            mempool_free(objs[i], my_pool);
    }
    mempool_destroy(my_pool);
    printk(KERN_INFO "mempool: Модуль выгружен, память освобождена\n");
}

module_init(mempool_init);
module_exit(mempool_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Пример mempool");

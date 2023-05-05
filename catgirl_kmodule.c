#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/slab.h>
#include <linux/string.h>

#define DEVICE_NAME "catgirl"
#define MEOW_ATTR_NAME "meow"
#define NAME_ATTR_NAME "name"

static struct kobject *catgirl_kmodule;
static const char * name = NULL;

static ssize_t meow_attribute_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    if (name)
    {
        return sprintf(buf, "%s: Nya!\n%s 可爱!\n", name, name);
    }
    else
    {
        return sprintf(buf, "Nya!\n");
    }
}

static ssize_t meow_attribute_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    return count;
}

static ssize_t name_attribute_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    if (name)
    {
        return sprintf(buf, "%s", name);
    }
    else
    {
        return sprintf(buf, "(not set yet)\n");
    }
}

static ssize_t name_attribute_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    if (name)
    {
        kfree(name);
    }
    name = kmalloc(count, GFP_KERNEL);
    if (!name)
    {
        return -ENOMEM;
    }
    memcpy((void *)name, buf, count);

    return count;
}

static struct kobj_attribute meow_attribute = __ATTR(meow, 0644, meow_attribute_show, meow_attribute_store);
static struct kobj_attribute name_attribute = __ATTR(name, 0644, name_attribute_show, name_attribute_store);

static int __init catgirl_module_init(void)
{
    int retval;
    catgirl_kmodule = kobject_create_and_add(DEVICE_NAME, NULL);
    if (!catgirl_kmodule)
    {
        pr_err("Failed to create kobject\n");
        return -ENOMEM;
    }

    retval = sysfs_create_file(catgirl_kmodule, &meow_attribute.attr);
    if (retval)
    {
        pr_err("Failed to create sysfs file\n");
        kobject_put(catgirl_kmodule);
        return retval;
    }

    retval = sysfs_create_file(catgirl_kmodule, &name_attribute.attr);
    if (retval)
    {
        pr_err("Failed to create sysfs file\n");
        kobject_put(catgirl_kmodule);
        return retval;
    }

    pr_info("%s module loaded\n", DEVICE_NAME);
    return 0;
}

static void __exit catgirl_module_exit(void)
{
    sysfs_remove_file(catgirl_kmodule, &meow_attribute.attr);
    sysfs_remove_file(catgirl_kmodule, &name_attribute.attr);
    kobject_put(catgirl_kmodule);
    pr_info("%s module unloaded\n", DEVICE_NAME);
}

module_init(catgirl_module_init);
module_exit(catgirl_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cocoa");
MODULE_DESCRIPTION("A simple sysfs module for catgirl");


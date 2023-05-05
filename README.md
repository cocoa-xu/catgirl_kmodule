# catgirl_kmodule
wwwwwwwwwwww

Maybe this is an example repo for how to write a simply kernel module? wwwww

### Install dependencies
```shell
sudo apt-get install libudev-dev linux-headers-$(uname -r) gcc
```

### Compile
```shell
git clone https://github.com/cocoa-xu/catgirl_kmodule
cd catgirl_kmodule
make
```

### Enable kernel module
```shell
sudo insmod catgirl_kmodule.ko
```

### Usage
```shell
# meow
cat /sys/catgirl/meow

# set name
echo -n "Cocoa" | sudo tee /sys/catgirl/name

# meow (again)
cat /sys/catgirl/meow
```

### Disable kernel module
```shell
sudo rmmod catgirl_kmodule
```

# File parsing and editing - C Program
### Introduction
This is a function which gets data from assigned structure, parses the file and  and edit the files. I have created this function for wireless config file.
### Features
* Written in C

### What's included
```
File-parsing-editing/
   |--wifi.d
	|-- wifi_ap+sta
   |--trial.c
```

### Application

1. You can edit this function and then can be used anywhere to edit the file 

2. Here, using structure format. Also, can be applied using normal array or pointer

3. This function can be use directly in linux based OS, such as: Ubuntu, OpenWRT

4. If you are creating program or website, that asks user to select wif mode(access point or station or both mode), wifi ssid and password; You can simply implement this program in your base code on your local device and provide information using portal or website. 


### how to test (for linux user)

* Edit code according to your requirement
* Open terminal
* type `gcc -o fiename` (here filename is trial.c)
* Run by typing `./a.out` (please refer gcc/linux manual for changing name of object file -- your device may not have gcc so install gcc befor using it)
* check your file

#### Note

Here, wifi_ap+sta is provided as an example target file.
Windows' user can also follow above test if they have installed gcc -terminal

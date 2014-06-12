# Running Custom Sketches

You can run your own sketches stored in a folder on your home directory (or anywhere else, for that matter) by creating a Makefile with the following tempelate:

```
path/to/Userspace-Arduino/arduino-makefile/arduino-mk/Userspace.mk
```

Replace the above path with the correct path and save the file as "Makefile".

You can simply save your sketch in the same folder.


To compile:

```
make
```

To upload:

```
make upload
```

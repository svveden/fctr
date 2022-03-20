## FCTR: Enumerated Folder Creator 

# v 0.2.2 adds ranges!

This simple C script is for creating/deleting multiple folders of the same name that are enumerated from 1 to n in the same directory.

For example, this script could create a list of folders as such:

```
folder_01, folder_02, folder_n
```
using the command: 
```
fctr -c n folder
```
or, delete a list of folders as such:

~~folder_01, folder_02, folder_n~~

using the command:
```
fctr -d n folder
```

## Installation

```sh
git clone https://github.com/svveden/fctr
bash ./fctr/install.sh
```

## Usage
```
flags: 
-c    Create folders.
-d    Delete folders.
```
```
command: fctr -flag number_of_folders name_of_folders
# folders are created with name_of_folder + _number, so no need to add '_' after the name
```
Folder ranges can now be added as a 4th argument as such:
```
fctr -c number_of_folders name_of_folders range 
# i.e. create n folders from range to n
```
So, for example, running:
```
fctr -c 10 folder 5
```
Will create the following:
```
folder_05, folder_06, folder_07, folder_08, folder_09, folder_10
```
The same can be done for deleting as well, but you must start the range at a folder number that exists.
Also, deleting will stop at the first folder it can't find, no skipping folders (yet)!

## Notes

!!Folder names cannot exceed 250 chars, as Linux/OSX only allow folder names up to 255 chars!!

This program/script is entirely written in C and mainly exists for me to get to know git and repo cloning! 

## FCTR: Enumerated Folder Creator 

This simple C script is for creating multiple folders of the same name that are enumerated from 1 to n in the same directory.

For example, this script could create a list of folders as such:

```
folder_01, folder_02, folder_0n
using the command: fctr n folder
```

## Installation

```sh
git clone https://github.com/svveden/fctr
bash ./fctr/install.sh
```

## Usage
```
fctr number_of_folders_to_create name_of_folder 
# folders are created with name_of_folder + _number, so no need to add '_' after the name
```

## Notes

This script/program is written in C and is definitely nothing ground breaking, but I wanted to create this repo to try and learn/understand creating scripts that are able to be ripped from github using git and installed on other machines. So, I made this very simple script to speed up some formatting I was doing for my other repos and decided to try and make it portable.

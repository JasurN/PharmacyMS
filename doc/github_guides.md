## Introduction
1. First of all you should create github account. 
1. Connect to Jasurn, so that you will be added to github repository.
1. Check your mail for invintation and accept

## Contributing
1. If you are using linux, you should install git by `sudo apt-get git`
1. Then in that terminal you should generate ssh key by `ssh-keygen -t rsa -b 4096 -C "your_email@example.com"`
1. Then you should copy what is inside in ./ssh/id_rsa.pub by `cat .ssh/id_rsa.pub `
1. Then you should add this ssh key to your **github account** by account -> settings -> ssh and gpg keys -> click new ssh key -> add any title and your copied but cat ssh key
1. Then open Clion and in terminal make directory for git repository by `mkdir your_git_rep` 
1. Then git clone repository by `git clone git@github.com:JasurN/PharmacyMS.git directory_name`
1. Signin in Clion to your Github account

## Working rules
1. For any changes please make new branch by `git branch name_of_branch`
1. You can see branches by `git branch`
1. You can checkout(change from master to your branch) by `git checkout name_of_branch`
1. Feel free to add. 
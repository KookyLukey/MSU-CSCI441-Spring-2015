CSCI441 Spring 2015
-------------------

This repository is where all your assignments will be provided. You will
import this repository into your own private bit bucket repository, where you
will make your additions to the code base. The reason for bit bucket is public 
repositories are free on github, whereas private ones are free on bit bucket.

I will be adding assignments to this repository throughout the semester so you will need to follow the
instructions below in order to keep your repository up-to-date, while also being
able to push changes up to your own personal repository.

Importing to bitbucket.org
--------------------------

First, you'll need a bitbucket account, so [sign up here](https://bitbucket.org/account/signup/).
Then you'll need to import this repository into your own private repository.
Start by going [here](https://bitbucket.org/repo/import). In the URL field, paste
in the url to this repository: 

https://github.com/jallwine/MSU-CSCI441-Spring-2015

Once the URL field loses focus, the Name field should be filled in. You can change
it if you like, as well as fill in a description. Leave 'This is a private repository'
checked, so no one else has access to it (it's also free when it's private on bitbucket).
Then click 'Import repository' at the bottom.

Share your repository
---------------------

In order to grade your assignments, I'll need access to your repository. You can
invite me to your newly created repository on the right-hand side where it says
'Invite users to this repo'. Click the 'Send invitation' button and add the user
jallwine. All I need is permission to read your repository (so not write or admin).
Then click 'Share'.

Install Git
---------------------

Now we need to make sure git is installed. There are a number
of git GUI clients, including bitbucket's [SourceTree](https://www.atlassian.com/software/sourcetree/overview),
or [others](http://git-scm.com/downloads/guis).
I'll leave you to figure out your GUI of choice on your own if you like. 
I always stick to the command line when I can, so that's what I'll be showing
you how to do. In a terminal run the following:

    git --version 

The latest version is git 2.2.1, so if you get an error or a version less than
that you may need to [download and install git](http://git-scm.com/downloads). 
If you've never used git before you might want to [read up on the docs](http://git-scm.com/doc), 
or go through the basics with [Try Git](try.github.com).

Clone your repository
---------------------

To download your repository so it's ready for modifications, we need to clone it.
Once git is installed, run the following command with &lt;repo url&gt; replaced with
the url to your repository (shown in the upper right of the Overview page on bit bucket).
It'll look something like https://jallwine@bitbucket.org/jallwine/msu-csci441-spring-2015.git.

    git clone <repo url>

It'll ask for your bit bucket password. You'll have to enter your password every time you
want to push changes up to bit bucket or pull changes down, unless you set up SSH keys (go to
Manage Account in the top right most menu, then under security is SSH keys).

How to pull the latest assignments
----------------------------------

I'll be adding assignments here throughout the semester so you'll need to add
this repository as a remote that you can pull changes from. Make sure you cd into
your repository, something like (depending on what you named it):

    cd msu-csci441-spring-2015

Then let's list what remotes we currently have:

    git remote -v

You should see two entries for your bit bucket repository, one (fetch) and one (push). When
you use `git push` or `git pull`, by default you'll push or pull to/from that url. We want to
add another entry that we can explicitly pull from to merge in assignments as I add them. To
do that, run the following:

    git remote add csci441 https://github.com/jallwine/MSU-CSCI441-Spring-2015.git

Now if you run the `git remote -v` command you'll see two addition entries. You won't have permission
to push to this one, but you will be able to pull new assignments by running the following:

    git pull csci441 master

Install Qt
----------

All assignments and labs will be written in C++ using OpenGL and Qt. Qt is a cross platform
UI framework. There are both commercial and open source licenses for Qt.  We'll be using the 
open source version, which can be downloaded [here](http://www.qt.io/download-open-source/).
Follow the instructions for installation on your platform.

Build Lab 1
-----------

Once you have Qt installed, try compiling and running the provided lab 1 code. Qt projects
are organized using project files (.pro files). The qt command `qmake` can generate a Makefile
(or an Xcode project, or a Visual Studio project). I like to stick to using a Makefile so I can
stay in a terminal:  

    cd lab1
    qmake
    make
    ./lab1

It should print "Output triangle.jpg" to the terminal and triangle.jpg should be a blank, black image (it's
your job to make it output a triangle). On the lab computers (in EPS 254, and others), multiple versions of qt are 
installed on Fedora. To use the right version of qmake use `qmake-qt5`.

How To Submit Your Work
-----------------------

Once you start making changes to your code, you'll want to commit those changes and push them back up
to the server. For every file you've changed or created, you'll want to run `get add <file name>`. This
stages the file for commit. You can think of staging a file as flagging that you want to save it in your
next commit. Once you've staged every file that you want to commit type:

    git commit -m "a short description of what you're committing"

It can be handy to see what files have been changed. To see what changes have been made you can 
use `git status`. `git status` will show you which files you've modified, which files are new 
and which files have been staged for commit. 

You can commit as many times as you want locally. When you're ready to submit all your commits up to the
server, where I can see them run:

    git push 

Now your changes are all on bitbucket where I can see them. Be sure to include everything necessary
to build and run your code! I recommend cloning your repository to another location (perhaps on the
lab machines) and building it to make sure you've remembered to include everything.

For labs, be sure to push your changes up
before demoing the lab to me in class. For programs, make sure your code is pushed before the deadline.
Once thing to be careful of is to not commit files that are generated by the build process (i.e. the
Makefile, the final executable, .o files, etc.). I've included a .gitignore file in the reposiotry that will
ignore most files that will be generated by your build processes, but you'll want to keep that in mind.

If you've cloned your repository in more than one location and have made changes to one of them and pushed
those changes up to the server, you can use `git pull` from the other location to bring it up to date.

More Git Basics
---------------

Git is a distributed version control system (VCS). When you cloned the repository above, you downloaded
every change that has ever been made to the repository. You can see each individual change by running the 
following:

    git log

You'll see a list of commits, which are changes to a set of files in your repository. Each commit looks
something like this (this is the first commit to your repository, made by me):

    commit 64b2f40ee1bfe685a301bbf912aeb87b46e5ca28
    Author: John Allwine <jallwine86@gmail.com>
    Date:   Sat Dec 27 16:49:04 2014 -0700

        added lab1

The first line shows the hash value for the commit. If you ever want to revert back to a specific commit
you can use `git checkout <hash value>`. In your repository, you can type the following to get to the very
first change ever made:

    git checkout 64b2f40ee1bfe685a301bbf912aeb87b46e5ca28

To get back to the lastest, you can run:

    git checkout master

For a more fully featured git cheat sheet go [here](https://training.github.com/kit/downloads/github-git-cheat-sheet.pdf).
The official git documentation is [here](http://git-scm.com/doc).

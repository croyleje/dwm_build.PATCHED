dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

Patches
-------
This build is heavily patched see the individual files for specifics.
- dwm-actualfullscreen-20211013-cb3f58a.diff
- dwm-alpha-20201019-61bb8b2.diff
- dwm-attachaside-6.3.diff
- dwm-cfacts-20200913-61bb8b2.diff
- dwm-fixborders-6.2.diff
- dwm-float-border-color-6.2.diff
- dwm-focusmaster-return-20210804-138b405.diff
- dwm-focusurgent-20160831-56a31dc.diff
- dwm-moveresize-6.2.diff
- dwm-smartborders-6.2.diff
- dwm-stacker-6.2.diff
- dwm-statuspadding-6.3.diff
- dwm-swallow-6.2.diff
- dwm-urgent-tag-6.2.diff (Manual patching required.)

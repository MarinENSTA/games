IMPORTANT : paths must be changed in snake_python.spec to current path (most likely not the same as mine)
Once it is done :
Just run
user@user$:~$ pyinstaller snake_python.spec
to get a fully autonomous executable version of this Snake Project.

TO REMEMBER (took me quite a while to figure):

- Pygame pre-implemented fonts will most likely make the executable crash. 
You need to add font file (.ttf) to snake_python.spec (and it's path) to make it work

- Any auxiliary file (font, image, etc) used in this python programm must be added to snake_python.spec.
This is in order to factor them in while processing pyinstaller and make the executable truly standalone/autonomous.
Any auxiliary file can't just be called by their name. In order to call them, you need to call : resource_path("YouFileName.filetype").
Doesn't work otherwise. See snake_game.py to read resource_parth() function. (Found on StackOverflow, works VERY WELL).

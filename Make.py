from subprocess import call
from platform import system
from sys import argv

argv.pop(0)

isRoot = "-r" in argv
if isRoot:
	argv.remove("-r")

if system() == "Windows":
	cmd = "bmptk-make " + " ".join(argv)
elif system() == "Linux":
	cmd = ("sudo " if isRoot else "") + "make " + " ".join(argv)

call(cmd.split(" "))

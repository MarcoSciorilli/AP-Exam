import numpy as np
import pylab as pl


# Container comparison plot
files = ["map_int", "u_map_int", "bst_int", "bst_int_b"]
labels = ["map", "unordered map", "bst", "balanced bst"]
colors = ["tab:cyan", "tab:orange", "tab:green", "tab:purple"]
N = np.loadtxt("results/map_int.txt")[:, 0]

for f, l, c in zip(files, labels, colors):
    line = np.loadtxt("results/"+f+".txt")[:, 1] / 1000
    pl.plot(N, line, label=l, color=c)

pl.xlabel("container size")
pl.ylabel("time to find 100 keys[us]")
pl.title("Comparison between containers")
pl.legend()
pl.savefig("results/container_comparison.png")
pl.show()


# Key types comparison plot
files = ["bst_int_b"]
labels = ["balanced bst"]
colors = ["tab:purple"]

for f, l, c in zip(files, labels, colors):
    line = np.loadtxt("results/"+f+".txt")[:, 1] / 1000
    pl.plot(N, line, label=l+" int", color=c)

    f = "results/"+f.replace("int", "double")+".txt"
    line = np.loadtxt(f)[:, 1:] / 1000
    pl.plot(N, line, "--", label=l+" double", color=c)

pl.xlabel("container size")
pl.ylabel("time to find 100 keys[us]")
pl.title("Comparison between key types")
pl.legend()
pl.savefig("results/key_comparison.png")
pl.show()

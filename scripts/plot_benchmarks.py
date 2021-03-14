import matplotlib.pyplot as plt
import json
import numpy as np
import re



def check_name(name, regex):
    if len(regex)==0:
        return True
    if re.findall(regex, name):
        return True
    return False


def read_info(fname, regex):
    f = open(fname, "r")
    json_data = json.load(f)
    f.close()
    data = {}
    data["names"] = []
    data["cpu_t"] = []
    data["real_t"] = []
    data["t_unit"] = json_data["benchmarks"][0]["time_unit"]
    for b_mark in json_data["benchmarks"]:
        if check_name(b_mark["name"], regex):
            data["names"].append(b_mark["name"])
            data["cpu_t"].append(b_mark["cpu_time"])
            data["real_t"].append(b_mark["real_time"])
    data["cpu_t"] = np.array(data["cpu_t"])
    data["real_t"] = np.array(data["real_t"])
    return data






import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-i', default="results.json",  help="input file [def = 'results.json']")
parser.add_argument("--norm", action="store_false", default=True, help="Normalize all times to the smallest [def=True]")
parser.add_argument("--real", action="store_true", default=False, help="Plot real time graph [def=False]")
parser.add_argument("--figsize", action="store", default="7 4", help="Figsize parameter [def = '7 4']")
parser.add_argument("--filter", action="store", default="", help="regex for peaking certain test names [def='' - take all]")
args = parser.parse_args()

fig_size = args.figsize.split()
fig_size[0] = int(fig_size[0])
fig_size[1] = int(fig_size[1])

data = read_info(args.i, args.filter)

if args.norm:
    data["cpu_t"] = data["cpu_t"]/min(data["cpu_t"]) 
    data["real_t"] = data["real_t"]/min(data["real_t"]) 
    data["t_unit"] = "a.u."




plt.figure(figsize=fig_size)
plt.grid(zorder=0)
plt.barh(data["names"], data["cpu_t"], zorder=3)
plt.xlabel("time, %s" % data["t_unit"])
plt.tight_layout()
plt.show()



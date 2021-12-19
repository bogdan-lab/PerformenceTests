import matplotlib.pyplot as plt
import argparse
import json
import numpy as np
import re


def check_name(name, regex):
    if len(regex) == 0:
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


def setup_parser(parser):
    parser.add_argument('-i', "--input", default="results.json",
                        help="input json file with results")
    parser.add_argument("--norm", action="store_true", default=False,
                        help="Sets whether graph should be plotted using "
                        "normalized times or not")
    parser.add_argument("--figsize", action="store", default="7 4",
                        help="Setting resultin figure size")
    parser.add_argument("--filter", action="store", default="",
                        help="Python regex for filtering which data to plot")


def plot_data(data, args):
    if args.norm:
        data["cpu_t"] = data["cpu_t"]/min(data["cpu_t"])
        data["real_t"] = data["real_t"]/min(data["real_t"])
        data["t_unit"] = "a.u."
    fig_size = args.figsize.split()
    fig_size[0] = int(fig_size[0])
    fig_size[1] = int(fig_size[1])
    plt.figure(figsize=fig_size)
    plt.grid(zorder=0)
    plt.barh(data["names"], data["cpu_t"], zorder=3)
    plt.xlabel("time, %s" % data["t_unit"])
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
            prog="Benchmark results plotter",
            description="Tool for selective plotting benchmark results from"
            " json file",
            formatter_class=argparse.ArgumentDefaultsHelpFormatter
            )
    setup_parser(parser)
    args = parser.parse_args()
    data = read_info(args.input, args.filter)
    plot_data(data, args)

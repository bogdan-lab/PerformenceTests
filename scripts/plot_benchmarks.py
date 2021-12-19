import matplotlib.pyplot as plt
import argparse
import json
import numpy as np
import re


def read_info(fname, regex):
    regex = re.compile(regex)
    with open(fname, "r") as f:
        json_data = json.load(f)
    data = {"names": [], "cpu_time": []}
    all_time_units = set()
    for b_mark in json_data["benchmarks"]:
        if regex.search(b_mark["name"]):
            data["names"].append(b_mark["name"])
            data["cpu_time"].append(b_mark["cpu_time"])
            all_time_units.add(b_mark["time_unit"])
    data["cpu_time"] = np.array(data["cpu_time"])
    if len(all_time_units) > 1:
        raise RuntimeError("There are different time units in the file")
    data["time_unit"] = all_time_units.pop()
    return data


def setup_parser(parser):
    parser.add_argument('-i', "--input", default="results.json", type=str,
                        help="input json file with results")
    parser.add_argument("--norm", action="store_true", default=False,
                        help="Sets whether graph should be plotted using "
                        "normalized times or not")
    parser.add_argument("--figsize", action="store", type=str, default="7 4",
                        help="Setting resulting figure size")
    parser.add_argument("--filter", action="store", default=".*", type=str,
                        help="Python regex for filtering which data to plot")


def plot_data(data, args):
    if args.norm:
        data["cpu_time"] = data["cpu_time"]/min(data["cpu_time"])
        data["time_unit"] = "a.u."
    fig_size = args.figsize.split()
    fig_size[0] = int(fig_size[0])
    fig_size[1] = int(fig_size[1])
    plt.figure(figsize=fig_size)
    plt.grid(zorder=0)
    plt.barh(data["names"], data["cpu_time"], zorder=3)
    plt.xlabel(f"time, {data['time_unit']}")
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

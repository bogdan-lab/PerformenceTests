import matplotlib.pyplot as plt
import argparse
import json
import numpy as np
import re
from collections import defaultdict


def read_info(fname, regex):
    regex = re.compile(regex)
    with open(fname, "r") as f:
        json_data = json.load(f)
    data = []
    all_time_units = set()
    for b_mark in json_data["benchmarks"]:
        if regex.search(b_mark["name"]):
            data.append(
                    {"name": b_mark["name"],
                     "cpu_time": b_mark["cpu_time"],
                     "time_unit": b_mark["time_unit"]}
                    )
            all_time_units.add(b_mark["time_unit"])
    if len(all_time_units) > 1:
        raise RuntimeError("There are different time units in the file")
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


def normalize_times(data):
    min_val = np.inf
    for el in data:
        min_val = min(min_val, el["cpu_time"])
    for i in range(len(data)):
        data[i]["cpu_time"] /= min_val
        data[i]["time_unit"] = "a.u."


def get_group_name(name, index):
    return name.split('/')[index]


def check_separate_groups(data, idx):
    groups = set()
    for el in data:
        groups.add(get_group_name(el["name"], idx))
    return len(groups) > 1


def find_separating_index(data):
    min_slash_num = min([el["name"].count('/') for el in data])
    for idx in range(0, min_slash_num+1):
        if check_separate_groups(data, idx):
            break
    return idx


def group_data(data):
    sep_idx = find_separating_index(data)
    result = defaultdict(lambda: defaultdict(list))
    for el in data:
        group_name = get_group_name(el["name"], sep_idx)
        result[group_name]["names"].append(el["name"])
        result[group_name]["cpu_time"].append(el["cpu_time"])
    return result


def plot_data(data, args):
    if args.norm:
        normalize_times(data)
    groups = group_data(data)
    plt.figure(figsize=[int(val) for val in args.figsize.split()])
    plt.grid(zorder=0)
    for key, val in groups.items():
        plt.barh(val["names"], val["cpu_time"], zorder=3)
    plt.xlabel(f"time, {data[0]['time_unit']}")
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

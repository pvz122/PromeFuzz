#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Draw the coverage plot for the given project.
"""

import matplotlib.pyplot as plt
import click
from pathlib import Path
from dataclasses import dataclass
import json


@dataclass
class CoverageHourData:
    """
    Class to store the coverage data for a specific hour.
    """

    hour: int
    """The hour timestamp of the coverage data"""

    line: int
    """The line coverage data"""

    branch: int
    """The branch coverage data"""

    @classmethod
    def from_json(cls, json_path: Path):
        # The filename is (g)cov-{HOUR}.json
        hour = int(json_path.stem.split("-")[-1])
        data = json.loads(json_path.read_text())
        return cls(hour, data["Summary"]["line"], data["Summary"]["branch"])


class CoverageData:
    """
    Class to store the per hour coverage data of a fuzz execution.
    """

    def __init__(self, data_hours: list[CoverageHourData]):
        self.data_hours = sorted(data_hours, key=lambda x: x.hour)

    @classmethod
    def from_directory(cls, cov_dir: Path) -> "CoverageData":
        data_hours = []
        for json_path in cov_dir.glob("*.json"):
            data_hour = CoverageHourData.from_json(json_path)
            data_hours.append(data_hour)
        return cls(data_hours)


def prepare_data(
    cov_dirs: list[Path], is_branch: bool
) -> tuple[list[float], list[float], list[float]]:
    """
    Prepare the coverage data for the coverage plot.

    :param cov_dirs: The path to the coverage directories
    :param is_branch: Whether the coverage type is branch coverage
    :return: A tuple containing the coverage data, in the form of ([upper], [lower], [average]),
            where each list contains the coverage data for each hour
    """
    cov_data_list = [CoverageData.from_directory(cov_dir) for cov_dir in cov_dirs]

    hour_num = cov_data_list[0].data_hours[-1].hour
    upper, lower, average = (
        [0.0] * hour_num,
        [float("inf")] * hour_num,
        [0.0] * hour_num,
    )
    for i in range(hour_num):
        for cov_data in cov_data_list:
            hour_data = cov_data.data_hours[i]
            if is_branch:
                coverage = hour_data.branch
            else:
                coverage = hour_data.line
            upper[i] = max(upper[i], coverage)
            lower[i] = min(lower[i], coverage)
            average[i] += coverage
        average[i] /= len(cov_data_list)
    return upper, lower, average


def draw_data(
    upper: list[float],
    lower: list[float],
    average: list[float],
    is_branch: bool,
    title: str,
):
    """
    Draw the coverage plot for the given data.

    :param upper: The upper bound of the coverage data
    :param lower: The lower bound of the coverage data
    :param average: The average of the coverage data
    :param is_branch: Whether the coverage type is branch coverage
    :param title: The title of the plot
    """
    x = list(range(len(upper) + 1))
    plt.xlim(0, len(x) - 1)
    plt.ylim(0, max(upper) + 100)
    plt.fill_between(x, [0] + lower, [0] + upper, color="gray", alpha=0.5)
    plt.plot(x, [0] + average, color="black")
    plt.xlabel("Time (hour)")
    plt.ylabel(f"Coverage{' (branch)' if is_branch else ' (line)'}")
    plt.title(title)


@click.command(help="Draw the coverage plot")
@click.option(
    "--project", "-p", required=True, help="The name of the project, e.g., ngiflib"
)
@click.option(
    "--version", "-v", required=True, help="The version of the project, e.g., latest"
)
@click.option(
    "--fuzz-id",
    "-fi",
    "fuzz_id",
    required=True,
    help="The identification name of the fuzz target, e.g., promefuzz",
)
@click.option(
    "--cov-type",
    "-ct",
    "cov_type",
    type=click.Choice(["gcov-line", "gcov-branch", "cov-line", "cov-branch"]),
    default="gcov-branch",
    help="The type of coverage to be plotted, can be gcov-line, gcov-branch, cov-line, or cov-branch",
)
@click.option(
    "--title", "-t", "title", default=None, help="The title of the coverage plot"
)
@click.option(
    "--output",
    "-o",
    "output",
    type=click.Path(path_type=Path, dir_okay=True, file_okay=False),
    default=None,
    help="The output directory of the coverage plot",
)
def draw_plot(
    project: str, version: str, fuzz_id: str, cov_type: str, title: str, output: Path
):
    is_branch = cov_type.endswith("branch")
    cov_type_str = cov_type.split("-")[0]
    cov_dir = (Path(project) / version / cov_type_str).resolve()
    if not cov_dir.exists():
        raise FileNotFoundError(f"Coverage directory {cov_dir} does not exist")
    if not output:
        output = cov_dir

    # find all {fuzz_id}_{num}_{index} directories
    cov_dirs = list(cov_dir.glob(f"{fuzz_id}_*_*"))
    if not cov_dirs:
        raise FileNotFoundError(f"No coverage data found for {fuzz_id}")

    # Prepare the coverage data
    plot_data = prepare_data(cov_dirs, is_branch)

    # Draw the coverage plot
    title = title if title else f"{project}-{version}-{fuzz_id}"
    draw_data(*plot_data, is_branch, title)
    plt.savefig(output / f"{title}.svg")
    plt.savefig(output / f"{title}.png", dpi=300)

    print(f"Coverage plot saved to \"{output / title}.png\"")


if __name__ == "__main__":
    draw_plot()

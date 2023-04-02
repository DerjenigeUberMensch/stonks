from matplotlib import pyplot as plt
import pandas as pd
import time
import os
def main():
    try:
        with open('ETH.txt', 'r') as file:
            var = [i for i in file]
    except FileNotFoundError:
        return None
    x = [i for i in range(len(var))]
    y = [float(i) for i in var]
    plt.ylabel("Price")
    plt.xlabel("days")
    plt.title("Stock Market Prices over time")
    plt.plot(x,y, c="black",linewidth=2)
    plt.show()
    plt.close()
    with open('nums.txt', 'w') as f:
        f.truncate()
        f.close()

if __name__ == "__main__":
    main()
import matplotlib.pyplot as plt
import numpy as np
import csv

def bootstrap(x, samples, statfunc):
    resampled_stat = []

    for k in range(samples):
        index = np.random.randint(0, len(x), len(x))
        sample = x[index]
        resampled_stat.append(statfunc(sample))
    
    return np.array(resampled_stat)

def open_data(file_name):
    file = open(file_name, "r")
    data = file.read().split("\n")
    split_data = [d.split(",") for d in data]
    filtered_data = []
    for s in split_data:
        if len(s) == 1:
            continue
        else:
            filtered_data.append(int(s[1]) - 128) #Account for offset
    return filtered_data

#Integer Addition Histogram
plt.figure()
data = np.asarray(open_data("integer_addition.txt"))
hist, bins = np.histogram(data, bins=2)
plt.hist(data, bins=bins)
plt.title("Cycles to Process Integer Addition")
plt.xlabel("# Cycles")
plt.ylabel("Frequency")

#Float Addition Histogram
plt.figure()
data = np.asarray(open_data("float_addition.txt"))
hist, bins = np.histogram(data, bins=2)
plt.hist(data, bins=bins)
plt.title("Cycles to Process Float Addition")
plt.xlabel("# Cycles")
plt.ylabel("Frequency")

#data access Histogram
plt.figure()
data = np.asarray(open_data("access_data.txt"))
hist, bins = np.histogram(data, bins=15)
plt.hist(data, bins=bins)
plt.title("Cycles to Print a Access Random DDR Address")
plt.xlabel("# Cycles")
plt.ylabel("Frequency")
print(np.mean(data))

#LED Histogram
plt.figure()
data = np.asarray(open_data("led.txt"))
hist, bins = np.histogram(data, bins=3)
plt.hist(data, bins=bins)
plt.title("Cycles to Activate LED")
plt.xlabel("# Cycles")
plt.ylabel("Frequency")

#printf Histogram
plt.figure()
data = np.asarray(open_data("printf.txt"))
hist, bins = np.histogram(data, bins=5)
plt.hist(data, bins=bins)
plt.title("Cycles to Print a Float")
plt.xlabel("# Cycles")
plt.ylabel("Frequency")

#xil_printf Histogram
plt.figure()
data = np.asarray(open_data("xil_printf.txt"))
hist, bins = np.histogram(data, bins=5)
plt.hist(data, bins=bins)
plt.title("Cycles to Print a 10 character string")
plt.xlabel("# Cycles")
plt.ylabel("Frequency")

#data access CDF
plt.figure()
data = np.asarray(open_data("access_data.txt"))
confidence_data = bootstrap(data, 1000, np.mean)

mu = np.mean(confidence_data)
sig = np.std(confidence_data)
low = mu - 1.96 * (sig/31.6223)
high = mu + 1.96 * (sig/31.6223)

x = np.sort(data)
y = np.arange(x.shape[0]) / float(x.shape[0])
t = "95% Confidence Interval for DDR Access: " + str(low) + " - " + str(high)

plt.title(t)
plt.xlabel("Cycles")
plt.ylabel("Probability")
plt.plot(x, y)







# plt.show()

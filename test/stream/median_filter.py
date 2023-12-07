import numpy as np
import matplotlib.pyplot as plt


# Function to get data from USB
def get_data_from_usb(x):
    # Simulating USB data retrieval
    data = 20 + np.random.randint(0, 5)
    return data


def gen_trig(x):
    in_x=x*8;
    return np.sin(in_x) + np.sin(50 * in_x) / 10


def get_data(x):
    return gen_trig(x)


# Median filter implementation
def median_filter(data, buffer_size):
    filtered_data = []
    buffer = []

    for i in range(len(data)):
        buffer.append(data[i])
        if len(buffer) > buffer_size:
            buffer.pop(0)
        sorted_buffer = sorted(buffer)
        median = sorted_buffer[len(sorted_buffer) // 2]
        filtered_data.append(median)

    return filtered_data


# Initialize buffer and filtered data
buffer = []
filtered_data = []

# Initialize plot
fig, ax = plt.subplots()

line1, = ax.plot([], [], 'b-', label='Original Data')
line2, = ax.plot([], [], 'r-', label='Filtered Data')

ax.set_title('Data Visualization')
ax.set_xlabel('Time')
ax.set_ylabel('Amplitude')

ax.legend()
plt.tight_layout()

# Start loop to retrieve and visualize data
x = 0
while True:
    # Get data from USB
    data = get_data(x)
    # Append data to buffer
    buffer.append(data)
    # Apply median filter dynamically
    if len(buffer) > 1:
        filtered_data = median_filter(buffer, 20)
    # Update plot
    time = np.arange(len(buffer))
    line1.set_data(time, buffer)
    line2.set_data(time, filtered_data)
    ax.set_xlim(x, x+20)
    ax.set_ylim(min(buffer) - 1, max(buffer) + 1)
    x += 0.1
    plt.draw()
    plt.pause(0.01)

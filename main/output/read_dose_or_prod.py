import sys
import matplotlib.pyplot as plt
import numpy as np


if __name__ == '__main__':
    print sys.argv
    file_name = sys.argv[1]
    print file_name

    with open(file_name)as f:
        data_vect = f.readlines()[6:]

    print 'data_vector shape: {0}'.format(np.shape(data_vect))
    print 'data_vector max: {0}'.format(max(data_vect))

    x_data = np.arange(len(data_vect))
    print type(data_vect[0])
    plt.plot(x_data, map(float, data_vect))
    plt.show()
    


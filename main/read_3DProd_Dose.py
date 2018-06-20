import sys
import matplotlib.pyplot as plt
import numpy as np
import os

def matrix_binning(_data, bin_factor, m_size):
        
    new_data = np.zeros((m_size[2]/binning, m_size[1], m_size[0]))
    #print np.shape(_data)
    for i in range(0, m_size[2]):
        new_data[int(i/bin_factor),:,:] = np.add(new_data[int(i/bin_factor),:,:],_data[i,:,:])
    return new_data

def dose_matrix_binning(_data, bin_factor):
        
    new_data = np.zeros((len(_data)/binning, 1))
    #print np.shape(_data)
    for i in range(0, len(_data)):
        new_data[int(i/bin_factor)] = np.add(new_data[int(i/bin_factor)],_data[i])
    return new_data

if __name__ == '__main__':


    binning = 2 #in mm
    
    nuclei = (('C11','N13','O15','B8','C9','C10','N12','O13','O14','P29','P30','S30','S31','K37','K38','Ca38','Ca39'))
    colours = (('r--','b-.','g:','k-', 'azure', 'crimson', 'orchid', 'lime','olive','khaki','yellowgreen','lavender','indigo','maroon','cyan','fuchsia','gold'))
    directory = sys.argv[1]
    extension = '_map-Stop.txt'
    dose_ext = 'dose_phantom-Dose.txt'  #dose_phantom-Edep.txt
    #print nuclei
    #print sys.argv
    file_name = os.path.join(sys.argv[1], nuclei[0]+extension)
    #print file_name

    fig, ax1 = plt.subplots()

    with open(file_name)as f:
	details = f.readlines()[1:6]
        matrix_size = map(int, details[0].split('= (')[1][:-2].split(","))
        print 'Actor matrix size: {0}'.format(matrix_size)
        resolution = map(int, details[1].split('= (')[1][:-2].split(","))
        print 'Actor size: {0} mm'.format(resolution)
        voxel_size = map(float, details[2].split('= (')[1][:-2].split(","))
        print 'Voxel size: {0} mm'.format(voxel_size)
        nbval = int(details[3].split('= ')[1])

    all_beta_plus = np.zeros((matrix_size[2]/binning, matrix_size[1], matrix_size[0]))    

    for i in range (0, len(nuclei)):
	print 'Nuclei map processing: {0}'.format(nuclei[i]+extension)
        with open(os.path.join(directory, nuclei[i]+extension)) as f:
            # data loading
            data_vect = np.loadtxt(f, dtype=float).reshape((matrix_size[2],matrix_size[1],matrix_size[0]))
            x_data = np.arange(0, len(data_vect), binning)
            
            # data binning as Antoni want
            if binning!=1:
		data_vect = matrix_binning(data_vect, binning, matrix_size)

            
            all_beta_plus = np.add(all_beta_plus, data_vect)
            
            ax1.plot(x_data, map(int, data_vect.sum(axis=2).sum(axis=1)), colours[i])

    ax1.plot(x_data, map(int, all_beta_plus.sum(axis=2).sum(axis=1)), colours[-1])

    ax1.set_xlabel('Phantom depth [mm]')
    ax1.set_xlim([0,matrix_size[2]])

    ax1.set_ylabel('Number of nuclei')

    #ax1.legend([nuclei[0], nuclei[1], nuclei[2], 'Sum of all'])

    ax1.set_title('Dose and stopping position in the phantom of the main beta+ emitters\n produced by 150MeV protons in PMMA phantom \nBinning: {0} mm'.format(binning))

    ax1.grid(linestyle = ':', linewidth = 0.75, color = 'grey')
    
    # DOSE PLOT
    with open(os.path.join(directory, dose_ext)) as f:
        dose = np.loadtxt(f, dtype=float)
        print np.shape(dose)
        
        if binning!=0:
            dose = dose_matrix_binning(dose, binning)
    
    ax2 = ax1.twinx()    
    ax2.plot(x_data, dose, color = 'magenta', linestyle = '-')
    ax2.set_ylabel('Dose [Gy]', color='magenta')
    ax2.tick_params('y', colors='magenta')    
    ax1.legend([nuclei[0], nuclei[1], nuclei[2], nuclei[3], nuclei[4], nuclei[5], nuclei[6], nuclei[7], nuclei[8], nuclei[9], nuclei[10], nuclei[11], nuclei[12], nuclei[13], nuclei[14], nuclei[15], nuclei[16], 'Sum of all','Deposited dose'])
    fig.tight_layout()
       
    plt.show()
    


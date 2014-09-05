import numpy as np
import matplotlib.pyplot as plt
import pylab
import glob
import os

with plt.xkcd():

    from matplotlib import rc
    rc('font',**{'size': 18})
    rc('text', usetex=True)
    
    current_path=os.getcwd()
    
    myx = np.linspace(0.01, 300000)
    mylog2 = np.log(myx)*np.log(myx)
    
    fig = plt.figure()
    axes = fig.add_subplot( 1, 1, 1 )
    #axes.set_yscale('log')

    datalist = pylab.loadtxt( "statVoronoi-mono.txt" )
    datalist2 = pylab.loadtxt( "statVoronoi-openmp.txt" )
    datalist3 = pylab.loadtxt( "result-raster.txt" )
    
    #plt.legend( loc=2 )
    plt.xlabel( "Mask size $m$" )
    plt.ylabel( 'Time in sec' )
    
    p1,=plt.plot( datalist[:,0],datalist[:,1]/1000, 'g',label="Voronoi Map (single thread)",alpha=1 )
    p2,=plt.plot( datalist2[:,0],datalist2[:,1]/1000, 'r',label="Voronoi Map (multi-thread)",alpha=1 )
    p2b,=plt.plot( datalist3[0:120,0],2.0*datalist3[0:120,1]/1000, 'b',label="Raster scan",alpha=1 )
    p3,=plt.plot( myx, 0.04*mylog2, '.r',label="$0.04\log^2{m}$",alpha=0.5 )
    p4,=plt.plot( myx, 0.4*mylog2, '.g',label="$0.4\log^2{m}$",alpha=0.5 )
    
    lines=[p1,p2,p2b,p3,p4]
    ##plt.legend( loc=2 )
    plt.legend(lines, [l.get_label() for l in lines],loc=1,prop={'size':16},frameon=False)


    ##plt.show()
    plt.savefig( 'result.pdf', format='PDF' )


    datalistt = pylab.loadtxt( "statVoronoi-mono-short.txt" )
    datalistt2 = pylab.loadtxt( "statVoronoi-openmp-short.txt" )
    datalistt3 = pylab.loadtxt( "result-raster-short.txt" )
    
    
    myxx = np.linspace(0.01, 90)
    myylog2 = np.log(myxx)*np.log(myxx)
    
    fig2 = plt.figure()
    axes2 = fig2.add_subplot( 1, 1, 1 )
    #axes2.set_yscale('log')

    plt.xlabel( "Mask size $m$" )
    plt.ylabel( 'Time in sec' )
    
    p1,=plt.plot( datalistt[:,0],datalistt[:,1]/1000, 'g',label="Voronoi Map (single thread)",alpha=1 )
    p2,=plt.plot( datalistt2[:,0],datalistt2[:,1]/1000, 'r',label="Voronoi Map (multi-thread)",alpha=1 )
    p2b,=plt.plot( datalistt3[:,0],2*datalistt3[:,1]/1000, 'b',label="Raster scan",alpha=1 )
    #p3,=plt.plot( myxx, 0.04*myylog2, '.r',label="$0.04\log^2{m}$",alpha=0.5 )
    #p4,=plt.plot( myxx, 0.4*myylog2, '.g',label="$0.4\log^2{m}$",alpha=0.5 )

    liness=[p1,p2,p2b]#,p3,p4]
    ##plt.legend( loc=2 )
    plt.legend(liness, [l.get_label() for l in lines], loc=2,prop={'size':16},frameon=False)


##plt.show()
plt.savefig( 'result-zoom.pdf', format='PDF' )




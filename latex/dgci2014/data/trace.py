import numpy as np
import matplotlib.pyplot as plt
import pylab
import glob
import os

from matplotlib import rc
rc('font',**{'size': 18})
rc('text', usetex=True)

current_path=os.getcwd()

myx = np.linspace(0.01, 300000)
mylog2 = np.log(myx)*np.log(myx)

fig = plt.figure()
axes = fig.add_subplot( 1, 1, 1 )

datalist = pylab.loadtxt( "statVoronoi-mono.txt" )
datalist2 = pylab.loadtxt( "statVoronoi-openmp.txt" )

#plt.legend( loc=2 )
plt.xlabel( "Mask size $m$" )
plt.ylabel( 'Time in sec' )

p1,=plt.plot( datalist[:,0],datalist[:,1]/1000, 'g',label="Voronoi Map (single thread)",alpha=1 )
p2,=plt.plot( datalist2[:,0],datalist2[:,1]/1000, 'r',label="Voronoi Map (multi-thread)",alpha=1 )
p3,=plt.plot( myx, 0.04*mylog2, '.r',label="$0.04\log^2{m}$",alpha=0.5 )
p4,=plt.plot( myx, 0.4*mylog2, '.g',label="$0.4\log^2{m}$",alpha=0.5 )

lines=[p1,p2,p3,p4]
##plt.legend( loc=2 )
plt.legend(lines, [l.get_label() for l in lines], loc=7,frameon=False)


##plt.show()
plt.savefig( 'result.pdf', format='PDF' )


datalistt = pylab.loadtxt( "statVoronoi-mono-short.txt" )
datalistt2 = pylab.loadtxt( "statVoronoi-openmp-short.txt" )


myxx = np.linspace(0.01, 90)
myylog2 = np.log(myxx)*np.log(myxx)

fig2 = plt.figure()
axes2 = fig2.add_subplot( 1, 1, 1 )

plt.xlabel( "Mask size $m$" )
plt.ylabel( 'Time in sec' )

p1,=plt.plot( datalistt[:,0],datalistt[:,1]/1000, 'g',label="Voronoi Map (single thread)",alpha=1 )
p2,=plt.plot( datalistt2[:,0],datalistt2[:,1]/1000, 'r',label="Voronoi Map (multi-thread)",alpha=1 )
p3,=plt.plot( myxx, 0.04*myylog2, '.r',label="$0.04\log^2{m}$",alpha=0.5 )
p4,=plt.plot( myxx, 0.4*myylog2, '.g',label="$0.4\log^2{m}$",alpha=0.5 )

liness=[p1,p2,p3,p4]
##plt.legend( loc=2 )
plt.legend(liness, [l.get_label() for l in lines], loc=2,frameon=False)


##plt.show()
plt.savefig( 'result-zoom.pdf', format='PDF' )





#   #  o     o ooo.   .oPYo.      .oo
#   #  8b   d8 8  `8. 8    8     .P 8
#   #  8`b d'8 8   `8 8         .P  8
#   #  8 `o' 8 8    8 8        oPooo8
#   #  8     8 8   .P 8    8  .P    8
#   #  8     8 8ooo'  `YooP' .P     8
#   #  ..::::.......:::.....:..:::::..
#   #  :::::::::::::::::::::::::::::::
#   #  :::::::::::::::::::::::::::::::
#   list_of_files = []
#   for current_file in glob.glob( "StatisticsMDCA_*.dat" ):
#       list_of_files.append( current_file )

#   datalist = [ ( pylab.loadtxt( filename ) ) for filename in list_of_files ]

#   nbfiles = len( datalist )
#   maxK = np.zeros( datalist[0][:,error].shape )
#   minK = 10*np.ones( datalist[0][:,error].shape )
#   meanh = np.zeros( datalist[0][:,error].shape ) ##ugly but fine

#   for data in datalist:
#       datasorted = np.array( sorted( data, key=tuple ))
#       meanh = meanh + datasorted[:,0]/nbfiles

#       for i in range( len( datasorted[:,error] )):
#           t = datasorted[:,error]
#           if t[i] > maxK[i]:
#               maxK[i] = t[i]
#           if t[i] < minK[i]:
#               minK[i] = t[i]

#   print maxK.size
#   print minK.size
#   print meanh.size

#   plt.fill_between( meanh, minK, maxK, facecolor='green', interpolate=True, alpha=0.3 )
#   plt.plot( meanh, minK, 'g', alpha=1 )
#   plt.plot( meanh, maxK, 'g', label="MDCA", alpha=1 )

#   #  o     o ooo.   .oPYo. .oPYo. 8
#   #  8b   d8 8  `8. 8      8      8
#   #  8`b d'8 8   `8 `Yooo. `Yooo. 8
#   #  8 `o' 8 8    8     `8     `8 8
#   #  8     8 8   .P      8      8 8
#   #  8     8 8ooo'  `YooP' `YooP' 8
#   #  ..::::.......:::.....::.....:..
#   #  :::::::::::::::::::::::::::::::
#   #  :::::::::::::::::::::::::::::::
#   # list_of_files = []
#   # for current_file in glob.glob( "StatisticsMDSSLength_*.dat" ):
#   #     list_of_files.append( current_file )

#   # datalist = [ ( pylab.loadtxt( filename )) for filename in list_of_files ]

#   # nbfiles = len( datalist )
#   # maxK = np.zeros( datalist[0][:,error].shape )
#   # minK = 10*np.ones( datalist[0][:,error].shape )
#   # meanh = np.zeros( datalist[0][:,error].shape ) ##ugly but fine

#   # for data in datalist:
#   #     datasorted = np.array( sorted( data, key=tuple ))
#   #     meanh = meanh + datasorted[:,0]/nbfiles

#   #     for i in range( len( datasorted[:,error] )):
#   #         t = datasorted[:,error]
#   #         if t[i] > maxK[i]:
#   #             maxK[i] = t[i]
#   #         if t[i] < minK[i]:
#   #             minK[i] = t[i]

#   # print maxK.size
#   # print minK.size
#   # print meanh.size

#   # plt.fill_between( meanh, minK, maxK, facecolor='cyan', interpolate=True, alpha=0.3 )
#   # plt.plot( meanh, minK, 'c', alpha=1)
#   # plt.plot( meanh, maxK, 'c', label="MDSS length", alpha=1)

#   #  o     o ooo.   .oPYo. .oPYo. 8
#   #  8b   d8 8  `8. 8      8      8
#   #  8`b d'8 8   `8 `Yooo. `Yooo. 8 o   o   o
#   #  8 `o' 8 8    8     `8     `8 8 Y. .P. .P
#   #  8     8 8   .P      8      8 8 `b.d'b.d'
#   #  8     8 8ooo'  `YooP' `YooP' 8  `Y' `Y'
#   #  ..::::.......:::.....::.....:..::..::..::
#   #  :::::::::::::::::::::::::::::::::::::::::
#   #  :::::::::::::::::::::::::::::::::::::::::
#   list_of_files = []
#   for current_file in glob.glob( "StatisticsMDSSLengthWidth_*.dat" ):
#       list_of_files.append( current_file )

#   datalist = [ ( pylab.loadtxt( filename )) for filename in list_of_files ]

#   nbfiles = len( datalist )
#   maxK = np.zeros( datalist[0][:,error].shape )
#   minK = 10*np.ones( datalist[0][:,error].shape )
#   meanh = np.zeros( datalist[0][:,error].shape ) ##ugly but fine

#   for data in datalist:
#       datasorted = np.array( sorted( data, key=tuple ))
#       meanh = meanh + datasorted[:,0]/nbfiles

#       for i in range( len( datasorted[:,error] )):
#           t = datasorted[:,error]
#           if t[i] > maxK[i]:
#               maxK[i] = t[i]
#           if t[i] < minK[i]:
#               minK[i] = t[i]

#   print maxK.size
#   print minK.size
#   print meanh.size

#   plt.fill_between( meanh, minK, maxK, facecolor='magenta', interpolate=True, alpha=0.3 )
#   plt.plot( meanh, minK, 'm', alpha=1)
#   plt.plot( meanh, maxK, 'm', label="MDSS", alpha=1 )

#   #  o   o
#   #  8   8
#   #  8   8
#   #  8   8
#   #  8   8
#   #  8   8
#   #  .....
#   #  :::::
#   #  :::::
#   list_of_files = []
#   for current_file in glob.glob( "StatisticsAllII_*.dat" ):
#     list_of_files.append( current_file )

#   datalist = [ ( pylab.loadtxt( filename )) for filename in list_of_files ]

#   print type( datalist )
#   print list_of_files

#   nbfiles = len( datalist )
#   print nbfiles

#   maxK = np.zeros( datalist[0][:,error].shape )
#   minK = 10*np.ones( datalist[0][:,error].shape )
#   meanh = np.zeros( datalist[0][:,error].shape ) ##ugly but fine

#   for data in datalist:
#       datasorted = np.array( sorted( data, key=tuple ))
#       meanh = meanh + datasorted[:,0]/nbfiles

#       for i in range( len( datasorted[:,error] )):
#           t = datasorted[:,error]
#           if t[i] > maxK[i]:
#               maxK[i] = t[i]
#           if t[i] < minK[i]:
#               minK[i] = t[i]

#   print maxK.size
#   print minK.size
#   print meanh.size

#   plt.fill_between( meanh, minK, maxK, interpolate=True, alpha=0.3 )
#   plt.plot( meanh, minK, 'b', alpha=1 )
#   plt.plot( meanh, maxK, 'b', label="II", alpha=1 )


#   #  .o        8   .oPYo.
#   #   8       8        `8
#   #   8      8       .oP'
#   #   8     8         `b.
#   #   8    8           :8
#   #   8   8        `YooP'
#   #  :..::..:::::::.....:
#   #  ::::::::::::::::::::
#   #  ::::::::::::::::::::

#   x = np.linspace( 0.0001, 1, 50 )
#   y = x**0.33333
#   plt.plot( x, scaleXOneThird*y, label="$O(h^{1/3})$", linestyle='--',color="k" )

#   axes.set_xscale( "log" )
#   axes.set_yscale( "log" )

#   plt.legend( loc=2 )
#   plt.xlabel( "$h$" )
#   if errortype == 'Loo':
#     plt.ylabel( '$l_\infty$ error' )
#   elif errortype == 'L2':
#     plt.ylabel( '$l_2$ error' )
#   elif errortype == 'L1':
#     plt.ylabel( '$l_1$ error' )

#   plt.savefig( '../../Graphs/' + shapeName + '_' + errortype + '.pdf', format='PDF' )

#   os.chdir( current_path )
#   ####### end computeError()





# #  o     o         o
# #  8b   d8
# #  8`b d'8 .oPYo. o8 odYo.
# #  8 `o' 8 .oooo8  8 8' `8
# #  8     8 8    8  8 8   8
# #  8     8 `YooP8  8 8   8
# #  ..::::..:.....::....::..
# #  ::::::::::::::::::::::::
# #  ::::::::::::::::::::::::

# computeError( 'L1', 'AccFlower', 0.04 )
# computeError( 'L2', 'AccFlower', 0.04 )
# computeError( 'Loo', 'AccFlower', 13 )

# computeError( 'L1', 'Flower', 0.04 )
# computeError( 'L2', 'Flower', 0.04 )
# computeError( 'Loo', 'Flower', 3 )

# computeError( 'L1', 'Ellipse', 0.04 )
# computeError( 'L2', 'Ellipse', 0.04 )
# computeError( 'Loo', 'Ellipse', 0.4 )

# #computeError( 'L1', 'Ball2D', 0.04 )
# #computeError( 'L2', 'Ball2D', 0.04 )
# #computeError( 'Loo', 'Ball2D', 0.4 )

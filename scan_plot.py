import os, glob, numpy as np, matplotlib
import collections
import matplotlib.pyplot as plt, operator as op
from matplotlib.ticker import FormatStrFormatter
matplotlib.use("agg")
import math

#    NEVENTS = 1000
#    NUM_CU = 1
#    NBUFFER = 1
#Throughput = 1689.42 events/s

markerlist = [
'v',
's',
'D',
'o',
'.',
',',
'^',
'<',
'>',
'p',
'*',
'h',
'H',
'+',
'x',
'd',
'|',
'_',
]
colorlist = [
'g',
'r',
'b',
'm',
'c',
'y',
'k',
'w',
]
stylelist = [colorlist, markerlist]

str_map = {
'NUM_CU':'# of CUs',
'NEVENTS':'# of events'
}

num_events = 10000
num_threads = 8

def plot_from_file(infile, xpar, outname, title, xlabel, ylabel, select = '', adtext='Alveo U250', cutx = -1.):

    trpt = {}
    tmppar = []
    parnames = []
    firstpt = True

    with open(infile) as fp:
        line = fp.readline()
        while line:
            var,val = line.strip().split(' = ')
            if 'events/s' in val:
                trpt[','.join(tmppar)] = float(val.replace(' events/s',''))
                tmppar = []
                firstpt = False
            else:
                if firstpt:
                    parnames.append(var)
                tmppar.append(val)
            line = fp.readline()

    print(parnames)
    print(trpt)

    lines_x = collections.defaultdict(list)
    lines_y = collections.defaultdict(list)

    for p in trpt:
        params = p.split(',')
        xtmp = params.pop(parnames.index(xpar))
        lines_x[','.join(params)].append(int(xtmp))
        lines_y[','.join(params)].append(trpt[p])

    parnames.pop(parnames.index(xpar))
    print(lines_x)
    print(lines_y)

    parlist = [[] for i in range(len(parnames))]
    for line in lines_x:
        parvals = line.split(',')
        for ip in range(len(parvals)):
            if (parvals[ip] not in parlist[ip]): parlist[ip].append(parvals[ip])

    for ip in range(len(parvals)):
        parlist[ip].sort(key=int)

    fig, ax = plt.subplots()
    ax.grid(True,linestyle='-',alpha=0.4)

    im = 0
    for line in lines_x:
        parvals = line.split(',')
        errscale = float(math.sqrt(num_events))/float(math.sqrt(num_threads)*num_events)
        if 'NEVENTS' in parnames:
            errscale = float(math.sqrt(int(parvals[parnames.index('NEVENTS')])))/float(math.sqrt(num_threads)*int(parvals[parnames.index('NEVENTS')]))
        lab = [i + " = " + j for i, j in zip(parnames, parvals)]
        if select!='':
            if select not in lab:
                continue
            else:
                lab.pop(lab.index(select))
        for il in range(len(lab)):
            for r in str_map:
                lab[il] = lab[il].replace(r,str_map[r])
        if select!='':
            ax.plot(np.array(lines_x[line]), np.array(lines_y[line]), "%s"%("".join([stylelist[ip][im] for ip in range(len(stylelist))])), label=", ".join(lab), markersize=11, markeredgewidth=0.0)
            im = im + 1
        else:
            ax.plot(np.array(lines_x[line]), np.array(lines_y[line]), "%s"%("".join([stylelist[ip][parlist[ip].index(parvals[ip])] for ip in range(min(2,len(parvals)))])), label=", ".join(lab), markersize=9, markeredgewidth=0.0)
        #ax.errorbar(np.array(lines_x[line]), np.array(lines_y[line]), fmt="%s"%("".join([stylelist[ip][parlist[ip].index(parvals[ip])] for ip in range(min(2,len(parvals)))])), yerr=errscale*np.array(lines_y[line]), label=", ".join(lab), markersize=9, elinewidth=10)

    #ax.legend(loc='lower right',fontsize=10)
    handles, labels = ax.get_legend_handles_labels()
    # sort both labels and handles by labels
    labels, handles = zip(*sorted(zip(labels, handles), key=lambda t: t[0]))
    ax.legend(handles, labels,loc='lower right',fontsize=12,numpoints=1)
    ax.yaxis.set_major_formatter(FormatStrFormatter('%.0f'))
    ax.set_xlabel(xlabel,fontsize=16)
    ax.set_ylabel(ylabel,fontsize=16)
    ax.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
    ax.set_title(title)
    ax.set_ylim(0,ax.get_ylim()[1]*1.2)
    if (cutx>0.):
        ax.set_xlim(ax.get_xlim()[0],cutx)
    plt.text(0.05, 0.95, adtext, horizontalalignment='left', verticalalignment='center', transform=ax.transAxes, bbox=dict(facecolor='gray', alpha=1., linewidth=0.))

    plt.savefig(outname)

#plot_from_file('scan_u55c.dat','NBUFFER','scan_u55c_10k.pdf','Throughput Test - U55C','Size of DDR buffer (# of inputs)','Throughput (events/sec)','NEVENTS = 10000', 'U55C')
plot_from_file('scan_u55c_hbm.dat','NBUFFER','scan_u55c_hbm_10k.pdf','NRP - U55C [HBM]','Size of HBM buffer (# of inputs)','Throughput (events/sec)','NEVENTS = 10000', 'U55C [HBM]')

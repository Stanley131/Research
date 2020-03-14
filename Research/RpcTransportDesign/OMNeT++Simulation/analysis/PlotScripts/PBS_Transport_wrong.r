#!/usr/bin/Rscript
library(reshape2)
library(ggplot2)
library(grid)
library(gridExtra)
library(plyr)

# Plots the stretch vs. unsched bytes from text data files generated by
# PlotDigeter.py script
stretchVsSize <- read.table("stretchVsTransport.txt",
    na.strings = "NA",
    col.names=c('TransportType', 'LoadFactor', 'WorkLoad', 'MsgSizeRange',
    'SizeCntPercent', 'BytesPercent', 'UnschedBytes', 'MeanStretch',
    'MedianStretch', 'TailStretch'), header=TRUE)

stretchVsSize$LoadFactor <- factor(stretchVsSize$LoadFactor)
stretchVsSize$TransportType <- factor(stretchVsSize$TransportType)

#print(stretchVsSize$TransportType)


avgStretchVsSize <- subset(stretchVsSize,
    !is.na(MeanStretch) & !(MsgSizeRange %in% c('Huge', 'OverAllSizes')),
    select=c('TransportType', 'LoadFactor', 'WorkLoad', 'MsgSizeRange',
    'SizeCntPercent', 'BytesPercent', 'UnschedBytes', 'MeanStretch'))

avgStretchVsSize <- ddply(avgStretchVsSize,
    .(TransportType, LoadFactor, WorkLoad, UnschedBytes), transform,
    SizeCumPercent = round(cumsum(SizeCntPercent), 2),
    BytesCumPercent = round(cumsum(BytesPercent), 2))

avgStretchVsSize$MsgSizeRange <- as.numeric(as.character(
    avgStretchVsSize$MsgSizeRange))

medianStretchVsSize <- subset(stretchVsSize,
    !is.na(MedianStretch) & !(MsgSizeRange %in% c('Huge', 'OverAllSizes')),
    select=c('TransportType', 'LoadFactor', 'WorkLoad', 'MsgSizeRange',
    'SizeCntPercent', 'BytesPercent', 'UnschedBytes', 'MedianStretch'))

medianStretchVsSize <- ddply(medianStretchVsSize,
    .(TransportType, LoadFactor, WorkLoad, UnschedBytes), transform,
    SizeCumPercent = round(cumsum(SizeCntPercent), 2),
    BytesCumPercent = round(cumsum(BytesPercent), 2))

medianStretchVsSize$MsgSizeRange <- as.numeric(
    as.character(medianStretchVsSize$MsgSizeRange))

tailStretchVsSize <- subset(stretchVsSize,
    !is.na(TailStretch) & !(MsgSizeRange %in% c('Huge', 'OverAllSizes')),
    select=c('TransportType', 'LoadFactor', 'WorkLoad', 'MsgSizeRange',
    'SizeCntPercent', 'BytesPercent', 'UnschedBytes', 'TailStretch'))

tailStretchVsSize <- ddply(tailStretchVsSize,
    .(TransportType, LoadFactor, WorkLoad, UnschedBytes), transform,
    SizeCumPercent = round(cumsum(SizeCntPercent), 2),
    BytesCumPercent = round(cumsum(BytesPercent), 2))

tailStretchVsSize$MsgSizeRange <- as.numeric(
    as.character(tailStretchVsSize$MsgSizeRange))

textSize <- 15
titleSize <- 20
yLimit <- 15
workloads <- c(
    levels(avgStretchVsSize$WorkLoad)[3], levels(avgStretchVsSize$WorkLoad)[5],
    levels(avgStretchVsSize$WorkLoad)[1], levels(avgStretchVsSize$WorkLoad)[4],
    levels(avgStretchVsSize$WorkLoad)[2])
# print(workloads)

for (rho in unique(tailStretchVsSize$LoadFactor)) {
    i <- 0
    tailStretchPlot = list()
    for (workload in workloads) {
        # Use CDF as the x axis
        tmp1 <- subset(tailStretchVsSize, WorkLoad==workload & LoadFactor==rho & TransportType=='homa', 
            select=c('LoadFactor', 'WorkLoad', 'MsgSizeRange', 'SizeCntPercent',
            'SizeCumPercent', 'TransportType', 'TailStretch', 'UnschedBytes'))
        tmp2 <- subset(tailStretchVsSize, WorkLoad==workload & LoadFactor==rho & TransportType=='bA', 
            select=c('LoadFactor', 'WorkLoad', 'MsgSizeRange', 'SizeCntPercent',
            'SizeCumPercent', 'TransportType', 'TailStretch', 'UnschedBytes'))
        tmp3 <- subset(tailStretchVsSize, WorkLoad==workload & LoadFactor==rho & TransportType=='bB', 
            select=c('LoadFactor', 'WorkLoad', 'MsgSizeRange', 'SizeCntPercent',
            'SizeCumPercent', 'TransportType', 'TailStretch', 'UnschedBytes'))

        tmp4 <- subset(tailStretchVsSize, WorkLoad==workload & LoadFactor==rho & TransportType=='bC', 
            select=c('LoadFactor', 'WorkLoad', 'MsgSizeRange', 'SizeCntPercent',
            'SizeCumPercent', 'TransportType', 'TailStretch', 'UnschedBytes'))
        tmp <- subset(tailStretchVsSize, WorkLoad==workload & oadFactor==rho, 
            select=c('LoadFactor', 'WorkLoad', 'MsgSizeRange', 'SizeCntPercent',
            'SizeCumPercent', 'TransportType', 'TailStretch', 'UnschedBytes'))
        if (nrow(tmp1) == 0) {
            next
        }
	#print(nrow(tmp))
        i <- i+1
        plotTitle = sprintf("Workload: %s                                 ",
            workload)

        yLab = 'TailStretch (Log Scale)\n'
        xLab <- 'Message Sizes (Bytes)'

        # You might ask why I'm using "x=SizeCumPercent-SizeCntPercent/200" in
        # the plot? The reason is that ggplot geom_bar is so dumb and I was
        # not able to shift the bars to the write while setting the width of
        # each bar to be equal to it's size probability. So I ended up manaully
        # shift the bars to the the left for half of the probability and
        # setting the width equal to the probability
	#/print(tmp)
        tailStretchPlot[[i]] <- ggplot() +
            geom_point(data=tmp1, aes(x=SizeCumPercent-SizeCntPercent/2,
            y=TailStretch, width=SizeCntPercent, colour=TransportType), size=4) +
            geom_point(data=tmp2, aes(x=SizeCumPercent-SizeCntPercent/2,
            y=TailStretch, width=SizeCntPercent, colour=TransportType), size=4)+ 
            geom_point(data=tmp3, aes(x=SizeCumPercent-SizeCntPercent/2,
            y=TailStretch, width=SizeCntPercent, colour=TransportType), size=4)+
            geom_point(data=tmp4, aes(x=SizeCumPercent-SizeCntPercent/2,
            y=TailStretch, width=SizeCntPercent, colour=TransportType), size=4) +
            geom_point(data=tmp4, aes(x=SizeCumPercent-SizeCntPercent/2,
            y=TailStretch, width=SizeCntPercent, colour=TransportType), size=4)

        plotTitle <- paste(append(unlist(strsplit(plotTitle, split='')), '\n',
            as.integer(nchar(plotTitle)/2)), sep='', collapse='')

        xIntervals <- findInterval(c(0)+seq(2,102,10),
            tmp[tmp$TransportType=='homa',]$SizeCumPercent)

        tailStretchPlot[[i]] <- tailStretchPlot[[i]] +
            theme(text = element_text(size=1.5*textSize),
                axis.text = element_text(size=1.3*textSize),
                axis.text.x = element_text(angle=75, vjust=0.5),
                strip.text = element_text(size = textSize),
                plot.title = element_text(size = 1.2*titleSize,
                color='darkblue'), plot.margin=unit(c(2,2,2.5,2.2),"cm"),
                legend.position = c(0.1, 0.85),
                legend.text = element_text(size=1.5*textSize)) +
            guides(colour = guide_legend(override.aes = list(size=textSize/4)))+
            scale_x_continuous(limits = c(0,101),
                breaks = tmp[xIntervals,]$SizeCumPercent,
                labels=tmp[xIntervals,]$MsgSizeRange, expand = c(0, 0)) +
            scale_y_log10(breaks=c(1,2,3,4,5,10,15)) +
            coord_cartesian(ylim=c(1, yLimit)) +
            labs(title = plotTitle, y = yLab, x = xLab)

    }
    pdf(sprintf("plots/TailStretchVsTransport_rho%s.pdf", rho),
        width=40,
        height=20*length(unique(tailStretchVsSize$WorkLoad)))
    args.list <- c(tailStretchPlot, list(ncol=1))
    do.call(grid.arrange, args.list)
    dev.off()
}


yLimit <- 5
for (rho in unique(medianStretchVsSize$LoadFactor)) {
    i <- 0
    medianStretchPlot = list()
    for (workload in workloads) {
        # Use CDF as the x axis
        tmp <- subset(medianStretchVsSize, WorkLoad==workload & LoadFactor==rho,
            select=c('LoadFactor', 'WorkLoad', 'MsgSizeRange', 'SizeCntPercent',
            'SizeCumPercent', 'TransportType', 'MedianStretch', 'UnschedBytes'))
        if (nrow(tmp) == 0) {
            next
        }
        i <- i+1
        plotTitle =
            sprintf("Workload: %s                                 ", workload)

        yLab = 'MedianStretch (Log Scale)\n'
        xLab <- 'Message Sizes (Bytes)'

        # You might ask why I'm using "x=SizeCumPercent-SizeCntPercent/200" in
        # the plot? The reason is that ggplot geom_bar is so dumb and I was not
        # able to shift the bars to the write while setting the width of each
        # bar to be equal to it's size probability. So I ended up manaully shift
        # the bars to the the left for half of the probability and setting the
        # width equal to the probability
        medianStretchPlot[[i]] <- ggplot() + geom_step(data=tmp,
            aes(x=SizeCumPercent-SizeCntPercent/2, y=MedianStretch,
            width=SizeCntPercent, colour=TransportType),
            size=4)

        plotTitle <- paste(append(unlist(strsplit(plotTitle, split='')), '\n',
            as.integer(nchar(plotTitle)/2)), sep='', collapse='')

        xIntervals <- findInterval(c(0)+seq(2,102,10),
            tmp[tmp$TransportType=='homa',]$SizeCumPercent)

        medianStretchPlot[[i]] <- medianStretchPlot[[i]] +
            theme(text = element_text(size=1.5*textSize),
                axis.text = element_text(size=1.3*textSize),
                axis.text.x = element_text(angle=75, vjust=0.5),
                strip.text = element_text(size = textSize),
                plot.title = element_text(size = 1.2*titleSize,
                color='darkblue'), plot.margin=unit(c(2,2,2.5,2.2),"cm"),
                legend.position = c(0.1, 0.85),
                legend.text = element_text(size=1.5*textSize)) +
            guides(colour = guide_legend(override.aes = list(size=textSize/4)))+
            scale_x_continuous(limits = c(0,101),
                breaks = tmp[xIntervals,]$SizeCumPercent,
                labels=tmp[xIntervals,]$MsgSizeRange, expand = c(0, 0)) +
            scale_y_log10(breaks=c(1,2,3,4,5,10,15)) +
            coord_cartesian(ylim=c(1, yLimit)) +
            labs(title = plotTitle, y = yLab, x = xLab)

    }
    pdf(sprintf("plots/MedianStretchVsTransport_rho%s.pdf", rho),
        width=40,
        height=20*length(unique(medianStretchVsSize$WorkLoad)))
    args.list <- c(medianStretchPlot, list(ncol=1))
    do.call(grid.arrange, args.list)
    dev.off()
}

for (rho in unique(avgStretchVsSize$LoadFactor)) {
    i <- 0
    avgStretchPlot = list()
    for (workload in workloads) {
        # Use CDF as the x axis
        tmp <- subset(avgStretchVsSize, WorkLoad==workload & LoadFactor==rho,
            select=c('LoadFactor', 'WorkLoad', 'MsgSizeRange', 'SizeCntPercent',
            'SizeCumPercent', 'TransportType', 'MeanStretch', 'UnschedBytes'))

        if (nrow(tmp) == 0) {
            next
        }
        i <- i+1
        plotTitle =
            sprintf("Workload: %s                                 ", workload)

        yLab = 'MeanStretch (Log Scale)\n'
        xLab <- 'Message Sizes (Bytes)'

        # You might ask why I'm using "x=SizeCumPercent-SizeCntPercent/200" in
        # the plot? The reason is that ggplot geom_bar is so dumb and I was not
        # able to shift the bars to the write while setting the width of each
        # bar to be equal to it's size probability. So I ended up manaully shift
        # the bars to the the left for half of the probability and setting the
        # width equal to the probability
        avgStretchPlot[[i]] <- ggplot() + geom_step(data=tmp,
            aes(x=SizeCumPercent-SizeCntPercent/2, y=MeanStretch,
            width=SizeCntPercent, colour=TransportType), size=4)

        plotTitle <- paste(append(unlist(strsplit(plotTitle, split='')), '\n',
            as.integer(nchar(plotTitle)/2)), sep='', collapse='')

        xIntervals <- findInterval(c(0)+seq(2,102,10),
            tmp[tmp$TransportType=='homa',]$SizeCumPercent)

        avgStretchPlot[[i]] <- avgStretchPlot[[i]] +
            theme(text = element_text(size=1.5*textSize),
                axis.text = element_text(size=1.3*textSize),
                axis.text.x = element_text(angle=75, vjust=0.5),
                strip.text = element_text(size=textSize),
                plot.title = element_text(size=1.2*titleSize, color='darkblue'),
                plot.margin=unit(c(2,2,2.5,2.2),"cm"),
                legend.position = c(0.1, 0.85),
                legend.text = element_text(size=1.5*textSize)) +
            guides(colour = guide_legend(override.aes = list(size=textSize/4)))+
            scale_x_continuous(limits = c(0,101),
                breaks = tmp[xIntervals,]$SizeCumPercent,
                labels=tmp[xIntervals,]$MsgSizeRange, expand = c(0, 0)) +
            scale_y_log10(breaks=c(1,2,3,4,5,10,15)) +
            coord_cartesian(ylim=c(1, yLimit)) +
            labs(title = plotTitle, y = yLab, x = xLab)
    }
    pdf(sprintf("plots/MeanStretchVsTransport_rho%s.pdf", rho),
        width=40,
        height=20*length(unique(avgStretchVsSize$WorkLoad)))
    args.list <- c(avgStretchPlot, list(ncol=1))
    do.call(grid.arrange, args.list)
    dev.off()
}
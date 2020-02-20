# ggplot

### 1. General Usage 
  - ggplot(data, aes(x=a_axis_data, y = y_axis_data, col=col_s, shape=shape_s))
    + geom_point()
    
  - ggplot(data, aes(x=a_axis_data, y = y_axis_data, col=col_s, shape=shape_s))
    + geom_histogram(bin=variable, fill="color", col="color")
   
  - ggplot(data, aes(x=a_axis_data, fill= chosen_col))
    + geom_histogram(bin=variable, fill="color", col="color")
    
  - ggplot(data, aes(x=price, col=chosen_col)) + geom_freqpoly(bin=60)
  
  - ggplot(data, aes(x=price, col=chosen_col)) + geom_smooth()
  
  
    + ylim(a, b)
  

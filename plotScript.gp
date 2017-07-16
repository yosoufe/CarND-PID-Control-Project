reset
set size 1,1

set key left bottom

set multiplot

#first
set size 1,0.5
set origin 0,0.5
plot 'error' with lines title 'error'

#second
set origin 0,0
plot 'control_terms' using 1 with lines title 'Control Command', 'control_terms' using 2 with lines title 'Prop. Term', 'control_terms' using 3 with lines title 'Integral Term', 'control_terms' using 4 with lines title 'Derivative Term'


unset multiplot

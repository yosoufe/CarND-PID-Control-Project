# PID Controller Project Reflection:
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

[//]: # (Image References)
[image1]: ./Images/final.png "Final Design"
[image2]: ./Images/Jerky.png "Jerky Control"
[image3]: ./Images/LessJerk.png "Les Jerky Control"

When I started the project I made a lot of implementation mistakes which I could not get the controller working. I decided to plot online all the errors and controll commands and saw some problems in the plots and found implementaion problems like wrong equations for PID terms.


In order to design the controller I started with implementing the main body of the controller and started tuning the parameters. I decided to start with [Ziegler–Nichols method](https://en.wikipedia.org/wiki/Ziegler%E2%80%93Nichols_method). The problem here is that I did not have any idea about the sampling rate and how much time difference is between each run of the PID algorithm, therefore just using Ziegler–Nichols does not work and the controller should be retune a lot after these parameters set.

The controller has three parts and three kind of behavior:

1. Proportional Action: This part is responsible of the current value of error. Which is a constant multipied by the current value of error. The proportional constant should be chosen wisely because:

   if it is too low: The controller would be to slow until it reaches the reference and in sharp turns, the car would understeer.
   If it is too high: It will generate a lot of overshoot and oscilations and may also cause unstability in system.

2. Integral Action: This part compensate long term error and looking to past of the system. It symply adds up all the errors and multiply it by a constant. If there is something wrong with steering sysstem for example which for example zero degree of steering will would not cause the zero degree on tyres, the integral action would solve such issues.

   If it is too high: would cause a lot of oscilations and overshooting.
   If it is too low: system with a lot of uncertainity would have big steady state error.

3. Derivative Action: This part would damps the oscilations in the system. The Derivative action is looking into the future by calculating the difference of the two last errors. Therefore it can anticipate that we are reaching to the refernce and decreases the control command.

   If it is too low: The oscilations caused by proportional or integral actions would not be dampes and the system would be oscilatory.
   If it is too high: The derivation of the error is very sensitive to noises and if the term is too big, during the noisy the system would have jerky behaviour. For example in plot below you can see that there are a lot of jerk and sudden commands in the graph. Yellow line is showing the derivative term. Another probelm with too high derivative is again overshooting and unstability possibilities.

![alt text][image2]

The jerky behaviour can be decreased by low pas filtering on the error or the derivative term. This requires very accurate design because filtering would introduce some delay in the controller as well which can lead the car out of the road at sharp curves or high speeds. For example the following plot is showing a system with moving average filter on the derivative term which lead the car to very dangerous area at sharp turns but it is less jerky.

![alt text][image3]

The following plot is showing the final reaction of the system.

![alt text][image1]

## How to compile:
If you want to see the plots you should install the gnuplot
```
sudo apt install gnuplot
```

```
cd CarND-PID-Control-Project
mkdir build && cd build
ccmake ..
# turn on WITH_GUNPLOT if you want to have online plot but you have to intstall gnuplot
# type `c` and `g`
make
```

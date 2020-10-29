

29. Oct. 2020, Version 1.0.0: 
A simple automated cap to cover the telescope lense for an automated dark frame process. 
This cap is controlled as filterwheel with two positions (open,close) via this ASCOM driver.
Please install ASCOM >= 6.5 before you install this driver.
This device provides two "filters", cap open and cap closed. Setup in your imaging software
(e.g. N.I.N.A.) to use this filter wheel device and set the filter to open for light frames
and close for dark frames. Use the newest nightly build release of N.I.N.A. to have the scripting
engin for a full control of the filter wheel. 


This driver is for a simple shutter device camouflaged as filter wheel. 
This driver supports two "filters", one open, the other closed. For dark images
under EKOS select the closed filter. 

-------------------------------------------------------

# Install Pre-requisites

On Debian/Ubuntu:

	sudo apt-get install libindi-dev
	sudo apt install libcfitsio-dev

-------------------------------------------------------

# Build and install the indi-picamera driver

	cd ~/Projects
	
	git clone --depth=1 https://github.com/indilib/indi-3rdparty
	
	cd indi-3rdparty

	git clone https://......

	mkdir -p ~/Projects/build/indi-arduinofw

	cd ~/Projects/build/indi-arduinofw
	
	cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug ~/Projects/indi-3rdparty/indi-arduinofw

	make -j4

	sudo make install
	
-------------------------------------------------------


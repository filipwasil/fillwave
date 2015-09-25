if [[ `lsb_release -rs` == "12.04" ]]
then
echo "Please update version of Ubuntu. Installer will now gently fail ..."
echo "Installation failed."
fi

if [[ `lsb_release -rs` == "12.10" ]]
then
echo "Please update version of Ubuntu. Installer will now gently fail ..."
echo "Installation failed."
fi

if [[ `lsb_release -rs` == "13.04" ]]
then
echo "Please update version of Ubuntu. Installer will now gently fail ..."
echo "Installation failed."
fi

if [[ `lsb_release -rs` == "13.10" ]]
then
echo "Please update version of Ubuntu. Installer will now gently fail ..."
echo "Installation failed."
fi

if [[ `lsb_release -rs` == "14.04" ]]
echo "version of ubuntu 14.04. libglfw3 is most probably unavailable. Let us add it."
then
echo "deb http://ppa.launchpad.net/keithw/glfw3/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list.d/fillwave_ext.list
echo "deb-src http://ppa.launchpad.net/keithw/glfw3/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list.d/fillwave_ext.list
fi

echo "Adding fillwave web to software sources"
echo "deb http://filipwasil.bitbucket.org/downloads ./" | sudo tee -a /etc/apt/sources.list.d/fillwave.list
echo "#deb-src http://filipwasil.bitbucket.org/downloads ./" | sudo tee -a /etc/apt/sources.list.d/fillwave.list
sudo apt-get update

echo "Installation of needed packages"
sudo apt-get install libglew1.10 libglew-dev
sudo apt-get install libglfw3 libglfw3-dev -y --force-yes
sudo apt-get install libassimp3 libassimp-dev
sudo apt-get install libfreetype6 libfreetype6-dev libglm-dev libx11-dev libglm-dev

echo "Installation of fillwave"
sudo apt-get install libfillwave libfillwave-dev fillwave-examples -y --force-yes

echo "Installation succeeded."

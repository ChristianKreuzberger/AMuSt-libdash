# AMuSt-libdash

This is an extension of <a href="https://github.com/bitmovin/libdash">bitmovin/libdash</a> for the <a href="https://github.com/ChristianKreuzberger/AMuSt-Simulator">Adaptive Multimedia Streaming Simulation (AMuSt) Framework</a>.

# libdash

libdash is the **official reference software of the ISO/IEC MPEG-DASH standard** and is an open-source library that provides an object orient (OO) interface to the MPEG-DASH standard, developed by [bitmovin](http://www.bitmovin.com).


## How to use

Please look at the <a href="https://github.com/ChristianKreuzberger/AMuSt-Simulator/">Adaptive Multimedia Streaming Simulation Framework</a> for more details. If you are just interested in using the libdash library, please consult the <a href="https://github.com/bitmovin/libdash">bitmovin/libdash</a> github repository.

### Pre-Requesits (Todo: cleanup)

    sudo apt-get install build-essential gccxml
    sudo apt-get install git-core build-essential cmake libxml2-dev libcurl4-openssl-dev
    sudo apt-get install cmake libxml2-dev libcurl4-openssl-dev
    sudo apt-get install libxml2-dev libxslt-dev python-dev lib32z1-dev

### Build

    cd AMuSt-libdash/libdash
    mkdir build
    cd build
    cmake ../
    make

## libdash-License

libdash is open source available and licensed under LGPL:

“This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA“

As libdash is licensed under LGPL, changes to the library have to be published again to the open-source project, which we are doing with this github repository.


## Acknowledgement

This work (extension of libdash) was partially funded by the Austrian Science Fund (FWF) under the CHIST-ERA project CONCERT (A Context-Adaptive Content Ecosystem Under Uncertainty), project number I1402. See <a href="http://www.concert-project.org">www.concert-project.org</a> for more information about the CONCERT project.
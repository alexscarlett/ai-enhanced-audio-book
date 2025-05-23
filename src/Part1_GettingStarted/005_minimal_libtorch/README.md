# Additional Instructions for M1 Mac

You'll need to build libtorch manually to work on M1 chips.

Go here: https://github.com/pytorch/pytorch/blob/main/docs/libtorch.rst

Run this in your terminal, but double check the link above to see if anything has changed...

```
git clone -b main --recurse-submodule https://github.com/pytorch/pytorch.git
mkdir pytorch-build
cd pytorch-build
cmake -DBUILD_SHARED_LIBS:BOOL=ON -DCMAKE_BUILD_TYPE:STRING=Release -DPYTHON_EXECUTABLE:PATH=`which python3` -DCMAKE_INSTALL_PREFIX:PATH=../pytorch-install ../pytorch
cmake --build . --target install
```

# simple libtorch

Minimal example based on https://pytorch.org/cppdocs/installing.html.

Creates a tensor with libtorch and prints out its values.

To build this, download libtorch if you need it
(this downloads a pre-built version of libtorch):

```
cd where_you_want_libtorch_to_live
wget https://download.pytorch.org/libtorch/nightly/cpu/libtorch-shared-with-deps-latest.zip
unzip libtorch-shared-with-deps-latest.zip
```

Or on a mac, see mac install instructions in README_mac in upper folder.

Suffice to say that on a mac m1, you need to do your own build of
libtorch from source.

This will end up in a folder called pytorch/torch where pytorch is the top
level folder cloned from the pytorch github.

Clone this repo (in case you did not already):

```
cd where_you_want_the_repo
git clone git@github.com:yeeking/ai-audio-book.git
cd ai-audio-book/src/1_minimal_libtorch
```

Now build:

```
# this works on mac and linux
cmake -DCMAKE_PREFIX_PATH=/where_you_want_libtorch_to_live/libtorch -B
build .
# this works on mac if you want to generate an xcode project
cmake -G Xcode -DCMAKE_PREFIX_PATH=/Users/matthewyk/src/sw/pytorch/torch
-B build .
#
cd build
cmake --build . --config Release
```

Then run:

```
./simple-nn
```

You should see something like this:

```
 0.6519  0.2523  0.0700
 0.3544  0.8296  0.7805
[ CPUFloatType{2,3} ]
```

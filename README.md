ArrayFire Feature Threading Example
===================================

This is a simple example that demonstrates how accessing an af::features
object from multiple threads will crash in unpredictable ways.

Usage
-----

First, install [ArrayFire 3.7.2](http://arrayfire.org).  Make note of where
its `ArrayFire/cmake` path is so that you can set it in your `CMAKE_PREFIX_PATH` later.

By default it links in the CUDA backend.  Further notes on this below...

```bash
git clone https://github.com/pjreed/af_threading.git
cd af_threading
mkdir build
cd build
CMAKE_PREFIX_PATH=/path/to/ArrayFire/cmake cmake ..
make
./af_threads
```

`af_threads` should crash.  Note that if you run it multiple times, it will
often crash in different places and provide a different stack trace.

Interestingly, using the Unified backend and letting it automatically choose
seems to hide this behavior.  Every time it crashes, it will produce an error
message saying `Input array does not belong to current backend`.  Randomized
error messages only happen when it is linked to a specific backend.

Credits
-------

Book images were borrowed from [learnopencv.com](https://www.learnopencv.com/homography-examples-using-opencv-python-c/).

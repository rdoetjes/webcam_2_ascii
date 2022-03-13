# webcam_2_ascii

Build on mac with homebrew OpenCV requires clang

export CXX=/usr/bin/clang++
export CC=/usr/bin/clang

# Build instruction
Edit the CMakeFiles.txt to opint to your OpenCV directorys

```
cd webcam_2_ascii
mkdir build
cd build
cmake ..
make
```

# Running

For using the webcam
```
./ascii 
```

For showing a film stream in ascii
```
./ascii film.mp4
```

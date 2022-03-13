cmake_minimum_required(VERSION 3.19)
project(ascii)

set(CMAKE_CXX_STANDARD 11)

#Find OpenCV library
find_package( OpenCV 4 REQUIRED )
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV4 REQUIRED IMPORTED_TARGET opencv4)

set(OPENCV_INCLUDE_DIRS, "/opt/homebrew/include/opencv4")
set(OPENCV_LIBRARIES, "/opt/homebrew/lib")
set(ImageMagick_LIBRARIES, "/opt/homebrew/Cellar/graphicsmagick/1.3.37_1/include/GraphicsMagick/" )
set(ImageMagick_INCLUDE_DIRS, "/opt/homebrew/Cellar/graphicsmagick/1.3.37_1/lib/")

include_directories(/opt/homebrew/include/opencv4)
link_directories(/opt/homebrew/lib)
include_directories(/opt/homebrew/Cellar/graphicsmagick/1.3.37_1/include/GraphicsMagick/)
link_directories(/opt/homebrew/Cellar/graphicsmagick/1.3.37_1/lib/)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} -lstdc++ -lopencv_gapi -lopencv_stitching -lopencv_alphamat -lopencv_aruco -lopencv_barcode -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform -lopencv_line_descriptor -lopencv_mcc -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_highgui -lopencv_datasets -lopencv_text -lopencv_plot -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_wechat_qrcode -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs 
-lopencv_features2d -lopencv_dnn -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core
-lpthread -lGraphicsMagick++ -lGraphicsMagick -lz -ldl)

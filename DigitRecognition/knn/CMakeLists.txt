set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NAME "Putra")
message("This project has been created by ${NAME}.")

add_library(knn_library
            src/KNN.cpp)

target_include_directories(knn_library PUBLIC include)
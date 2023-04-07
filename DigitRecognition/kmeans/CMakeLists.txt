set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NAME "Putra")
message("This project has been created by ${NAME}.")

add_library(kmeans_library
            src/KMeans.cpp)

target_include_directories(kmeans_library PUBLIC include)
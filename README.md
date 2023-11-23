Step 1: Install package
+ Install git, msys2 mingw64 and add Path of environments
+ Install Python
+ Install grpc on msys2 mingw64
+ Install protobuf on msys2 mingw64

Step 2: Create File
+ Create .proto file
+ Build file "grpc.pb.cc", "grpc.pb.h", "pb.cc", "pb.h" using command
    - "protoc --cpp_out=. file_transfer.proto"
    - "protoc --grpc_out=. --plugin=protoc-gen-grpc="grpc_cpp_plugin.exe" file_transfer.proto"
+ create cmake file for protos, server and client

Step 3: Build project
+ mkdir build
+ cd build 
+ cmake .. 
+ cmake --build .
+ Run client.exe and server.exe in folder "build/client" and "build/server"
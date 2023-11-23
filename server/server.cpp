#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "../protos/file_transfer_lib/file_transfer.grpc.pb.h"
#include "../protos/file_transfer_lib/file_transfer.pb.h"
#include <fstream>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using filetransfer::FileRequest;
using filetransfer::FileResponse;
using filetransfer::FileTransfer;

class FileTransferServiceImpl final : public FileTransfer::Service {
    public:
        Status SendFile(ServerContext* context, const FileRequest* request, FileResponse* response) override {
            std::string filename = request->filename();
            
            //Open the file
            std::ifstream file(filename, std::ios::binary);
            if(!file.is_open()) {
                return Status(grpc::StatusCode::NOT_FOUND, "File not found");
            }

            //Read the file content

            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            //Set the file content in the response

            response->set_content(content);

            return Status::OK;
        }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    FileTransferServiceImpl service;

    ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "server listening on " << server_address << std::endl;
    server->Wait();
} 

int main() {
    RunServer();
    return 0;
}
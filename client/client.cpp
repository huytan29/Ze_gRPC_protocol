#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "../protos/file_transfer_lib/file_transfer.grpc.pb.h"
#include "../protos/file_transfer_lib/file_transfer.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using filetransfer::FileRequest;
using filetransfer::FileResponse;
using filetransfer::FileTransfer;

class FileTransferClient {
public:
    FileTransferClient(std::shared_ptr<Channel> channel) : stub(FileTransfer::NewStub(channel)) {}

    std::string SendFile(const std::string& filename) {
        FileRequest request;
        request.set_filename(filename);

        FileResponse response;
        ClientContext context;

        Status status = stub->SendFile(&context, request, &response);

        if (status.ok()) {
            return response.content();
        } else {
            std::cout << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
            return "";
        }
    }

private:
    std::unique_ptr<FileTransfer::Stub> stub;
};

int main() {
    std::string server_address("192.168.56.1:50051"); // Replace with the server address
    FileTransferClient client(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

    std::string filename = "../../server/hello.txt"; // Replace with your desired filename
    std::string fileContent = client.SendFile(filename);

    if (!fileContent.empty()) {
        std::cout << "Received file content:\n" << fileContent << std::endl;
    } else {
        std::cout << "Failed to receive file content." << std::endl;
    }

    return 0;
}

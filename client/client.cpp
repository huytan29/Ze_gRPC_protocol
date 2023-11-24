#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/grpcpp.h>
#include "../protos/file_transfer_lib/file_transfer.grpc.pb.h"
#include "../protos/file_transfer_lib/file_transfer.pb.h"
#include "../protos/session_lib/session.grpc.pb.h"
#include "../protos/session_lib/session.pb.h"
#include "class_session.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::Status;
using filetransfer::FileRequest;
using filetransfer::FileResponse;
using filetransfer::FileTransfer;
using session::Greeter;
using session::Reply;
using session::Request;
using session::SessionReply;

ABSL_FLAG(std::string, target, "localhost:50051", "Server address");


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

session_an Test;
class SessionClient {
public:
  SessionClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  void SessionCall() {
    ClientContext context;
    Request request;
    std::shared_ptr<ClientReader<SessionReply>> reader(
        stub_->SessionInfor(&context, request));

    SessionReply reply;
    while (reader->Read(&reply)) {
      Test.init(reply.key(), reply.session_id());
      Test.addModel(reply.filename(), reply.data());
    }

    Status status = reader->Finish();
    if (status.ok()) {
      std::cout << "Call Session rpc succeeded." << std::endl;
    } else {
      std::cout << "Call Session rpc failed: " << status.error_message() << std::endl;
    }
  }

private:
  std::unique_ptr<Greeter::Stub> stub_;
};

void GetSession(int argc, char **argv) {
  absl::ParseCommandLine(argc, argv);
  std::string target_str = absl::GetFlag(FLAGS_target);

  SessionClient sessionClient(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

  sessionClient.SessionCall();
  Test.showModel();
}

int main(int argc, char **argv) {
    // Rest of the code remains the same as before
    GetSession(argc, argv);

    // Existing file transfer client code
    std::string server_address("localhost:50051"); // Replace with the server address
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


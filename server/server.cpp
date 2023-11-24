#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/grpcpp.h>
#include "../protos/file_transfer_lib/file_transfer.grpc.pb.h"
#include "../protos/file_transfer_lib/file_transfer.pb.h"
#include "../protos/session_lib/session.grpc.pb.h"
#include "../protos/session_lib/session.pb.h"

using filetransfer::FileRequest;
using filetransfer::FileResponse;
using filetransfer::FileTransfer;
using grpc::Server;
using grpc::ServerAsyncWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using session::Greeter;
using session::Reply;
using session::Request;
using session::SessionReply;


class GreeterServiceImpl final : public Greeter::Service {
public:
    Status SayHello(ServerContext* context, const Request* request, Reply* reply) override {
        std::string prefix("Get session ");
        reply->set_message(prefix + request->name());
        return Status::OK;
    }

    Status SessionInfor(ServerContext* context, const Request* request, ServerWriter<SessionReply>* reply) override {
        // Tạo các thông tin phiên mới mỗi khi có yêu cầu từ client
        session::SessionReply newsession;
        newsession.set_session_id("sessionId-123-456-789");
        newsession.set_key("key-123456");

        reply->Write(newsession); // Gửi thông tin phiên đầu tiên

        // Gửi các thông tin phiên bổ sung
        sendSessionInformation(reply, "w3.txt", "2 3 1.2 2.3 3.4 4.5 5.6 6.7");
        sendSessionInformation(reply, "w2.txt", "2 3 1 11 1 1 1 1");
        sendSessionInformation(reply, "w1.txt", "2 3 1 11 1 1 1 1");

        return Status::OK;
    }

private:
    // Helper function to send session information
    void sendSessionInformation(ServerWriter<SessionReply>* reply, const std::string& filename, const std::string& data) {
        session::SessionReply newsession;
        newsession.set_filename(filename);
        newsession.set_data(data);
        reply->Write(newsession);
    }
};


class FileTransferServiceImpl final : public FileTransfer::Service
{
public:
  Status SendFile(ServerContext *context, const FileRequest *request, FileResponse *response) override
  {
    std::string filename = request->filename();

    // Open the file
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
      return Status(grpc::StatusCode::NOT_FOUND, "File not found");
    }

    // Read the file content

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Set the file content in the response

    response->set_content(content);

    GreeterServiceImpl greeterService;
    Request request_;
    Reply reply;

    request_.set_name("File Transfer Service");
    greeterService.SayHello(context, &request_, &reply);

    return Status::OK;
  }
};


void RunServer()
{
  std::string server_address("localhost:6000");
  FileTransferServiceImpl fileTransferService;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&fileTransferService);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main()
{
  RunServer();
  return 0;
}
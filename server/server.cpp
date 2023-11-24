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

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerAsyncWriter;
using grpc::ServerWriter;
using grpc::Status;
using filetransfer::FileRequest;
using filetransfer::FileResponse;
using filetransfer::FileTransfer;
using session::Greeter;
using session::Reply;
using session::Request;
using session::SessionReply;

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

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service
{
  public:
  Status SayHello(ServerContext *context, const Request *request,
                  Reply *reply) override
  {
    std::string prefix("Get session ");
    reply->set_message(prefix + request->name());
    return Status::OK;
  }

  Status SessionInfor(ServerContext *context, const Request *request,
                      ServerWriter<SessionReply> *reply) override
  {
    // std::string prefix("mod.txt");
    // reply->set_session_id("123-4556-789");
    // reply->set_data("2 3 1 2 3 4 5 6");
    // reply->set_filename(prefix);
    session::SessionReply newsession;
    newsession.set_session_id("sessionId-123-456-789");
    newsession.set_key("key-123456");
    session_list.push_back(newsession);
    reply->Write(newsession);
    newsession.set_filename("w3.txt");
    newsession.set_data("2 3 1.2 2.3 3.4 4.5 5.6 6.7");
    session_list.push_back(newsession);
    newsession.set_filename("w2.txt");
    newsession.set_data("2 3 1 11 1 1 1 1");
    session_list.push_back(newsession);
    newsession.set_filename("w1.txt");
    newsession.set_data("2 3 1 11 1 1 1 1");
    session_list.push_back(newsession);
    for (const SessionReply& f : session_list)
    {
      f.filename();
      f.session_id();
      f.data();
      f.key();
      reply->Write(f);
    }
    session_list.clear();
    return Status::OK;
  }
  private:
  std::vector<SessionReply> session_list;
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    GreeterServiceImpl greeterService;
    FileTransferServiceImpl fileTransferService;

    ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&greeterService); // Register Greeter service
    builder.RegisterService(&fileTransferService); // Register FileTransfer service

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}


int main() {
    RunServer();
    return 0;
}
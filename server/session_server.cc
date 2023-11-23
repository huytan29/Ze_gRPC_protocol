#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>


#include "../protos/session_lib/session.grpc.pb.h"
#include "../protos/session_lib/session.pb.h"

using grpc::Server;
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

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

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

void RunServer(uint16_t port)
{
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char **argv)
{
  absl::ParseCommandLine(argc, argv);
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}

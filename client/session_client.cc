#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include <grpcpp/grpcpp.h>
#include "class_session.h"
#include "../protos/session_lib/session.grpc.pb.h"
#include "../protos/session_lib/session.pb.h"


ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::Status;
using session::Greeter;
using session::Reply;
using session::Request;
using session::SessionReply;

session_an Test;
class SessionClient
{
public:
  SessionClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  void SessionCall()
  {
    SessionReply reply;
    ClientContext context;
    Request request;
    std::unique_ptr<ClientReader<SessionReply>> reader(
        stub_->SessionInfor(&context, request));
    while (reader->Read(&reply))
    {
      // std::cout << "Test message\n";
      // Test.init(key,id);
      Test.init(reply.key(), reply.session_id());
      Test.addModel(reply.filename(), reply.data());
    }
    //
    Status status = reader->Finish();
    if (status.ok())
    {
      std::cout << "Call Session rpc succeeded." << std::endl;
    }
    else
    {
      std::cout << "Call Session rpc failed." << std::endl;
    }
  }

private:
  std::unique_ptr<Greeter::Stub> stub_;
};

void GetSession(int argc, char **argv)
{
  absl::ParseCommandLine(argc, argv);
  std::string target_str = absl::GetFlag(FLAGS_target);
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).

  SessionClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

  std::string user("Session_ID");
  greeter.SessionCall();
  // std::string reply = greeter.GetSession(user);

  // // test session
  // std::cout << "Value model: " << reply << std::endl;
  // Test.addModel("W1.txt",reply);

  Test.showModel();
}
int main(int argc, char **argv)
{
  GetSession(argc, argv);

  std::cout << Test.get_key() << " : "<< Test.get_session_id() << "\n";
  std::string model_name;
//
    std::cin >> model_name;
    std::cout << "Get model: " << model_name << "\n";
    for (const auto &row : Test.getModelbyName(model_name).matrix)
    {
      for (double element : row)
      {
        std::cout << element << " ";
      }
      std::cout << "\n";
    }
//
  Test.cleanModel();
  return 0;
}

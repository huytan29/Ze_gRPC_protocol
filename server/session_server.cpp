#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/grpcpp.h>
#include "../protos/session_lib/session.grpc.pb.h"
#include "../protos/session_lib/session.pb.h"
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

using grpc::Greeter;
using grpc::Reply;
using grpc::Request;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::SessionReply;
using grpc::Status;

class GreeterServiceImpl final : public Greeter::Service
{
public:
    Status GetSession(ServerContext *context, const Request *request,
                      Reply *rely) override
    {
        std::string prefix("Get session");
        reply->set_message(prefix + request->name());
        return Status::OK;
    }

    Status SessionInfor(ServerContext *context, const Request *request, ServerWriter<SessionReply> *rely) override
    {
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
        for (const SessionReply &f : session_list)
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
// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: file_transfer.proto

#include "file_transfer.pb.h"
#include "file_transfer.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace filetransfer {

static const char* FileTransfer_method_names[] = {
  "/filetransfer.FileTransfer/SendFile",
};

std::unique_ptr< FileTransfer::Stub> FileTransfer::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< FileTransfer::Stub> stub(new FileTransfer::Stub(channel, options));
  return stub;
}

FileTransfer::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_SendFile_(FileTransfer_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status FileTransfer::Stub::SendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::filetransfer::FileResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::filetransfer::FileRequest, ::filetransfer::FileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SendFile_, context, request, response);
}

void FileTransfer::Stub::async::SendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest* request, ::filetransfer::FileResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::filetransfer::FileRequest, ::filetransfer::FileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendFile_, context, request, response, std::move(f));
}

void FileTransfer::Stub::async::SendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest* request, ::filetransfer::FileResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendFile_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::filetransfer::FileResponse>* FileTransfer::Stub::PrepareAsyncSendFileRaw(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::filetransfer::FileResponse, ::filetransfer::FileRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SendFile_, context, request);
}

::grpc::ClientAsyncResponseReader< ::filetransfer::FileResponse>* FileTransfer::Stub::AsyncSendFileRaw(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSendFileRaw(context, request, cq);
  result->StartCall();
  return result;
}

FileTransfer::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FileTransfer_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< FileTransfer::Service, ::filetransfer::FileRequest, ::filetransfer::FileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](FileTransfer::Service* service,
             ::grpc::ServerContext* ctx,
             const ::filetransfer::FileRequest* req,
             ::filetransfer::FileResponse* resp) {
               return service->SendFile(ctx, req, resp);
             }, this)));
}

FileTransfer::Service::~Service() {
}

::grpc::Status FileTransfer::Service::SendFile(::grpc::ServerContext* context, const ::filetransfer::FileRequest* request, ::filetransfer::FileResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace filetransfer


// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: file_transfer.proto
#ifndef GRPC_file_5ftransfer_2eproto__INCLUDED
#define GRPC_file_5ftransfer_2eproto__INCLUDED

#include "file_transfer.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace filetransfer {

class FileTransfer final {
 public:
  static constexpr char const* service_full_name() {
    return "filetransfer.FileTransfer";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status SendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::filetransfer::FileResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::filetransfer::FileResponse>> AsyncSendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::filetransfer::FileResponse>>(AsyncSendFileRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::filetransfer::FileResponse>> PrepareAsyncSendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::filetransfer::FileResponse>>(PrepareAsyncSendFileRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void SendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest* request, ::filetransfer::FileResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void SendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest* request, ::filetransfer::FileResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::filetransfer::FileResponse>* AsyncSendFileRaw(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::filetransfer::FileResponse>* PrepareAsyncSendFileRaw(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status SendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::filetransfer::FileResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::filetransfer::FileResponse>> AsyncSendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::filetransfer::FileResponse>>(AsyncSendFileRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::filetransfer::FileResponse>> PrepareAsyncSendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::filetransfer::FileResponse>>(PrepareAsyncSendFileRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void SendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest* request, ::filetransfer::FileResponse* response, std::function<void(::grpc::Status)>) override;
      void SendFile(::grpc::ClientContext* context, const ::filetransfer::FileRequest* request, ::filetransfer::FileResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::filetransfer::FileResponse>* AsyncSendFileRaw(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::filetransfer::FileResponse>* PrepareAsyncSendFileRaw(::grpc::ClientContext* context, const ::filetransfer::FileRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_SendFile_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status SendFile(::grpc::ServerContext* context, const ::filetransfer::FileRequest* request, ::filetransfer::FileResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_SendFile : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_SendFile() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_SendFile() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendFile(::grpc::ServerContext* /*context*/, const ::filetransfer::FileRequest* /*request*/, ::filetransfer::FileResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendFile(::grpc::ServerContext* context, ::filetransfer::FileRequest* request, ::grpc::ServerAsyncResponseWriter< ::filetransfer::FileResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_SendFile<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_SendFile : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_SendFile() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::filetransfer::FileRequest, ::filetransfer::FileResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::filetransfer::FileRequest* request, ::filetransfer::FileResponse* response) { return this->SendFile(context, request, response); }));}
    void SetMessageAllocatorFor_SendFile(
        ::grpc::MessageAllocator< ::filetransfer::FileRequest, ::filetransfer::FileResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::filetransfer::FileRequest, ::filetransfer::FileResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_SendFile() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendFile(::grpc::ServerContext* /*context*/, const ::filetransfer::FileRequest* /*request*/, ::filetransfer::FileResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* SendFile(
      ::grpc::CallbackServerContext* /*context*/, const ::filetransfer::FileRequest* /*request*/, ::filetransfer::FileResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_SendFile<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_SendFile : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_SendFile() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_SendFile() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendFile(::grpc::ServerContext* /*context*/, const ::filetransfer::FileRequest* /*request*/, ::filetransfer::FileResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_SendFile : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_SendFile() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_SendFile() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendFile(::grpc::ServerContext* /*context*/, const ::filetransfer::FileRequest* /*request*/, ::filetransfer::FileResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendFile(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_SendFile : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_SendFile() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->SendFile(context, request, response); }));
    }
    ~WithRawCallbackMethod_SendFile() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendFile(::grpc::ServerContext* /*context*/, const ::filetransfer::FileRequest* /*request*/, ::filetransfer::FileResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* SendFile(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_SendFile : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_SendFile() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::filetransfer::FileRequest, ::filetransfer::FileResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::filetransfer::FileRequest, ::filetransfer::FileResponse>* streamer) {
                       return this->StreamedSendFile(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_SendFile() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SendFile(::grpc::ServerContext* /*context*/, const ::filetransfer::FileRequest* /*request*/, ::filetransfer::FileResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSendFile(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::filetransfer::FileRequest,::filetransfer::FileResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_SendFile<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_SendFile<Service > StreamedService;
};

}  // namespace filetransfer


#endif  // GRPC_file_5ftransfer_2eproto__INCLUDED
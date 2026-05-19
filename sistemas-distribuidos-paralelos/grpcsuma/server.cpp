#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include "sum.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using sum::SumRequest;
using sum::SumResponse;
using sum::SumService;

class SumServiceImpl final : public SumService::Service {
	Status Sum(ServerContext* context, const SumRequest* request,
				SumResponse* response) override {
 					std::cout << "Sumando: " << request->num1() << " + " << request->num2() 
																			<< std::endl;
 					int result = request->num1() + request->num2();
					response->set_result(result);
					return Status::OK;
				}
};

void RunServer() {
	std::string server_address("0.0.0.0:50051");
	SumServiceImpl service;

	ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);

	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;
	server->Wait();
}

int main() {
	RunServer();
	return 0;
}


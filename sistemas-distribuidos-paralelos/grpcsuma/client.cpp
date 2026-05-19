#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include "sum.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using sum::SumRequest;
using sum::SumResponse;
using sum::SumService;

class SumClient {
public:
	SumClient(std::shared_ptr<Channel> channel)
		: stub_(SumService::NewStub(channel)) {}

	int Sum(int num1, int num2) {
		SumRequest request;
		request.set_num1(num1);
		request.set_num2(num2);

		SumResponse response;
		ClientContext context;
		Status status = stub_->Sum(&context, request, &response);
		if (status.ok()) {
			return response.result();
		} else {
			std::cout <<"RPC failed with status: " << status.error_code() << ": "
					<< status.error_message() << std::endl;
			return -1;
		}
	}
private:
	std::unique_ptr<SumService::Stub> stub_;
};

int main(int argc, char *argv[]) {
		if(argc != 4){
			std::cout<<"Uso: " << argv[0] << " num1 num2 dir_ip"<<std::endl;
			exit(1);
		}
		std::string dir_puerto = argv[3];
		dir_puerto+=":50051";
		std::string server_address(dir_puerto);
		SumClient client(grpc::CreateChannel(server_address,
		grpc::InsecureChannelCredentials()));
		int num1 = atoi(argv[1]), num2 = atoi(argv[2]);
		int result = client.Sum(num1, num2);
		if (result != -1) {
			std::cout << "Result: " << result << std::endl;
		}
		return 0;
}

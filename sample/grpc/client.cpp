#include <stdio.h>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "data_service.grpc.pb.h"


int main()
{
    std::unique_ptr<tdpkg::DataService::Stub> stub = tdpkg::DataService::NewStub(grpc::CreateChannel("127.0.0.1:50010", grpc::InsecureChannelCredentials()));

    tdpkg::DataReq req;
    tdpkg::DataResp resp;

    req.set_ra(1);
    req.set_rb(2);
    req.set_rc("3");

    grpc::ClientContext context;
    grpc::Status status = stub->GetData(&context, req, &resp);
    if(!status.ok())
    {
        printf("grpc Data failed\n");
        return -1;
    }

    printf("%d-%u %s\n", resp.rsa(), resp.rsb(), resp.rsc().c_str());
    int cnt = resp.datas_size();
    for (int i = 0; i < cnt; i ++)
    {
        const tdpkg::Data &d = resp.datas(i);
        printf("%ld-%lu %d-%u %s\n",
               d.da(), d.db(), d.dc(), d.dd(), d.de().c_str());
    }

    return 0;
}

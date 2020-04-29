#include "Raft.h"

Raft::Raft(int num_servers): num_servers(num_servers) {
    // start the specified amount of servers(threads)
    for (int i=0; i<num_servers; i++) {
        Server* svr = new Server(i, this);
        servers.push_back(svr);
    }

    for (int i=0; i<num_servers; i++) {
        handles.push_back(std::thread(&Server::eventLoop, servers[i]));
    }
}

void Raft::crashServer(int serverId) {
    assert(serverId < num_servers);

    servers[serverId]->crash();
}

void Raft::restartServer(int serverId) {
    assert(serverId < num_servers);

    servers[serverId]->restart();
}

ClientRequestResponse Raft::clientRequestRPC(int serverId, string stateMachineCommand) {
    assert(serverId < num_servers);
    vector<string> parts;
    split1(stateMachineCommand, parts);
    ClientRequest request;
    request.key = parts[0];
    if (parts.size() > 1) {
        request.valueDelta = stoi(parts[1]);
    } else {
        request.valueDelta = 0;
    }

    std::promise<ClientRequestResponse> p;
    auto f = p.get_future();
    std::thread t(&Server::clientRequest, servers[serverId], request, std::move(p));
    t.join();
    return f.get();
}

void Raft::syncCout(string msg) {
    outputLock.lock();
    cout << msg << endl;
    outputLock.unlock();
}
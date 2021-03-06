# Raft
Pengcheng Rong \
Aaron Chang

### Build and Run
```make``` \
Interactive mode:\
```./raft.o```\
Input file mode:\
```./raft.o < test/test_election_simple.txt```

### Command Line Interface
StartRaft [num_servers] [timeout_type]
   - num_servers (int)             : number of initial server threads to create
   - timeout_type (int, default=0) : 0 for deterministic election timeouts, any other int for random

Sleep [num_seconds]

CrashServer [server_id] \
RestartServer [server_id]
   - server_id (int)               : server id to crash

Request [server_id] [key] [value]
   - key (string)                  : key for state machine, i.e. X
   - value (int, optional)         : leave blank for read request, provide int for delta to apply to state machine

ConfigChange [server_id] [ids]
   - ids (string)                  : list of server ids to change configuration to, without spaces i.e. 0,6,3,2,100

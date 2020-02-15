# server-client-model
Implementation and testing of multiple server models that achieve high concurrency.


### Getting started
1.Clone the project

```sh
git clone https://github.com/Boooooots/server-client-model.git
```
2.Build

```sh
gcc client.c -o client
gcc server_poll.c -o sp
gcc server_multithread.c -o sm -lpthread
```

3.Run the multithread-server and clients

```sh
./sm
./client.sh 1
```
4.Run the poll-server and clients

```sh
./sp
./client.sh 1
```

### Notes
1.client.sh : Start multiple clients base on first parameter value(1~1000).
2.The server address adapted to your local machine.


### Performance Test
**Multithreaded server consume more memory and CPU resources than poll server. **


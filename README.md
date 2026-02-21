# TCP Client–Server Implementation (C++)

A minimal C++ implementation of a TCP client and server demonstrating socket programming fundamentals, bidirectional communication, and basic network protocol handling.

This project showcases low-level networking concepts and the POSIX socket API.

---

## Overview

This repository contains:

- A TCP server that listens on a specified port  
- A TCP client that connects to the server  
- Bidirectional string-based message passing between client and server  

The project focuses on clean separation of concerns, basic connection lifecycle handling, and reliable message transmission using TCP.

---

## Features

- TCP socket creation and configuration  
- Client-server connection establishment  
- Blocking send/receive loop  
- Graceful connection teardown  
- Simple string-based message exchange  

---

## Tech Stack

- **Language:** C++  
- **Networking:** POSIX socket API  
- **Build System:** CMake

---

## Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

--- 

## Usage 

Start the server by running the server executable, and passing the port number:

```bash
./server <port>
```

Start the client in another terminal, and passing the IP Address and port number:

```bash
./client <server_ip> <port>
```

Send messages via the client, and examine the server log files following execution.

--- 

## Author 

Jack Newcomb

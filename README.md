## About
- Build your own Redis project

## Run application
- Requirements: Linux or UNIX-like systems
- Compile
```
g++ -Wall -Wextra -O2 -g server.cpp -o server
g++ -Wall -Wextra -O2 -g client.cpp -o client
```
- Compile with dependency
```
g++ -o server server.cpp hash_table.cpp
```
- Run
./server
./client
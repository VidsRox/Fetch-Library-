# Fetch Library in C - Built from Scratch

A minimal HTTP client library written in C without using standard networking libraries like libcurl or even libc networking functions. This project uses direct Linux system calls to interact with the kernel.

## About This Project

This is my attempt at building a fetch library from the ground up. I started by coding along with [Dr. Jonas Birch's HTTP fetch library video](https://youtu.be/A8kiEAxo080?si=OuRKisgYsxSAKlWY), but decided to extend it into a complete end-to-end implementation to deeply understand:

- C programming fundamentals
- Pointer manipulation and memory management
- Networking concepts (TCP/IP, sockets, HTTP)
- Low-level systems programming
- Direct system call usage

Before starting this project, I knew next to nothing about these concepts. Claude AI was instrumental in helping me understand how everything works under the hood - from byte-order conversion to TCP handshakes.

While I now have a much better understanding of these concepts than I ever did back in college, I recognize that I'll need to practice with more projects to develop a truly concrete grasp of low-level programming and networking.

## What It Does

The library currently supports:
- ✅ TCP socket creation via direct syscalls
- ✅ HTTP/1.1 request construction
- ✅ HTTP response parsing
- ✅ Manual byte-order conversion (htons/htonl)
- ✅ Zero external dependencies (no libcurl, no standard network libs)

## Architecture

```
Application Layer (grab.c)
         ↓
    HTTP Layer (http.c, fetch.c)
         ↓
   Network Layer (network.c)
         ↓
    System Calls (Linux kernel)
```

### Components

| File | Purpose |
|------|---------|
| `grab.c` | Application entry point and demo |
| `fetch.c` | Orchestrates request/response cycle |
| `http.c` | HTTP protocol formatting and parsing |
| `network.c` | Socket operations via syscalls |
| `utils.c` | Helper functions (string ops, byte conversion) |

## Building and Running

```bash
make
./grab
```

Example output:
```
Fetching http://www.google.com/
Connected successfully!
Sending request:
GET / HTTP/1.1
Host: www.google.com
User-Agent: FetchLibC/1.0
Connection: close

Received 6848 bytes

=== RESPONSE ===
Status: 200
Content-Type: text/html; charset=ISO-8859-1
Body size: 5373 bytes
```

## What I Learned

### Networking Concepts
- **TCP Three-Way Handshake**: How connections are established (SYN, SYN-ACK, ACK)
- **Socket Programming**: Creating, connecting, sending, receiving, closing
- **HTTP Protocol**: Request/response structure, headers, methods, status codes
- **Byte Order**: Network (big-endian) vs host (little-endian) byte order
- **IP Addressing**: Converting dotted-decimal notation to binary format

### Systems Programming
- **System Calls**: Direct kernel interaction via `syscall()`
- **File Descriptors**: How sockets are just file descriptors
- **Memory Management**: Stack vs heap, malloc/free patterns
- **Pointer Arithmetic**: Walking through buffers, zero-copy techniques
- **String Manipulation**: Building requests, parsing responses without libc

### Key Implementation Details

**Network Byte Order Conversion:**
```c
// Converting port 80 to network byte order
addr.port = htons(80);  // 0x0050 → 0x5000

// Converting IP address
addr.addr = inet_addr("142.250.182.100");  // String → binary
```

**Direct System Calls:**
```c
// Create socket without using socket() from libc
int32 socket_create(int32 domain, int32 type, int32 protocol) {
    long ret = syscall(SYS_socket, domain, type, protocol);
    return (ret < 0) ? -1 : (int32)ret;
}
```

**Zero-Copy Parsing:**
```c
// Response data points directly into buffer (no copying)
resp->data = (int8 *)body_start;  
resp->size = strlen(body_start);
```

## Current Limitations

- ❌ Hardcoded IP addresses (no DNS resolution yet)
- ❌ HTTP only (no HTTPS/TLS support)
- ❌ Single-threaded (blocking I/O)
- ❌ No chunked transfer encoding support
- ❌ No HTTP redirect following
- ❌ No timeout handling

## Next Steps: Phase 8 - Concurrency

After studying concurrency and threading concepts, I plan to extend this library to handle multiple simultaneous requests efficiently. The current implementation is single-threaded and blocking, which means it can only handle one request at a time.

### Key Concepts Studied
- TCP/IP stack layers
- Socket states and lifecycle
- HTTP message structure
- Memory layout (stack/heap/rodata)
- Endianness and byte ordering


## Feel free to learn from this code!

---

**Note**: This is a learning project, not production-ready code. It's designed to understand networking from first principles, not to replace robust libraries like libcurl.
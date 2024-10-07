<!--   my-ticker -->    
<!-- &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;[![Typing SVG](https://readme-typing-svg.herokuapp.com?color=%F0E68C&center=true&vCenter=true&width=250&lines=Registry+Stagger-Reader"")](https://git.io/typing-svg) -->

<p align="center">
  <a href="https://git.io/typing-svg">
    <img src="https://readme-typing-svg.herokuapp.com?color=%F0E68C&center=true&vCenter=true&width=250&lines=Registry+Stagger-Reader" alt="Typing SVG">
  </a>
</p>

# Registry Stagger-Reader: Injecting Shellcode from Windows Registry

This repository demonstrates a malware model that reads XOR-encrypted shellcode from the Windows Registry, decrypts it, and injects it into a remote process. The project is written in C and showcases basic techniques in shellcode injection and process manipulation.

## Features

- **Registry Shellcode Storage**: Shellcode is stored in a specific registry key and read by the malware during execution.
- **XOR Encryption/Decryption**: The shellcode is encrypted with XOR and decrypted dynamically before injection.
- **Process Injection**: Injects shellcode into a target process using `CreateRemoteThread`.

## Technical Overview

### 1. XOR Shellcode Encryption
- **Encryption**: Shellcode is XOR-encrypted using a single-byte key (`0x46`).
- **Decryption**: The malware reads the encrypted shellcode from the registry and decrypts it before injecting.

### 2. Process Injection
- **OpenProcess**: Opens a handle to the target process for shellcode injection.
- **Memory Allocation**: Allocates memory in the target process using `VirtualAllocEx`.
- **Injection**: Writes the shellcode to the allocated memory and executes it using `CreateRemoteThread`.

## Usage

1. **Clone the Repository**: Download the project and compile it with Visual Studio or another compatible compiler.
2. **Run the Malware**: Execute the compiled binary, passing the target process ID (PID) and thread ID (TID) as arguments.

    ```bash
    Registry_Stagger-Reader.exe <PID> <TID>
    ```

### Example:
```bash
Registry_Stagger-Reader.exe 1234 5678


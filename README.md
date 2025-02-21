# XYZ AI Agent Framework (CLI)

![New Project](https://github.com/user-attachments/assets/906acef6-f088-4d42-8c2a-7d95bdf8a50a)

![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![C++](https://img.shields.io/badge/C++-17-orange)

XYZ is a high-performance, C++-based AI agent framework designed for real-time data processing, low-latency interactions, and scalable multi-agent environments. This repository contains the CLI (Command Line Interface) version of the framework.

**Looking for the UI version?** Visit [https://xyzagents.xyz/](https://xyzagents.xyz/)

## Features

- **Autonomous Agents** - Create independent AI agents that process real-time data with millisecond latency
- **Multi-Agent Systems** - Build collaborative agent networks that communicate and coordinate
- **Real-Time Processing** - Handle streaming data efficiently with optimized C++ performance
- **Cross-Language Integration** - Seamless integration with Python, Rust, and Go
- **Extensible Architecture** - Plug-and-play with custom AI models and external APIs
- **Comprehensive CLI** - Full control of the agent ecosystem through command-line interface

## Requirements

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 19.14+)
- CMake 3.12 or higher
- Google Test (for building tests)
- JsonCpp
- pthread library

## Installation

### From Source

```bash
# Clone the repository
git clone https://github.com/xyzlabs/xyz-framework.git
cd xyz-framework

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
make

# Install (optional)
sudo make install
```

### Package Managers

```bash
# Ubuntu/Debian
sudo apt install libxyz-dev

# macOS
brew install xyz-framework

# Windows (vcpkg)
vcpkg install xyz-framework
```

## Usage

### Starting the CLI

```bash
xyz_cli
```

You'll see the XYZ ASCII art banner and an interactive prompt:

```
$$\   $$\ $$\     $$\ $$$$$$$$\ 
$$ |  $$ |\$$\   $$  |\____$$  |
\$$\ $$  | \$$\ $$  /     $$  / 
 \$$$$  /   \$$$$  /     $$  /  
 $$  $$<     \$$  /     $$  /   
$$  /\$$\     $$ |     $$  /    
$$ /  $$ |    $$ |    $$$$$$$$\ 
\__|  \__|    \__|    \________|

XYZ AI Agent Framework CLI v1.0.0
Type 'help' for available commands

xyz>
```

### Common Commands

| Command | Description | Example |
|---------|-------------|---------|
| `help` | Display help information | `help` |
| `version` | Show version information | `version` |
| `create <type>` | Create a new agent | `create autonomous_agent` |
| `list` | List all active agents | `list` |
| `start <id>` | Start an agent | `start agent_1234` |
| `stop <id>` | Stop an agent | `stop agent_1234` |
| `status` | Display system status | `status` |
| `exit` | Exit the CLI | `exit` |

### Creating an Agent

```
xyz> create autonomous_agent
Creating new agent of type: autonomous_agent
Agent created successfully with ID: agent_1234
```

### Programming with XYZ

Include the necessary headers in your C++ application:

```cpp
#include <xyz/agent.hpp>
#include <xyz/model.hpp>
#include <xyz/utils.hpp>

int main() {
    // Initialize an agent
    auto agent = xyz::Agent::create("neural_agent");
    agent->initialize();
    agent->start();
    
    // Process data
    std::vector<float> input = {1.0f, 2.0f, 3.0f};
    agent->processData(input);
    auto output = agent->getOutput();
    
    // Cleanup
    agent->stop();
    return 0;
}
```

## Examples

The repository includes example applications in the `app/examples/` directory:

1. **Real-time Data Processing** (`example_1.cpp`) - Demonstrates how to process streaming data with multiple agents
2. **Multi-Agent Collaboration** (`example_2.cpp`) - Shows how multiple agents can work together to solve complex tasks

Run the examples after building:

```bash
./bin/examples/example_1
./bin/examples/example_2
```

## Configuration

XYZ can be configured through JSON config files:

```json
{
  "version": "1.0.0",
  "log_level": "INFO",
  "max_agents": 100,
  "debug_mode": false,
  
  "network": {
    "port": 8080,
    "host": "localhost",
    "max_connections": 1000
  }
}
```

Load a configuration file:

```bash
xyz_cli
xyz> load_config path/to/config.json
```

## Performance

XYZ is designed for high-performance applications:

- **Agent Creation**: <1ms
- **Data Processing**: ~50μs per operation
- **Memory Footprint**: ~500KB per agent
- **Max Agents**: 10,000+ on standard hardware

## License

XYZ is a product of XYZ Labs, released under the MIT License. See the [LICENSE](LICENSE) file for details.

## Support

- **Website**: [https://xyzailabs.com/](https://xyzailabs.com/)
- **Documentation**: [https://xyzlabsdocs.xyz/](https://xyzlabsdocs.xyz/)
- **Discord**: [https://discord.com/invite/xyzlabs](https://discord.com/invite/xyzlabs)
- **Twitter**: [https://x.com/xyzdotlabs](https://x.com/xyzdotlabs)


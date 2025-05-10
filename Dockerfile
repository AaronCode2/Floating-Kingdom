FROM ubuntu:latest

# Install required packages
RUN apt update && apt install -y build-essential cmake

# Set working directory
WORKDIR /app

# Copy source code into container
COPY . .

# Create build dir, run cmake & make
RUN mkdir -p build && cd build && cmake .. && make

# Run the compiled binary
CMD ["./build/Floating_Kingdom"]
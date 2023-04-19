# Use an official Ubuntu base image
FROM debian:latest

# Set the working directory to /app
WORKDIR /app

# Update apt package manager and install necessary dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

# Copy the C++ web server code into the container
COPY server.cpp .

# Build the C++ web server
RUN g++ -o web_server server.cpp -lws2_32

# Expose the port to run the web server
EXPOSE 8080

# Run the C++ web server
CMD ["./web_server"]
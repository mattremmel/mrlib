//
// Socket.hpp
// mrlib
//
// Created by Matthew Remmel on 2/18/16.
// Copyright (c) 2015 Matthew Remmel. All rights reserved.

/*
 * The purpose of the class is to wrap raw sockets to make them easier to work with.
 */


#ifndef MRLIB_SOCKET_HPP
#define MRLIB_SOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>

// TODO: This will work on POSIX only, can use Winsock for windows.
// TODO: Get host name, get ip address, get port, getters, description, inspect

namespace mrlib {

    class Socket {
    public:
        // Internal Data
        int _socket;
        struct sockaddr_in _socketAddress;

        // Constructors
        Socket();
        Socket(sa_family_t sock_family, int sock_type);

        // Socket Configuration
        Socket&  setType(sa_family_t sock_family, int sock_type);
        Socket&  setAddress(const std::string& address);
        Socket&  setPort(in_port_t sock_port);

        // Socket Functions
        void    bind() const;
        void    bind(const std::string& target, in_port_t port);
        void    listen(int backlog = 5) const;
        Socket  accept() const;
        void    connect() const;
        void    connect(const std::string& target, in_port_t port);
        void    close() const;

        // Send Data
        ssize_t send(const std::string& data) const;

        // Receive Data
        std::string receive();
        std::string receive(unsigned int bytes);
    };


    /////////////////////////////
    // TEMPLATE IMPLEMENTATION //
    /////////////////////////////

    // Constructors
    inline
    Socket::Socket() {
        bzero((char *) &this->_socketAddress, sizeof(this->_socketAddress));
        this->setType(AF_INET, SOCK_STREAM);
    }

    Socket::Socket(sa_family_t sock_family, int sock_type) {
        bzero((char *) &this->_socketAddress, sizeof(this->_socketAddress));
        this->setType(sock_family, sock_type);
    }


    // Socket Configuration
    inline
    Socket& Socket::setType(sa_family_t sock_family, int sock_type) {
        this->_socketAddress.sin_family = sock_family;
        this->_socket = ::socket(sock_family, sock_type, 0);
        return *this;
    }

    inline
    Socket& Socket::setAddress(const std::string& address) {
        struct hostent* host;
        host = gethostbyname(address.c_str());
        bcopy((char *)host->h_addr, (char *)&this->_socketAddress.sin_addr.s_addr, host->h_length);
        return *this;
    }

    inline
    Socket& Socket::setPort(in_port_t port) {
        this->_socketAddress.sin_port = htons(port);
        return *this;
    }


    // Socket Functions
    inline
    void Socket::bind() const {
        if (::bind(this->_socket, (struct sockaddr *)&this->_socketAddress, sizeof(this->_socketAddress)) < 0) {
            std::string message = std::string("Error binding to port: ") + std::to_string(this->_socketAddress.sin_port);
            throw std::runtime_error(message);
        }
    }

    inline
    void Socket::bind(const std::string& target, in_port_t port) {
        this->setAddress(target);
        this->setPort(port);
        this->bind();
    }

    inline
    void Socket::listen(int backlog) const {
        if (::listen(this->_socket, backlog)) {
            std::string message = std::string("Error listening on port: ") + std::to_string(this->_socketAddress.sin_port);
            throw std::runtime_error(message);
        }
    }

    inline
    Socket Socket::accept() const {
        Socket client = Socket();
        socklen_t client_addr_len = sizeof(client._socketAddress);
        client._socket = ::accept(this->_socket, (struct sockaddr *) &client._socketAddress, &client_addr_len);
        return client;
    }

    inline
    void Socket::connect() const {
        if (::connect(this->_socket, (struct sockaddr *) &this->_socketAddress, sizeof(this->_socketAddress)) < 0) {
            std::string message = std::string("Error connecting to host");
            throw std::runtime_error(message);
        }
    }

    inline
    void Socket::connect(const std::string& target, in_port_t port) {
        this->setAddress(target);
        this->setPort(port);
        this->connect();
    }

    inline
    void Socket::close() const {
        ::close(this->_socket);
    }


    // Send Data
    inline
    ssize_t Socket::send(const std::string& data) const {
        int bytes_written = write(this->_socket, data.c_str(), data.size());

        if (bytes_written < 0) {
            std::string message = std::string("Error sending data to host");
            throw std::runtime_error(message);
        }
        else {
            return bytes_written;
        }
    }


    // Receive Data
    inline
    std::string Socket::receive() {
        std::string data = "";

        ssize_t recv_len = 1;
        char buff[1024];

        while (recv_len > 0) {
            recv_len = ::recv(this->_socket, buff, 1024, 0);
            data.append(buff, recv_len);

            if (recv_len < 1024) break;
        }

        return data;
    }
}

#endif // MRLIB_SOCKET_HPP

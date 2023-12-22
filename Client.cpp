#include <boost/asio.hpp>
#include <iostream>
#include <array>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_service io_service;
        tcp::socket socket(io_service);
        socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12345));

        std::string message = "Hello, server!\n";
        boost::asio::write(socket, boost::asio::buffer(message));

        std::array<char, 128> reply;
        boost::system::error_code error;
        size_t length = socket.read_some(boost::asio::buffer(reply), error);

        if (error) {
            throw boost::system::system_error(error); // 실제 에러 처리
        }

        std::cout.write(reply.data(), length);
        std::cout << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

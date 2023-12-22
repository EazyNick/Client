#include <boost/asio.hpp>
#include <iostream>
#include <array>

using boost::asio::ip::tcp;

int main() {
    try {
        // I/O 작업을 처리할 수 있게 해주는 io_service 객체를 생성합니다. 
        // 이 객체는 네트워크 I/O 작업을 수행하기 위한 중심적인 이벤트 루프를 관리
        boost::asio::io_service io_service;
        //TCP 소켓 객체를 생성합니다. 이 소켓은 서버에 연결하고 데이터를 주고받기 위해 사용
        tcp::socket socket(io_service);
        //소켓을 통해 서버에 연결을 시도합니다. 여기서는 로컬호스트 주소인 127.0.0.1과 포트 12345를 사용
        socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12345));

        //서버로 보낼 메시지를 std::string 객체에 저장
        std::string message = "Hello, server 한글되냐?!\n";
        //message에 저장된 데이터를 서버로 전송합니다. 
        // boost::asio::buffer는 메모리 버퍼를 생성하여 write 함수가 전송할 데이터를 소켓을 통해 보낼 수 있게 합니다.
        boost::asio::write(socket, boost::asio::buffer(message));

        //서버로부터의 응답을 저장할 고정 크기의 std::array를 선언
        std::array<char, 128> reply;
        //에러 코드를 저장할 boost::system::error_code 객체를 생성
        boost::system::error_code error;
        //소켓으로부터 데이터를 읽어 reply 배열에 저장, 읽은 데이터의 크기를 length에 저장
        //만약 에러가 발생하면 error에 에러 코드가 저장
        size_t length = socket.read_some(boost::asio::buffer(reply), error);

        if (error) {
            //에러가 있으면 boost::system::system_error 예외를 던져 에러를 처리
            throw boost::system::system_error(error); // 실제 에러 처리
        }
        //읽은 데이터를 콘솔에 출력
        //std::cout.write 함수는 바이너리 데이터를 처리할 수 있으며, 
        //length만큼 데이터를 콘솔에 출력합니다. std::endl은 새 줄 문자를 출력하고 버퍼를 플러시합니다.
        std::cout.write(reply.data(), length);
        std::cout << std::endl;
    }
    catch (std::exception& e) {
        //에러 발생시 에러메시지 출력
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

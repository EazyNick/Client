#include <boost/asio.hpp>
#include <iostream>
#include <array>

using boost::asio::ip::tcp;

int main() {
    try {
        // I/O �۾��� ó���� �� �ְ� ���ִ� io_service ��ü�� �����մϴ�. 
        // �� ��ü�� ��Ʈ��ũ I/O �۾��� �����ϱ� ���� �߽����� �̺�Ʈ ������ ����
        boost::asio::io_service io_service;
        //TCP ���� ��ü�� �����մϴ�. �� ������ ������ �����ϰ� �����͸� �ְ�ޱ� ���� ���
        tcp::socket socket(io_service);
        //������ ���� ������ ������ �õ��մϴ�. ���⼭�� ����ȣ��Ʈ �ּ��� 127.0.0.1�� ��Ʈ 12345�� ���
        socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12345));

        //������ ���� �޽����� std::string ��ü�� ����
        std::string message = "Hello, server �ѱ۵ǳ�?!\n";
        //message�� ����� �����͸� ������ �����մϴ�. 
        // boost::asio::buffer�� �޸� ���۸� �����Ͽ� write �Լ��� ������ �����͸� ������ ���� ���� �� �ְ� �մϴ�.
        boost::asio::write(socket, boost::asio::buffer(message));

        //�����κ����� ������ ������ ���� ũ���� std::array�� ����
        std::array<char, 128> reply;
        //���� �ڵ带 ������ boost::system::error_code ��ü�� ����
        boost::system::error_code error;
        //�������κ��� �����͸� �о� reply �迭�� ����, ���� �������� ũ�⸦ length�� ����
        //���� ������ �߻��ϸ� error�� ���� �ڵ尡 ����
        size_t length = socket.read_some(boost::asio::buffer(reply), error);

        if (error) {
            //������ ������ boost::system::system_error ���ܸ� ���� ������ ó��
            throw boost::system::system_error(error); // ���� ���� ó��
        }
        //���� �����͸� �ֿܼ� ���
        //std::cout.write �Լ��� ���̳ʸ� �����͸� ó���� �� ������, 
        //length��ŭ �����͸� �ֿܼ� ����մϴ�. std::endl�� �� �� ���ڸ� ����ϰ� ���۸� �÷����մϴ�.
        std::cout.write(reply.data(), length);
        std::cout << std::endl;
    }
    catch (std::exception& e) {
        //���� �߻��� �����޽��� ���
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

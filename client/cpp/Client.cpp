#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char * argv[])
{
  boost::asio::io_service io;

  // Daytime
  try {
    if (argc != 2) {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    tcp::resolver resolver (io);
    tcp::resolver::query query (argv[1], "10674");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    tcp::socket socket (io);
    boost::asio::connect(socket, endpoint_iterator);

    for (;;) {
      boost::array<char, 128> buffer;
      boost::system::error_code error;
      size_t len = socket.read_some(boost::asio::buffer(buffer), error);

      if (error == boost::asio::error::eof) {
        break; // Connection closed cleanly by peer.
      }
      else if (error) {
        throw boost::system::system_error(error); // Some other error.
      }

      std::cout.write(buffer.data(), len);
    }
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

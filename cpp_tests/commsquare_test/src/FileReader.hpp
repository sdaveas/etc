#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class FileReader {
public:
  FileReader(std::string data) : m_ifstream(std::move(data)), m_buffer() {
    m_ifstream.seekg(0, std::ios::end);
    m_buffer.resize(m_ifstream.tellg());
    m_ifstream.seekg(0);
    m_ifstream.read(m_buffer.data(), m_buffer.size());
  }
  FileReader(const FileReader &) = delete;
  FileReader(FileReader &&) = delete;
  FileReader &operator=(FileReader) = delete;
  ~FileReader() { m_ifstream.close(); }

  inline const std::vector<char> &buffer() { return m_buffer; }

  void print() const {
    for (const auto c : m_buffer) {
      std::cout << c;
    }
    std::cout << '\n';
  }

private:
  std::ifstream m_ifstream;
  std::vector<char> m_buffer;
};

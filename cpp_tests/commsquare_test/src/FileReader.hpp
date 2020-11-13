#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class FileReader {
public:
  FileReader(std::string data) : m_buffer() {
    std::ifstream ifs(std::move(data));
    ifs.seekg(0, std::ios::end);
    m_buffer.resize(ifs.tellg());
    ifs.seekg(0);
    ifs.read(m_buffer.data(), m_buffer.size());
    ifs.close();
  }
  FileReader(const FileReader &) = delete;
  FileReader(FileReader &&) = delete;
  FileReader &operator=(FileReader) = delete;
  ~FileReader() {}

  inline const std::vector<char> &buffer() { return m_buffer; }

  void print() const {
    for (const auto c : m_buffer) {
      std::cout << c;
    }
    std::cout << '\n';
  }

private:
  std::vector<char> m_buffer;
};

#ifndef RELIGHTER_IO_FILEREADER_H
#define RELIGHTER_IO_FILEREADER_H

#include <string>

class FileReader
{
public:
	FileReader(const std::string& path);
	~FileReader();
	template <class T> T read();
	void fread(void* buffer, size_t length);
	size_t length();
	size_t position();
	void seek(size_t position);
private:
	FILE* m_file;
	size_t m_length;
};

template <class T> T FileReader::read()
{
	T t;
	fread(&t, sizeof(T));
	return t;
}

#endif

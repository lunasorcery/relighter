#ifndef RELIGHTER_IO_FILEWRITER_H
#define RELIGHTER_IO_FILEWRITER_H

#include <string>

class FileWriter
{
public:
	FileWriter(const std::string& path);
	~FileWriter();
	template <class T> void write(const T& t);
	void fwrite(const void* buffer, size_t length);
	size_t length();
	size_t position();
	void seek(size_t position);
private:
	FILE* m_file;
	size_t m_length;
};

template <class T> void FileWriter::write(const T& t)
{
	fwrite(&t, sizeof(T));
}

#endif

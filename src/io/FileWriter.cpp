#include "FileWriter.h"

FileWriter::FileWriter(const std::string& path)
:
m_file(fopen(path.c_str(), "wb")),
m_length(0)
{ }

FileWriter::~FileWriter()
{
	if (m_file)
	{
		fclose(m_file);
	}
}

void FileWriter::fwrite(const void* buffer, size_t length)
{
	int pos = position();
	int bytesWritten = ::fwrite(buffer, 1, length, m_file);
	if (pos + bytesWritten > m_length)
	{
		m_length = pos + bytesWritten;
	}
}

size_t FileWriter::length()
{
	return m_length;
}

size_t FileWriter::position()
{
	return ftell(m_file);
}

void FileWriter::seek(size_t position)
{
	fseek(m_file, position, SEEK_SET);
}
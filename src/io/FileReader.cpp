#include "FileReader.h"

FileReader::FileReader(const std::string& path)
{
	m_file = fopen(path.c_str(), "rb");
	if (m_file)
	{
		fseek(m_file, 0, SEEK_END);
		m_length = ftell(m_file);
		fseek(m_file, 0, SEEK_SET);
	}
}

FileReader::~FileReader()
{
	if (m_file)
	{
		fclose(m_file);
	}
}

void FileReader::fread(void* buffer, size_t length)
{
	::fread(buffer, 1, length, m_file);
}

size_t FileReader::length()
{
	return m_length;
}

size_t FileReader::position()
{
	return ftell(m_file);
}

void FileReader::seek(size_t position)
{
	fseek(m_file, position, SEEK_SET);
}
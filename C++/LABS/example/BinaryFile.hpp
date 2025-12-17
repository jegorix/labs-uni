template<typename T>
void BinaryFile<T>::openForWrite()
{
	fs.open(filename, std::ios::binary | std::ios::out);
	if (!fs.is_open())
	{
		throw FileException(306, "Не удалось открыть бинарный файл для записи");
	}
}

template<typename T>
void BinaryFile<T>::openForRead()
{
	fs.open(filename, std::ios::binary | std::ios::in);
	if (!fs.is_open())
	{
		throw FileException(307, " не удалось открыть бинарный файл для чтения");
	}
}

template<typename T>
void BinaryFile<T>::write(const T& object)
{
	if (!fs.is_open())
	{
		throw FileException(308, " бинарный файл не открыт для записи");
	}

	try
	{
		fs << object;
	}
	catch (const FileException&)
	{
		throw;
	}
}

template<typename T>
T BinaryFile<T>::read()
{
	if (!fs.is_open())
	{
		throw FileException(309, " бинарный файл не открыт для чтения");
	}

	T new_object;

	try
	{
		fs >> new_object;
	}
	catch (const FileException&)
	{
		throw;
	}

	return new_object;
}

template<typename T>
bool BinaryFile<T>::eof() const
{
	return fs.eof();
}

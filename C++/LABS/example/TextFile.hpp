template<typename T>
void TextFile<T>::openForWrite()
{
	ofs.open(filename, std::ios::out | std::ios::trunc);
	if (!ofs.is_open())
	{
		throw FileException(300, "íå óäàëîñü îòêðûòü ôàéë äëÿ çàïèñè");
	}
}


template<typename T>
void TextFile<T>::openForRead()
{
	ifs.open(filename, std::ios::in);
	if (!ifs.is_open())
	{
		throw FileException(301, "íå óäàëîñü îòêðûòü ôàéë äëÿ ÷òåíèÿ");
	}
}

template<typename T>
void TextFile<T>::write(const T& obj)
{
	if (!ofs.is_open())
	{
		throw FileException(302, "ôàéë íå îòêðûò äëÿ çàïèñè");
	}

	ofs << obj;

	if (!ofs.good())
	{
		throw FileException(304, "îøèáêà çàïèñè â òåêñòîâûé ôàéë");
	}
}

template<typename T>
T TextFile<T>::read()
{
	if (!ifs.is_open())
	{
		throw FileException(303, "ôàéë íå îòêðûò äëÿ ÷òåíèÿ");
	}

	T new_object;

	if (!(ifs >> new_object))
	{
		throw FileException(305, "îøèáêà ÷òåíèÿ èç ôàéëà èëè íåâåðíûé ôîðìàò äàííûõ");
	}

	return new_object;
}

template<typename T>
bool TextFile<T>::eof() const
{
	return ifs.eof();
}

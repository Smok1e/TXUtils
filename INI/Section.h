#pragma once

//----------------------

namespace txu
{
 
//----------------------

namespace ini
{

//----------------------

class Section
{
public:
	Section ();				   
	Section (const Section&  copy);
	Section (      Section&& move);
	Section (const char* name);
	Section (const char* filename, const char* section_name);

	~Section ();

	bool loadFromFile (const char* filename, const char* section_name = nullptr);
	bool saveToFile   (const char* filename);

	Section& operator = (const Section& copy);

	void        setName (const char* name);
	const char* getName () const;

	bool exists (const char* key);

	template <typename value_t>
	Value& setValue    (const char* key, value_t value);
	Value& setValue    (const Value& value);
	Value& getValue    (const char* key);
	void   removeValue (const char* key);
	void   clear       ();

	Value& operator [] (const char* key);
	Value& operator [] (size_t index);

	size_t       getValuesCount () const;
	const Value* getData        () const;
	      Value* getData        ();

	Section& operator += (const Value& value);
	Section& operator -= (const char*  key  );

private:
	char* m_name;

	std::vector <Value> m_values;

};

//----------------------

Section::Section ():
	m_name   (nullptr),
	m_values ()
{}

Section::Section (const Section& copy):
	Section ()
{
	setName (copy.m_name);
	m_values = copy.m_values;
}

Section::Section (Section&& move):
	Section ()
{
	std::swap (m_name,   move.m_name  );
	std::swap (m_values, move.m_values);
}

Section::Section (const char* name):
	Section ()
{
	setName (name);
}

Section::Section (const char* filename, const char* section_name):
	Section ()
{
	loadFromFile (filename, section_name);
}

Section::~Section ()
{
	if (m_name) delete[] (m_name);
}

//----------------------

bool Section::loadFromFile (const char* filename, const char* section_name /*= nullptr*/)
{
	if (!section_name) section_name = m_name;
	if (!section_name) return false;

	static char path[_TX_BUFSIZE] = "";
	GetFullPathNameA (filename, _TX_BUFSIZE, path, nullptr);
	
	if (!fexists (path)) return false;

	size_t buffsize = _TX_BUFSIZE;
	char* buffer = new char[buffsize];

	while (GetPrivateProfileStringA (section_name, nullptr, "", buffer, buffsize, path) == buffsize-1)
	{
		delete[] (buffer);

		buffsize *= 2;
		buffer = new char[buffsize];
	}

	m_values.clear ();
	for (const char* key = buffer; *key; key++)
	{
		Value value;
		if (!value.loadFromFile (path, section_name, key)) 
		{
			delete[] (buffer);
			return false;
		}

		m_values.push_back (value);
		for (key; *key; key++);
	}

	setName (section_name);

	delete[] (buffer);
	return true;
}

bool Section::saveToFile (const char* filename)
{
	static char path[_TX_BUFSIZE] = "";
	GetFullPathNameA (filename, _TX_BUFSIZE, path, nullptr);

	// WritePrivateProfileSectionA принимает double-null-terminated строку, которая содержит связки key=value\0key=value\0...\0\0
	// Для начала найдём необходимый размер памяти для выделения

	size_t buffsize = 0;
	for (size_t i = 0, count = getValuesCount (); i < count; i++)
	{
		Value& value = m_values[i];

		buffsize += strlen (value.getKey         ()); // key
		buffsize += 1;								  // =
		buffsize += strlen (value.getStringValue ()); // value
		buffsize += 1;                                // \0
	}

	buffsize += 1; // \0

	// Выделим память под буффер, и запишем в неё значения 
	char* buffer = new char[buffsize];

	char* l_buffer = buffer; // Локальный указатель на буффер, который будет сдвигаться
	for (size_t i = 0, count = getValuesCount (); i < count; i++)
	{
		Value& value = m_values[i];

		const char* str = value.getKey ();
		size_t      len = strlen (str);
		std::memcpy (l_buffer, str, len), l_buffer += len;

		*l_buffer = '=';
		l_buffer ++;

		str = value.getStringValue ();
		len = strlen (str);
		std::memcpy (l_buffer, str, len), l_buffer += len;

		*l_buffer = '\0';
		l_buffer ++;
	}
	*l_buffer = '\0';

	bool result = WritePrivateProfileSectionA (m_name, buffer, path);

	delete[] (buffer);
	return result;
}

//----------------------

Section& Section::operator = (const Section& that)
{
	if (&that == this) return *this;

	setName (that.m_name);
	m_values = that.m_values;
	return *this;
}

//----------------------

void Section::setName (const char* name)
{
	if (!name || name == m_name) return;

	if (m_name) delete[] (m_name);

	size_t len = strlen (name);
	m_name = new char[len+1];

	std::memcpy (m_name, name, len);
	m_name[len] = '\0';
}

//----------------------

const char* Section::getName () const
{
	return m_name? m_name: "";
}

//----------------------

bool Section::exists (const char* key)
{
	size_t count = m_values.size ();
	for (size_t i = 0; i < count; i++) 
		if (!strcmp (m_values[i].getKey (), key)) return true;

	return false;
}

//----------------------

template <typename value_t>
Value& Section::setValue (const char* key, value_t value)
{
	if (exists (key)) 
		return getValue (key) = value;

	m_values.push_back (Value (key, value));
	return m_values.back ();
}

Value& Section::setValue (const Value& value)
{
	if (exists (value.getKey ()))
		return getValue (value.getKey ()) = value;

	m_values.push_back (value);
	return m_values.back ();
}

Value& Section::getValue (const char* key)
{
	size_t count = m_values.size ();
	for (size_t i = 0; i < count; i++)
	{
		Value& value = m_values[i];
		if (!strcmp (value.getKey (), key)) return value;
	}	

	return setValue (key, 0);
}

void Section::removeValue (const char* key)
{
	size_t count = m_values.size ();
	for (size_t i = 0; i < count; i++)
	{
		if (!strcmp (m_values[i].getKey (), key)) 
		{
			m_values.erase (m_values.begin () + i);
			return;
		}
	}
}

void Section::clear ()
{
	m_values.clear ();
}

//----------------------

Value& Section::operator [] (const char* key)
{
	return getValue (key);
}

Value& Section::operator [] (size_t index)
{
	assert (index < m_values.size ());
	return m_values[index];
}

//----------------------

size_t Section::getValuesCount () const
{
	return m_values.size ();
}

//----------------------

const Value* Section::getData () const
{
	return m_values.data ();
}

Value* Section::getData ()
{
	return m_values.data ();
}

//----------------------

Section& Section::operator += (const Value& value)
{
	setValue (value);
	return *this;
}

Section& Section::operator -= (const char* key)
{
	removeValue (key);
	return *this;
}

//----------------------

} // namespace ini

//----------------------

} // namespace txu

//----------------------
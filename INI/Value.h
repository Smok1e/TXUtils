#pragma once

//----------------------

namespace txu
{

//----------------------

namespace ini
{

//----------------------

class Value
{
public:
	Value ();
	Value (const Value&  copy);
	Value (      Value&& move);

	template <typename value_t>
	Value (const char* key, value_t value);

	~Value ();

	bool loadFromFile (const char* filename, const char* section, const char* key = nullptr);
	bool saveToFile (const char* filename, const char* section);

	Value& operator = (const Value& that);

	template <typename value_t>
	Value& operator = (const value_t& value);

	void        setKey (const char* key);
	const char* getKey () const;

	void setValue (const char* value);
	void setValue (int         value);
	void setValue (double      value);
	void setValue (float       value);
	void setValue (char        value);
	void setValue (bool        value);
	void setValue (Color       value);
	void setValue (Coord2D     value);

	const char* getStringValue  ();
	int         getIntValue     ();
	double      getDoubleValue  ();
	float       getFloatValue   ();
	char        getCharValue    ();
	bool        getBoolValue    ();
	Color       getColorValue   ();
	Coord2D     getCoord2DValue ();

	operator const char* ();
	operator int         ();
	operator double      ();
	operator float       ();
	operator char        ();
	operator bool        ();
	operator Color       ();
	operator Coord2D     ();

private:
	char* m_key;
	char* m_value;

	void formatValue (const char* format, ...);

};

//----------------------

Value::Value ():
	m_key   (nullptr),
	m_value (nullptr)
{}

Value::Value (const Value& copy):
	Value ()
{
	setKey   (copy.m_key  );
	setValue (copy.m_value);
}

Value::Value (Value&& move):
	Value ()
{
	std::swap (m_key,   move.m_key  );
	std::swap (m_value, move.m_value);
}

template <typename value_t>
Value::Value (const char* key, value_t value):
	Value ()
{
	setKey   (key  );
	setValue (value);
}

Value::~Value ()
{
	if (m_key)   delete[] (m_key);
	if (m_value) delete[] (m_value);
}

//----------------------

bool Value::loadFromFile (const char* filename, const char* section, const char* key /*= nullptr*/)
{
	if (!key) key = m_key;
	if (!key) return false;

	static char path[_TX_BUFSIZE] = "";
	GetFullPathNameA (filename, _TX_BUFSIZE, path, nullptr);	

	if (!fexists (path)) return false;

	size_t buffsize = _TX_BUFSIZE;
	char* buffer = new char[buffsize];

	size_t readbytes = 0;
	while ((readbytes = GetPrivateProfileStringA (section, key, "", buffer, buffsize, path)) == buffsize-1)
	{
		delete[] (buffer);

		buffsize *= 2;
		buffer = new char[buffsize];
	}	

	if (!readbytes)
	{
		delete[] (buffer);
		return false;
	}

	setValue (buffer);
	setKey   (key);

	delete[] (buffer);
	return true;
}

//----------------------

bool Value::saveToFile (const char* filename, const char* section)
{
	static char path[_TX_BUFSIZE] = "";
	GetFullPathNameA (filename, _TX_BUFSIZE, path, nullptr);	

	return WritePrivateProfileStringA (section, m_key, m_value, path);
}

//----------------------

Value& Value::operator = (const Value& that)
{
	if (&that == this) return *this;

	setKey   (that.m_key  );
	setValue (that.m_value);
	return *this;
}

template <typename value_t>
Value& Value::operator = (const value_t& value)
{
	setValue (value);
	return *this;
}

//----------------------

void Value::setKey (const char* key)
{
	if (!key || key == m_key) return;

	if (m_key) delete[] (m_key);

	size_t len = strlen (key);
	m_key = new char[len+1];

	std::memcpy (m_key, key, len);
	m_key[len] = '\0';
}

const char* Value::getKey () const
{
	return m_key? m_key: "";
}

//----------------------

void Value::setValue (const char* value)
{
	if (!value || value == m_value) return;

	if (m_value) delete[] (m_value);

	size_t len = strlen (value);
	m_value = new char[len+1];

	std::memcpy (m_value, value, len);
	m_value[len] = '\0';
}

void Value::setValue (int value)
{
	formatValue ("%d", value);
}

void Value::setValue (double value)
{
	formatValue ("%lf", value);
}

void Value::setValue (float value)
{
	formatValue ("%f", value);
}

void Value::setValue (char value)
{
	formatValue ("%c", value);
}

void Value::setValue (bool value)
{
	setValue (value? "true": "false");
}

void Value::setValue (Color value)
{
	formatValue ("0x%08X", value.r << 24 | value.g << 16 | value.b << 8 | value.a << 0);
}

void Value::setValue (Coord2D value)
{
	formatValue ("{%lf, %ld}", value.x, value.y);
}

//----------------------

const char* Value::getStringValue ()
{
	return m_value? m_value: "";
}

int Value::getIntValue ()
{
	return std::atoi (getStringValue ());
}

double Value::getDoubleValue ()
{
	return std::strtod (getStringValue (), nullptr);
}

float Value::getFloatValue ()
{
	return std::strtof (getStringValue (), nullptr);
}

char Value::getCharValue ()
{
	return getStringValue ()[0];
}

bool Value::getBoolValue ()
{
	if (!strcmp (getStringValue (), "true" )) return true;
	if (!strcmp (getStringValue (), "false")) return false;

	return getIntValue ();
}

Color Value::getColorValue ()
{
	const char* str = getStringValue ();
	if (str[1] == 'x') str += 2; 

	size_t len = strlen (str);
	if (len != 6 && len != 8) 
		return txu::Color::Black;

	unsigned num = strtoul (str, nullptr, 16);
	if (len == 6) num = ((num << 8) | 0xFF);

	return Color 
	(
		(num >> 24) & 0xFF, // R
		(num >> 16) & 0xFF, // G
		(num >>  8) & 0xFF, // B
		(num >>  0) & 0xFF  // A
	);
}

Coord2D Value::getCoord2DValue ()
{
	txu::Coord2D coord;
	sscanf_s (getStringValue (), "{%lf, %lf}", &coord.x, &coord.y);

	return coord;
}

//----------------------

Value::operator const char* ()
{
	return getStringValue ();
}

Value::operator int ()
{
	return getIntValue ();
}

Value::operator double ()
{
	return getDoubleValue ();
}

Value::operator float ()
{
	return getFloatValue ();
}

Value::operator char ()
{
	return getCharValue ();
}

Value::operator bool ()
{
	return getBoolValue ();
}

Value::operator Color ()
{
	return getColorValue ();
}

Value::operator Coord2D ()
{
	return getCoord2DValue ();
}

//----------------------

void Value::formatValue (const char* format, ...)
{
	static char buffer[_TX_BUFSIZE] = "";

	va_list args = {};
	va_start (args, format);
	vsprintf_s (buffer, format, args);
	va_end (args);

	setValue (buffer);
}

//----------------------

} // namespace ini

//----------------------

} // namespace txu

//----------------------
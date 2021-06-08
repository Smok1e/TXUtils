#pragma once

//-------------------

namespace txu
{

//-------------------

class Sound
{
public: 
	Sound ();
	Sound (const char* filename);
	Sound (Sound&  copy);
	Sound (Sound&& copy);

	~Sound ();

	bool loadFromFile (const char* filename);

	void play      ();
	void playAsync ();

private:
	char*  m_data;
	size_t m_data_size;

	void resize (size_t new_size);
	
};

//-------------------

Sound::Sound () :
	m_data      (nullptr),
	m_data_size (0)
{}

Sound::Sound (const char* filename)	:
	m_data      (nullptr),
	m_data_size (0)
{ loadFromFile (filename); }

Sound::Sound (Sound& copy) :
	m_data      (nullptr),
	m_data_size (0)
{
	resize (copy.m_data_size);
	std::memcpy (m_data, copy.m_data, m_data_size);
}

Sound::Sound (Sound&& copy)	:
	m_data      (nullptr),
	m_data_size (0)
{
	std::swap (m_data,      copy.m_data     );
	std::swap (m_data_size, copy.m_data_size);
}

Sound::~Sound ()
{
	delete[] (m_data);
}

//-------------------

bool Sound::loadFromFile (const char* filename)
{
	FILE* file = __txu_fopen (filename, "rb");
	if (!file)
		return false;

	size_t size = fsize (file);
	resize (size);

	fread (m_data, 1, size, file);
	fclose (file);

	return true;
}

//-------------------

void Sound::play ()
{
	winmm::PlaySoundA (m_data, GetModuleHandleA (nullptr), SND_MEMORY);
}

void Sound::playAsync ()
{
	winmm::PlaySoundA (m_data, GetModuleHandleA (nullptr), SND_MEMORY | SND_ASYNC);
}

//-------------------

void Sound::resize (size_t new_size)
{
	char* tmp = new char[new_size];
	
	if (m_data) 
		std::memcpy (tmp, m_data, std::min (new_size, m_data_size));

	std::swap (m_data, tmp);
	m_data_size = new_size;

	if (tmp)
		delete[] (tmp);
}

//-------------------

} // namespace txu
#include <vector>
#include <string>

static bool strchr(char c, const char *str)
{
	while (*str)
	{
		if (*str == c)
			return true;
		str++;
	}
	if (*str == c)
		return true;
	return false;
}

static size_t	strlen_word(const std::string::const_iterator str, const char* c)
{
	size_t	len;

	len = 0;
	while (!strchr(str[len], c) && str[len])
	{
		len++;
	}
	return (len);
}

std::vector<std::string> split(const std::string &str, const char* c)
{   
	std::vector<std::string> tab;
    size_t i = 0;

    while (str[i])
    {
		while (str[i] && strchr(str[i], c))
		{
			++i; 
		}
		tab.push_back(str.substr(i, strlen_word(str.begin() + i, c)));;
		i = i + strlen_word(str.begin() + i, c);
	}
	return (tab);
}
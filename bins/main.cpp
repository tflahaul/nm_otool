#include <iostream>
#include <string>

static void		ft_putendl(std::string const &str)
{
	std::cout << str << std::endl;
}

int			main(void)
{
	std::string	string("oui oui baguette");

	ft_putendl(string);
	return (0);
}

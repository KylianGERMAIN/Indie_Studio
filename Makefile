##
## EPITECH PROJECT, 2021
## B-YEP-400-PAR-4-1-indiestudio-kylian.germain
## File description:
## Makefile
##

NAME	=	IndieStudio

all:
	-mkdir build
	cmake . -Bbuild
	@make --no-print-directory -C build

clean:
	-@make clean --no-print-directory -C build

fclean:	clean
	rm -rf build
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
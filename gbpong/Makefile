NAME = pong.gb
AS = ./wla_dx_9.9/wla-gb.exe
LD = ./wla_dx_9.9/wlalink.exe
LDFLAGS = -v
SFILES = pong.s
OFILES = $(SFILES:.s=.o)
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OFILES)
	$(LD) $(LDFLAGS) linkfile $(NAME)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

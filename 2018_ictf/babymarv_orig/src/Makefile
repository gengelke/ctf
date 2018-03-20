
all: babymarvel babymarvel2

babymarvel2: program2.c utils.c  utils.h  lobby.c  lobby.h   users.c   users.h   pastes.c  pastes.h
	gcc program2.c utils.c lobby.c users.c pastes.c -std=c99 -O1 -Wno-unused-result -Wno-format-security -fno-stack-protector -z execstack -o babymarvel2
	strip --strip-all babymarvel2

babymarvel-hex: program-printhex.c  utils.c  utils.h  lobby.c  lobby.h   users.c   users.h   pastes.c  pastes.h
        gcc program-printhex.c  utils.c lobby.c users.c pastes.c -std=c99 -O1 -Wno-unused-result -Wno-format-security -fno-stack-protector -z execstack -o $@


babymarvel: program.c \
	utils.c \
	utils.h \
	lobby.c \
	lobby.h \
	users.c \
	users.h \
	pastes.c \
	pastes.h
	gcc program.c utils.c lobby.c users.c pastes.c -std=c99 -O1 -Wno-unused-result -Wno-format-security -fno-stack-protector -z execstack -o babymarvel
	strip --strip-all babymarvel

clean:
	rm -f babymarvel babymarvel2


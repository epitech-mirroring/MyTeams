##
## EPITECH PROJECT, 2024
## Teams Master
## File description:
## This is the Makefile for the MyTeams project
## This manages the compilation of the project
##

# All the source files
LIBRARIES		=	common/my		\
					common/json

TESTS			=

# Compiler and linker settings
SERVER 			=   server/
CLIENT 			=   client/
LOG				=	./build.log

.PHONY: all clean fclean re tests_run clean_test \
	$(LIBRARIES) $(SERVER) $(CLIENT) libraries

# Colors and formatting
GREEN =		\033[1;32m
YELLOW =	\033[1;33m
RED =		\033[1;31m
BLUE =		\033[1;36m
GOLD =		\033[1;33m
MAGENTA =	\033[1;35m
RESET =		\033[0m

RUNNING = [$(YELLOW)~$(RESET)]
SUCCESS = [$(GREEN)✔$(RESET)]
FAILURE = [$(RED)✘$(RESET)]
SKIPPED = [$(MAGENTA)@$(RESET)]

all:	libraries $(SERVER) $(CLIENT)
# Check presence of server and client
		@if [ -f 'myteams_cli' ]; then \
			printf "$(SUCCESS)$(GREEN)  🎉  myteams_cli built \
successfully$(RESET)\n";\
		else \
			printf "$(FAILURE)$(RED)  🚨  \
myteams_cli build failed$(RESET)\n"; \
			cat $(LOG); \
			exit 1; \
		fi
		@if [ -f 'myteams_server' ]; then \
			printf "$(SUCCESS)$(GREEN)  🎉  myteams_server built \
successfully$(RESET)\n";\
		else \
			printf "$(FAILURE)$(RED)  🚨  myteams_server build \
failed$(RESET)\n"; \
			cat $(LOG); \
			exit 1; \
		fi

libraries: $(LIBRARIES)

$(LIBRARIES):
	@LOWERCASE_DIR=$$(echo $@ | sed 's:.*/::' \
	| tr '[:upper:]' '[:lower:]') ; \
	LIB_NAME=lib$${LOWERCASE_DIR}.a ; \
	printf "$(RUNNING) $(BLUE) 🧱  Building $@$(RESET)"; \
	if [ -f libs/$${LIB_NAME} ]; then \
		printf "\r$(SKIPPED)\n"; \
	else \
		make -C $@ >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || \
		(printf "\r$(FAILURE)\n" && cat $(LOG) && exit 1); \
		printf "$(RUNNING) $(BLUE) 📦  Moving built binary (\
$@/$${LIB_NAME})$(RESET)"; \
		cp $@/$${LIB_NAME} libs/ >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || (printf "\r$(FAILURE)\n"); \
	fi; \
	printf "$(RUNNING) $(BLUE) 📦  Linking include/\
$${LOWERCASE_DIR}$(RESET)"; \
	if [ -d include/$${LOWERCASE_DIR} ]; then \
		printf "\r$(SKIPPED)\n"; \
	else \
		ln -s $(shell pwd)/$@/include/* include/ \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	fi;

$(SERVER):
		@printf "$(RUNNING) $(BLUE) 🧱  Building $@$(RESET)"
		@make -C $@ >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
		@printf "$(RUNNING) $(BLUE) 📦  Moving built binary$(RESET)"
		@mv $@/myteams_server . >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || (printf "\r$(FAILURE)\n" && cat $(LOG) \
		&& exit 1)

$(CLIENT):
		@printf "$(RUNNING) $(BLUE) 🧱  Building $@$(RESET)"
		@make -C $@ >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
		@printf "$(RUNNING) $(BLUE) 📦  Moving built binary$(RESET)"
		@mv $@/myteams_cli . >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || (printf "\r$(FAILURE)\n" && cat $(LOG) \
		&& exit 1)

clean:
# Delete all the object files
		@for lib in $(LIBRARIES); do \
			printf "$(RUNNING) $(RED) 🗑️   Cleaning $${lib}$(RESET)"; \
			make -C $${lib} clean >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done

fclean: clean clean_test
# Delete the binary
		@printf "$(RUNNING) $(RED) 🗑️   Deleting myteams_cli$(RESET)";
		@if [ -f myteams_cli ]; then \
			rm -f myteams_cli >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		else \
			printf "\r$(SKIPPED)\n"; \
		fi
		@printf "$(RUNNING) $(RED) 🗑️   Deleting myteams_server$(RESET)";
		@if [ -f myteams_server ]; then \
			rm -f myteams_server >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		else \
			printf "\r$(SKIPPED)\n"; \
		fi
		@printf "$(RUNNING) $(RED) 🗑️   Fcleaning server$(RESET)";
		@make -C $(SERVER) fclean >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
		@printf "$(RUNNING) $(RED) 🗑️   Fcleaning client$(RESET)";
		@make -C $(CLIENT) fclean >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
		@for lib in $(LIBRARIES); do \
			LOWERCASE_DIR=$$(echo $${lib} | sed 's:.*/::' \
			| tr '[:upper:]' '[:lower:]') ; \
			LIB_NAME=lib$${LOWERCASE_DIR}.a ; \
			printf "$(RUNNING) $(RED) 🗑️   Deleting libs/$${LIB_NAME}\
$(RESET)"; \
			if [ -f libs/$${LIB_NAME} ]; then \
				rm -f libs/$${LIB_NAME} >> $(LOG) 2>&1 \
				&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
			else \
				printf "\r$(SKIPPED)\n"; \
			fi; \
			printf "$(RUNNING) $(RED) 🗑️   Deleting \
include/$${LOWERCASE_DIR}$(RESET)"; \
			if [ -d include/$${LOWERCASE_DIR} ]; then \
				rm -f include/$${LOWERCASE_DIR} >> $(LOG) 2>&1 \
				&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
			else \
				printf "\r$(SKIPPED)\n"; \
			fi; \
			printf "$(RUNNING) $(RED) 🗑️   Fcleaning $${lib}$(RESET)"; \
			make -C $${lib} fclean >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done
# Delete the log file
		@printf "$(RUNNING) $(RED) 🗑️   Deleting $(LOG)$(RESET)";
		@if [ -f $(LOG) ]; then \
			rm -f $(LOG) >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		else \
			printf "\r$(SKIPPED)\n"; \
		fi

re:			fclean all

tests_run: fclean $(LIBRARIES)
# Run tests for the server
		@printf "$(RUNNING) $(BLUE) 🧪  Running server tests$(RESET)"
		@make -C $(SERVER) tests_run >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
# Run tests for the client
		@printf "$(RUNNING) $(BLUE) 🧪  Running client tests$(RESET)"
		@make -C $(CLIENT) tests_run >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
# Run tests for the libraries
		@for lib in $(LIBRARIES); do \
			printf "$(RUNNING) $(BLUE) 🧪  Running tests for \
$${lib}$(RESET)"; \
			make -C $${lib} tests_run >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done

clean_test:
	@printf "$(RUNNING) $(RED) 🗑️   Deleting tests.out$(RESET)"
	@if [ -f tests.out ]; then \
		rm -f tests.out >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️   Deleting coverage$(RESET)"
	@rm -f coverage* >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting tests/*.o$(RESET)"
	@rm -f $(TESTS_OBJS) >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting *.gcda$(RESET)"
	@find ./ -name "*.gcda" -delete >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting *.gcno$(RESET)"
	@find ./ -name "*.gcno" -delete >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting criterion.xml$(RESET)"
	@if [ -f criterion.xml ]; then \
		rm -f criterion.xml >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️   Deleting tests.log$(RESET)"
	@if [ -f tests.log ]; then \
		rm -f tests.log >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️   Deleting coverage.log$(RESET)"
	@if [ -f coverage.log ]; then \
		rm -f coverage.log >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@if [ -d .cache/ ]; then \
		printf "$(RUNNING) $(RED) 🗑️   Deleting .cache/$(RESET)"; \
		rm -rf .cache >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	fi
	@if [ -d .local/ ]; then \
		printf "$(RUNNING) $(RED) 🗑️   Deleting .local/$(RESET)"; \
		rm -rf .local >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	fi
# Clean the tests for the server
	@printf "$(RUNNING) $(RED) 🗑️   Deleting tests for server$(RESET)"
	@make -C $(SERVER) clean_test >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
# Clean the tests for the client
	@printf "$(RUNNING) $(RED) 🗑️   Deleting tests for client$(RESET)"
	@make -C $(CLIENT) clean_test >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
# Clean the tests for the libraries
	@for lib in $(LIBRARIES); do \
		printf "$(RUNNING) $(RED) 🗑️   \
Deleting tests for $${lib}$(RESET)";\
		make -C $${lib} clean_test >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	done
